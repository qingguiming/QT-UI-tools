#include "ocustompie.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>

OCustomPie::OCustomPie(QWidget *parent) :
    QWidget(parent)
{
     showPercent = false;
}
void OCustomPie::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制饼图
    drawPie(&painter);
}

void OCustomPie::drawPie(QPainter *painter)
{
    painter->save();

    int radius = 93;
    QRect rect(-radius, -radius, radius * 2, radius * 2);

    double startAngle = 0;
    double sum = getSumValue();

    //逐个取出值并绘制饼图区域和对应的文字
    int count = labels.count();
    for (int i = 0; i < count; ++i)
    {
        //取出值并计算当前值占比面积
        double value = values.at(i);
        double arcLength = value / sum * 360;
        double percent = value / sum * 100;
        QRect pieRect = rect;

        //如果当前区域展开则需要设置边框
//        painter->setPen(Qt::NoPen);
//        if (explodedIndex == i || explodedAll) {
//            painter->setPen(borderColor);
//            QPoint center = pieRect.center();
//            int mid = startAngle + arcLength / 2;
//            center += getOffsetPoint(mid);
//            pieRect.moveCenter(center);
//        }

        //从颜色集合中取出颜色
        painter->setBrush(colors.at(i));
        painter->drawPie(pieRect, startAngle * 16, arcLength * 16);

        QString strValue = labels.at(i);
        if (showPercent && percent > 7) {
            strValue = QString("%1%2%3%").arg(strValue).arg(strValue.isEmpty() ? "" : "\n").arg(QString::number(percent, 'f', 0));
        }

        int mid = startAngle + arcLength / 2;
        int offset = 60;
        if (percent >= 50) {
            offset = 45;
        } else if (percent >= 30) {
            offset = 55;
        } else if (percent >= 15) {
            offset = 60;
        }

        QPoint p = getOffsetPoint(mid, offset);
//        qDebug()<< p << offset << mid;
        QRect textRect;
        textRect.setX(p.x() - 40);
        textRect.setY(p.y() - 30);
        textRect.setWidth(80);
        textRect.setHeight(60);
        painter->setPen(Qt::black);
        //painter->drawRect(textRect);

        QFont font;
        font.setPixelSize(strValue.isEmpty() ? 20 : 17);
        painter->setFont(font);

        painter->setPen(textColor);
        painter->drawText(textRect, Qt::AlignCenter, strValue);
        startAngle += arcLength;
    }

    painter->restore();
}

double OCustomPie::getSumValue()
{
    int val = 0 ;
    for(int i = 0 ; i <values.size();i++)
    {
        val = val + values.at(i);
    }
    return val;
}

QPoint OCustomPie::getOffsetPoint(double angel, int offset)
{
    double x = qCos(angel * M_PI / 180) * offset;
    double y = -1 * qSin(angel * M_PI / 180) * offset ;
    return QPoint(x,y);

}

QColor OCustomPie::getTextColor() const
{
    return textColor;
}

QColor OCustomPie::getBorderColor() const
{
    return borderColor;
}

void OCustomPie::setExplodedAll(bool explodedAll)
{
    this->explodedAll = explodedAll;
}

void OCustomPie::setExplodedIndex(int index)
{
    this->explodedIndex = index;
}

void OCustomPie::setDefaultColor(bool defaultColor)
{
}

void OCustomPie::setTextColor(const QColor &textColor)
{
    this->textColor = textColor;
}

void OCustomPie::setBorderColor(const QColor &borderColor)
{
    this->borderColor = borderColor;
}

void OCustomPie::setColors(const QList<QColor> &colors)
{
    this->colors = colors;
}

void OCustomPie::initPie()
{

}

void OCustomPie::appendPie(const QString &label, double value, const QString &tip)
{
    labels.append(label);
    values.append(value);
    update();

}

void OCustomPie::setDataPie()
{

}

void OCustomPie::loadPercent()
{
    showPercent = true;
    update();
}

void OCustomPie::clearPie()
{
    labels.clear();
    values.clear();
    update();

}

void OCustomPie::setHoleSize(double holeSize)
{
    this->holeSize = holeSize;
}

