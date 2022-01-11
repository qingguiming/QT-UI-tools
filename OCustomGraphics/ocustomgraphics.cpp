#include "ocustomgraphics.h"
#include <QMouseEvent>
#include <QtMath>
#include <QPainter>

OCustomGraphics::OCustomGraphics(QWidget *parent) :
    QWidget(parent)
{
    selectDotVisible = true;
    dotRadius = 3;
    lineWidth = 1;

    dotColor = Qt::red;
    lineColor = Qt::green;
    polygonColor = Qt::cyan;

    selectColor = Qt::yellow;
    selectedIndex = -1;

}

void OCustomGraphics::mousePressEvent(QMouseEvent *e)
{
    QPoint p = e->pos();
    pressed = true;
    lastPoint = this->mapToGlobal(p);

    //连线模式下不选中
    if(tempPoints.isEmpty())
    {
        //如果选中了,检测是否点到点上
        bool selectedPot = false;
        selectedEllipseIndex = -1;
        if (selectedIndex != -1)
        {
            for(int i = tempPolygons.at(selectedIndex).pos.size() - 1; i >= 0; --i)
            {
                if(length(p, tempPolygons.at(selectedIndex).pos[i]) <= 36) {
                    selectedPot = true;
                    selectedEllipseIndex = i;
                    ellipsePos = tempPolygons.at(selectedIndex).pos[i];
                    break;
                }
            }
        }

        //当前选中了点则不用重绘
        if(selectedPot) {
            return;
        }

        //判断是否选中一个
        selectedIndex = -1;
        for(int i = tempPolygons.size() - 1; i >= 0; --i)
        {
            tempPolygons[i].selected = checkPoint(tempPolygons.at(i).pos, p.x(), p.y());
            if(tempPolygons.at(i).selected)
            {
                //防止重叠部分
                if(selectedIndex == -1)
                {
                    selectedIndex = i;
                    pressedPolygon = tempPolygons.at(i);
                }
                else
                {
                    tempPolygons[i].selected = false;
                }
            }
        }

        this->update();
    }
}

void OCustomGraphics::mouseMoveEvent(QMouseEvent *e)
{
    tempPoint = e->pos();
    if(pressed && selectedIndex != -1) {
        //整体偏移坐标
        QPoint delta = this->mapToGlobal(tempPoint) - lastPoint;
        int len = tempPolygons.at(selectedIndex).pos.size();

        if(selectedEllipseIndex != -1) { //移动点
            tempPolygons[selectedIndex].pos[selectedEllipseIndex] = ellipsePos + delta;
        } else if(selectedIndex != -1) { //移动面
            for(int i = 0; i < len; ++i) {
                tempPolygons[selectedIndex].pos[i] = pressedPolygon.pos.at(i) + delta;
            }
        }
    }

    this->update();
}

void OCustomGraphics::mouseReleaseEvent(QMouseEvent *e)
{
    //鼠标右键清空临时的
    if (e->button() == Qt::RightButton) {
        clearTemp();
        return;
    }

    //检测再次点击与最后个点 - 还没写
    pressed = false;
    if(selectedIndex != -1) {
        return;
    }

    QPoint point = e->pos();
    if(tempPoints.count() > 0) {
        qreal len = (qPow(tempPoints.first().x() - point.x() , 2.0) + qPow(tempPoints.first().y() - point.y() , 2.0) );
        if(len < 100) {
            //完成一个多边形
            if(tempPoints.size() >= 3) {
                Polygon pol;
                pol.pos = tempPoints.toVector();
                pol.selected = false;
                tempPolygons.append(pol);
            }

            tempPoints.clear();
            this->update();
            return;
        }
    }

    tempPoints.append(point);
    this->update();
}

void OCustomGraphics::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing, true);

    //绘制多边形
    foreach(const Polygon &p, tempPolygons) {
        drawPolygon(&painter, p);
    }

    //绘制点集合
    drawLines(&painter, tempPoints, false);
}

void OCustomGraphics::drawPolygon(QPainter *p, const Polygon &v)
{
    p->save();

    //绘制多边形
    p->setPen(QPen(lineColor, lineWidth));
    v.selected ? p->setBrush(selectColor) : p->setBrush(polygonColor);
    p->drawPolygon(v.pos.data(), v.pos.size());

    //绘制圆点
    if(selectDotVisible && v.selected) {
        p->setPen(Qt::NoPen);
        p->setBrush(dotColor);
        foreach(const QPoint &point, v.pos) {
            p->drawEllipse(point, dotRadius, dotRadius);
        }
    }

    p->restore();
}

void OCustomGraphics::drawLines(QPainter *p, const QList<QPoint> &list, bool isFirst)
{
    p->save();

    int count = list.count();
    if (count > 0) {
        //绘制点集合
        p->setPen(Qt::NoPen);
        p->setBrush(dotColor);
        for(int i = 0; i < count; ++i) {
            p->drawEllipse(list.at(i), dotRadius, dotRadius);
        }

        //绘制线条集合
        p->setPen(QPen(lineColor, lineWidth));
        p->setBrush(Qt::NoBrush);
        for(int i = 0; i < count - 1; ++i) {
            p->drawLine(list.at(i), list.at(i + 1));
        }

        //绘制最后一条线条
        p->drawLine(list.last(), isFirst ? list.first() : tempPoint);
    }

    p->restore();
}

double OCustomGraphics::length(const QPoint &p1, const QPoint &p2)
{
    //平方和
    return qPow(p1.x() - p2.x(), 2.0) + qPow(p1.y() - p2.y(), 2.0);
}

bool OCustomGraphics::checkPoint(const QVector<QPoint> &points, int testx, int testy)
{
    //最少保证3个点
    const int count = points.size();
    if(count < 3) {
        return false;
    }

    QList<int> vertx, verty;
    for(int i = 0; i < count; ++i) {
        vertx << points.at(i).x();
        verty << points.at(i).y();
    }

    //核心算法,计算坐标是否在多边形内部
    int i = 0, j, c = 0;
    for (i = 0, j = count - 1; i < count; j = i++)
    {
        bool b1 = (verty.at(i) > testy) != (verty.at(j) > testy);
        bool b2 = (testx < (vertx.at(j) - vertx.at(i)) * (testy - verty.at(i)) / (verty.at(j) - verty.at(i)) + vertx.at(i));
        if (b1 && b2)
        {
            c = !c;
        }
    }

    return c;
}


bool OCustomGraphics::getSelectDotVisible() const
{
    return selectDotVisible;
}

int OCustomGraphics::getDotRadius() const
{
    return dotRadius;
}

int OCustomGraphics::getLineWidth() const
{
    return lineWidth;
}

QColor OCustomGraphics::getDotColor() const
{
    return dotColor;
}

QColor OCustomGraphics::getLineColor() const
{
    return lineColor;
}

QColor OCustomGraphics::getPolygonColor() const
{
    return polygonColor;
}

QColor OCustomGraphics::getSelectColor() const
{
    return selectColor;
}



void OCustomGraphics::setSelectDotVisible(bool selectDotVisible)
{
    this->selectDotVisible = selectDotVisible;
}

void OCustomGraphics::setDotRadius(int dotRadius)
{
    this->dotRadius = dotRadius;

}

void OCustomGraphics::setLineWidth(int lineWidth)
{
    this->lineWidth = lineWidth;

}

void OCustomGraphics::setDotColor(const QColor &dotColor)
{
    this->dotColor = dotColor;

}

void OCustomGraphics::setLineColor(const QColor &lineColor)
{
    this->lineColor = lineColor;

}

void OCustomGraphics::setPolygonColor(const QColor &polygonColor)
{
    this->polygonColor = polygonColor;

}

void OCustomGraphics::setSelectColor(const QColor &selectColor)
{
    this->selectColor = selectColor;

}

void OCustomGraphics::clearTemp()
{
    tempPoints.clear();
}

void OCustomGraphics::clearAll()
{
    tempPolygons.clear();
}
