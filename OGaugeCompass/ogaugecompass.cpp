#include "ogaugecompass.h"
#include <QPainter>
#include <QTimer>

OGaugeCompass::OGaugeCompass(QWidget *parent) :
    QWidget(parent)
{
    value = 2;
    precision = 1;
    animation = true;
    animationStep = 1;

    crownColorStart = Qt::red;
    crownColorEnd = Qt::magenta;

    bgColorStart = Qt::yellow;
    bgColorEnd = Qt::cyan;

    darkColor = Qt::darkGray;
    lightColor = Qt::lightGray;

    textColor = Qt::white;

    northPointerColor = Qt::green;
    southPointerColor = Qt::blue;

    centerColorStart = Qt::black;
    centerColorEnd = Qt::white;



}
void OGaugeCompass::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制外边框圆
    drawCrownCircle(&painter);
    //绘制背景圆
    drawBgCircle(&painter);
    //绘制刻度
    drawScale(&painter);
    //绘制东南西北标识
    drawScaleNum(&painter);
    //绘制覆盖圆外圆
    drawCoverOuterCircle(&painter);
    //绘制覆盖圆内圆
    drawCoverInnerCircle(&painter);
    //绘制覆盖圆中心圆
    drawCoverCenterCircle(&painter);
    //绘制南北指针
    drawPointer(&painter);
    //绘制中心圆
    drawCenterCircle(&painter);
    //绘制当前值
    drawValue(&painter);
}

void OGaugeCompass::drawCrownCircle(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, crownColorStart);
    lineGradient.setColorAt(1, crownColorEnd);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeCompass::drawBgCircle(QPainter *painter)
{
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, bgColorStart);
    lineGradient.setColorAt(1, bgColorEnd);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeCompass::drawScale(QPainter *painter)
{
    int radius = 85;
    painter->save();

    //总共8格,4格为NESW字母,4格为线条
    int steps = 8;
    double angleStep = 360.0 / steps;

    QPen pen;
    pen.setColor(foreground);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(4);
    painter->setPen(pen);

    //%2整数部分绘制NESW字母,其余绘制线条刻度
    for (int i = 0; i <= steps; i++) {
        if (i % 2 != 0) {
            painter->drawLine(0, radius - 10, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void OGaugeCompass::drawScaleNum(QPainter *painter)
{
    int radius = 88;
    painter->save();
    painter->setPen(foreground);

    QFont font;
    font.setPixelSize(15);
    font.setBold(true);
    painter->setFont(font);

    QRect textRect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignTop | Qt::AlignHCenter, "N");
    painter->drawText(textRect, Qt::AlignBottom | Qt::AlignHCenter, "S");

    radius -= 2;
    textRect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, "W");

    radius -= 2;
    textRect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, "E");

    painter->restore();
}

void OGaugeCompass::drawCoverOuterCircle(QPainter *painter)
{
    int radius = 68;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, lightColor);
    lineGradient.setColorAt(1, darkColor);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeCompass::drawCoverInnerCircle(QPainter *painter)
{
    int radius = 60;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, darkColor);
    lineGradient.setColorAt(1, lightColor);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeCompass::drawCoverCenterCircle(QPainter *painter)
{
    int radius = 15;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setOpacity(0.8);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, lightColor);
    lineGradient.setColorAt(1, darkColor);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeCompass::drawPointer(QPainter *painter)
{
    int radius = 75;

    QPolygon pts;

    painter->save();
    painter->setOpacity(0.7);
    painter->setPen(Qt::NoPen);
    painter->setBrush(northPointerColor);
    pts.setPoints(3, -10, 0, 10, 0, 0, radius);
    painter->rotate(currentValue + 180);
    painter->drawConvexPolygon(pts);
    painter->restore();

    painter->save();
    painter->setOpacity(0.7);
    painter->setPen(Qt::NoPen);
    painter->setBrush(southPointerColor);
    pts.setPoints(3, -10, 0, 10, 0, 0, radius);
    painter->rotate(currentValue);
    painter->drawConvexPolygon(pts);
    painter->restore();
}

void OGaugeCompass::drawCenterCircle(QPainter *painter)
{
    int radius = 12;
    painter->save();
    painter->setOpacity(1.0);
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, centerColorStart);
    lineGradient.setColorAt(1, centerColorEnd);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeCompass::drawValue(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(11);
    font.setBold(true);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)value, 0, 'f', precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);
    painter->restore();
}

void OGaugeCompass::updateValue()
{

}

double OGaugeCompass::getValue() const
{
    return value;
}

int OGaugeCompass::getPrecision() const
{
    return precision;
}

bool OGaugeCompass::getAnimation() const
{
    return animation;
}

double OGaugeCompass::getAnimationStep() const
{
    return animationStep;
}

QColor OGaugeCompass::getCrownColorStart() const
{
    return crownColorStart;
}

QColor OGaugeCompass::getCrownColorEnd() const
{
    return crownColorEnd;
}

QColor OGaugeCompass::getBgColorStart() const
{
    return bgColorStart;
}

QColor OGaugeCompass::getBgColorEnd() const
{
    return bgColorEnd;
}

QColor OGaugeCompass::getDarkColor() const
{
    return darkColor;
}

QColor OGaugeCompass::getLightColor() const
{
    return lightColor;

}

QColor OGaugeCompass::getForeground() const
{
    return foreground;
}

QColor OGaugeCompass::getTextColor() const
{
    return textColor;
}

QColor OGaugeCompass::getNorthPointerColor() const
{
    return northPointerColor;
}

QColor OGaugeCompass::getSouthPointerColor() const
{
    return southPointerColor;
}

QColor OGaugeCompass::getCenterColorStart() const
{
    return centerColorStart;
}

QColor OGaugeCompass::getCenterColorEnd() const
{
    return centerColorEnd;
}

void OGaugeCompass::setValue(double value)
{
    this->value = value;
    this->currentValue = value;
    update();
}

void OGaugeCompass::setValue(int value)
{
    this->value = value;
    this->currentValue = value;
    update();

}

void OGaugeCompass::setPrecision(int precision)
{
    this->precision = precision;

}

void OGaugeCompass::setAnimation(bool animation)
{
    this->animation = animation;

}

void OGaugeCompass::setAnimationStep(double animationStep)
{
    this->animationStep = animationStep;

}

void OGaugeCompass::setCrownColorStart(const QColor &crownColorStart)
{
    this->crownColorStart = crownColorStart;

}

void OGaugeCompass::setCrownColorEnd(const QColor &crownColorEnd)
{
    this->crownColorEnd = crownColorEnd;

}

void OGaugeCompass::setBgColorStart(const QColor &bgColorStart)
{
    this->bgColorStart = bgColorStart;

}

void OGaugeCompass::setBgColorEnd(const QColor &bgColorEnd)
{
    this->bgColorEnd = bgColorEnd;

}

void OGaugeCompass::setDarkColor(const QColor &darkColor)
{
    this->darkColor = darkColor;

}

void OGaugeCompass::setLightColor(const QColor &lightColor)
{
    this->lightColor = lightColor;

}

void OGaugeCompass::setForeground(const QColor &foreground)
{
    this->foreground = foreground;

}

void OGaugeCompass::setTextColor(const QColor &textColor)
{
    this->textColor = textColor;

}

void OGaugeCompass::setNorthPointerColor(const QColor &northPointerColor)
{
    this->northPointerColor = northPointerColor;

}

void OGaugeCompass::setSouthPointerColor(const QColor &southPointerColor)
{
    this->southPointerColor = southPointerColor;

}

void OGaugeCompass::setCenterColorStart(const QColor &centerColorStart)
{
    this->centerColorStart = centerColorStart;

}

void OGaugeCompass::setCenterColorEnd(const QColor &centerColorEnd)
{
    this->centerColorEnd = centerColorEnd;

}




