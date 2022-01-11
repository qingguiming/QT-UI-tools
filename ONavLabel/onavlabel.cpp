#include "onavlabel.h"
#include <QPainter>

ONavLabel::ONavLabel(QWidget *parent) :
    QLabel(parent)
{
    borderRadius = 4;
    background = Qt::gray;
    foreground = Qt::cyan;
    showArrow = true;
    arrowSize = 5;

    arrowPosition = ArrowPosition_Left;

    showTriangle = true;
    triangleLen = 5;
    triangleLen = 5;
    trianglePosition = TrianglePosition_Left;
    triangleColor = Qt::yellow;
    bgRect = QRect(0,0,100,22);
}

void ONavLabel::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}
void ONavLabel::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制文字
    drawText(&painter);
    //绘制倒三角
    drawTriangle(&painter);
}

void ONavLabel::drawBg(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int endX = width - arrowSize;
    int endY = height - arrowSize;

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(background);

    QPolygon pts;
    if (arrowPosition == ArrowPosition_Right) {
        bgRect = QRect(0, 0, endX, height);
        pts.setPoints(3, endX, height / 2 - arrowSize, endX, height / 2 + arrowSize, width, height / 2);
    } else if (arrowPosition == ArrowPosition_Left) {
        bgRect = QRect(arrowSize, 0, width - arrowSize, height);
        pts.setPoints(3, arrowSize, height / 2 - arrowSize, arrowSize, height / 2 + arrowSize, 0, height / 2);
    } else if (arrowPosition == ArrowPosition_Bottom) {
        bgRect = QRect(0, 0, width, endY);
        pts.setPoints(3, width / 2 - arrowSize, endY, width / 2 + arrowSize, endY, width / 2, height);
    } else if (arrowPosition == ArrowPosition_Top) {
        bgRect = QRect(0, arrowSize, width, height - arrowSize);
        pts.setPoints(3, width / 2 - arrowSize, arrowSize, width / 2 + arrowSize, arrowSize, width / 2, 0);
    }

    //绘制圆角矩形和三角箭头
    if (!showArrow) {
        bgRect = this->rect();
        painter->drawRoundedRect(bgRect, borderRadius, borderRadius);
    } else {
        painter->drawRoundedRect(bgRect, borderRadius, borderRadius);
        painter->drawPolygon(pts);
    }

    painter->restore();
}

void ONavLabel::drawText(QPainter *painter)
{
    painter->save();
    painter->setPen(foreground);
    painter->setBrush(Qt::NoBrush);
    painter->drawText(bgRect, Qt::AlignCenter, this->text());
    painter->restore();
}

void ONavLabel::drawTriangle(QPainter *painter)
{
    if (!showTriangle) {
        return;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(triangleColor);

    //绘制在右侧中间,根据设定的倒三角的边长设定三个点位置
    int width = this->width();
    int height = this->height();
    int midWidth = width / 2;
    int midHeight = height / 2;

    QPolygon pts;
    if (trianglePosition == TrianglePosition_Left) {
        pts.setPoints(3, triangleLen, midHeight, 0, midHeight - triangleLen, 0, midHeight + triangleLen);
    } else if (trianglePosition == TrianglePosition_Right) {
        pts.setPoints(3, width - triangleLen, midHeight, width, midHeight - triangleLen, width, midHeight + triangleLen);
    } else if (trianglePosition == TrianglePosition_Top) {
        pts.setPoints(3, midWidth, triangleLen, midWidth - triangleLen, 0, midWidth + triangleLen, 0);
    } else if (trianglePosition == TrianglePosition_Bottom) {
        pts.setPoints(3, midWidth, height - triangleLen, midWidth - triangleLen, height, midWidth + triangleLen, height);
    }

    painter->drawPolygon(pts);

    painter->restore();
}

int ONavLabel::getBorderRadius() const
{
    return borderRadius;
}

QColor ONavLabel::getBackground() const
{
    return background;
}

QColor ONavLabel::getForeground() const
{
    return foreground;

}

bool ONavLabel::getShowArrow() const
{
    return showArrow;
}

int ONavLabel::getArrowSize() const
{
    return arrowSize;
}

ONavLabel::ArrowPosition ONavLabel::getArrowPosition() const
{
    return arrowPosition;
}

bool ONavLabel::getShowTriangle() const
{
    return showTriangle;
}

int ONavLabel::getTriangleLen() const
{
    return triangleLen;
}

ONavLabel::TrianglePosition ONavLabel::getTrianglePosition() const
{
    return trianglePosition;
}

QColor ONavLabel::getTriangleColor() const
{
    return triangleColor;
}

QSize ONavLabel::sizeHint() const
{
    return QSize(100,22);
}

QSize ONavLabel::minimumSizeHint() const
{
    return QSize(100,22);

}

void ONavLabel::setBorderRadius(int borderRadius)
{
    this->borderRadius = borderRadius;
}

void ONavLabel::setBackground(const QColor &background)
{
    this->background = background;

}

void ONavLabel::setForeground(const QColor &foreground)
{
    this->foreground = foreground;

}

void ONavLabel::setShowArrow(bool showArrow)
{
    this->showArrow = showArrow;

}

void ONavLabel::setArrowSize(int arrowSize)
{
    this->arrowSize = arrowSize;

}

void ONavLabel::setArrowPosition(const ONavLabel::ArrowPosition &arrowPosition)
{
    this->arrowPosition = arrowPosition;

}

void ONavLabel::setShowTriangle(bool showTriangle)
{
    this->showTriangle = showTriangle;

}

void ONavLabel::setTriangleLen(int triangleLen)
{
    this->triangleLen = triangleLen;

}

void ONavLabel::setTrianglePosition(const ONavLabel::TrianglePosition &trianglePosition)
{
    this->trianglePosition = trianglePosition;

}

void ONavLabel::setTriangleColor(const QColor &triangleColor)
{
    this->triangleColor = triangleColor;

}

