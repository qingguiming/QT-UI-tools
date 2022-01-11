#include "ogaugespeed.h"
#include <QLCDNumber>
#include <QPainter>
#include <QtMath>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QDebug>

OGaugeSpeed::OGaugeSpeed(QWidget *parent) :
    QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 10;
    precision = 1;

    scaleMajor = 5;
    scaleMinor = 1;
    startAngle = 30;
    endAngle= 150;

    animation = true;
    animationStep = 2;

    ringWidth = 20;

    ringStartPercent = 30;
    ringMidPercent = 40;
    ringEndPercent = 30;

    ringColorStart = Qt::green;
    ringMidPercent = Qt::blue;
    ringEndPercent = Qt::red;

    pointerColor = Qt::gray;
    textColor = Qt::white;

    reverse = true;
    currentValue = value;

    lcd = new QLCDNumber(this);
    // 设置能显示的位数
    lcd->setDigitCount(4);
    // 设置显示的模式为十进制
    lcd->setMode(QLCDNumber::Dec);
    // 设置显示外观
    lcd->setSegmentStyle(QLCDNumber::Flat);

    QVBoxLayout* vBoxLayout = new QVBoxLayout();
//    QSpacerItem* item = new QSpacerItem();
//    vBoxLayout->addSpacerItem(item);
    vBoxLayout->addStretch(1);
    vBoxLayout->addWidget(lcd);
    setLayout(vBoxLayout);
}

void OGaugeSpeed::resizeEvent(QResizeEvent *)
{

}

void OGaugeSpeed::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    int w = width() / 2;
    int h = height() / 2;

    painter.translate(w,h);


    drawRing(&painter);
    drawScale(&painter);
    drawScaleNum(&painter);
    drawPointer(&painter);



}
void OGaugeSpeed::drawRing(QPainter *painter)
{
    int nWidth = width();
    int nHeight = height();

    int radius = qMin(nWidth,nHeight) / 2;
    painter->save();

    QPen pen;
    pen.setCapStyle(Qt::FlatCap);
    pen.setWidthF(ringWidth);

    radius = radius - ringWidth;
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);

    //计算总范围角度,根据占比例自动计算三色圆环范围角度
    double angleAll = endAngle - startAngle;
    double angleStart = angleAll * (double)ringStartPercent / 100;
    double angleMid = angleAll * (double)ringMidPercent / 100;
    double angleEnd = angleAll * (double)ringEndPercent / 100;

    int tempStartAngle = 270 - startAngle;
    qDebug()<<tempStartAngle << angleStart << angleMid << angleEnd ;

    //绘制第一圆环
    pen.setColor(ringColorStart);
    painter->setPen(pen);
    painter->drawArc(rect, (tempStartAngle - angleStart) * 16, angleStart * 16);

    //绘制第二圆环
    pen.setColor(ringColorMid);
    painter->setPen(pen);
    painter->drawArc(rect, (tempStartAngle - angleStart - angleMid) * 16, angleMid * 16);

    //绘制第三圆环
    pen.setColor(ringColorEnd);
    painter->setPen(pen);
    painter->drawArc(rect, (tempStartAngle - angleStart - angleMid - angleEnd) * 16, angleEnd * 16);

    painter->restore();
}

void OGaugeSpeed::drawScale(QPainter *painter)
{
    //int radius = 94;

    int nWidth = width();
    int nHeight = height();
    int radius = qMin(nWidth,nHeight) / 2;
    radius = radius - ringWidth*2;


    painter->save();

    QPen pen;
    pen.setColor(textColor);
    pen.setCapStyle(Qt::RoundCap);

    painter->rotate(startAngle);
    int steps = (scaleMajor * scaleMinor);
    double angleStep = (endAngle - startAngle) / steps;

    //计算圆环对应大刻度范围索引
    int indexStart = steps * (double)ringStartPercent / 100 + 1;
    int indexMid = steps * (double)ringMidPercent / 100 - 1;
    int indexEnd = steps * (double)ringEndPercent / 100 + 1;
    int index = 0;

    for (int i = 0; i <= steps; i++) {
        if (i % scaleMinor == 0) {
            qDebug()<<index << "----" << indexStart <<  indexMid << indexEnd << scaleMajor << scaleMinor;
            //根据所在圆环范围切换颜色
            if (i < indexStart) {
                pen.setColor(ringColorStart);
            } else if (i < (indexStart + indexMid)) {
                pen.setColor(ringColorMid);
            } else if (i < (indexStart + indexMid + indexEnd)) {
                pen.setColor(ringColorEnd);
            }

            index++;

            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 13, 0, radius);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void OGaugeSpeed::drawScaleNum(QPainter *painter)
{
    //int radius = 70;

    int nWidth = width();
    int nHeight = height();
    int radius = qMin(nWidth,nHeight) / 2;
    radius = radius - 2*ringWidth / 2;

    painter->save();
    painter->setPen(textColor);

    double startRad = (270 - startAngle) * (M_PI / 180);
    double deltaRad = (endAngle - startAngle) * (M_PI / 180) / scaleMajor;

    for (int i = 0; i <= scaleMajor; i++) {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 1.0 * i * ((maxValue - minValue) / scaleMajor) + minValue;

        QString strValue = QString("%1M").arg((double)value, 0, 'f', 0);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void OGaugeSpeed::drawPointer(QPainter *painter)
{
    int nWidth = width();
    int nHeight = height();
    int radius = qMin(nWidth,nHeight) / 2;
    radius = radius - ringWidth  - 25;

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(4, -5, 0, 0, -8, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (endAngle - startAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void OGaugeSpeed::drawValue(QPainter *painter)
{

}

void OGaugeSpeed::updateValue()
{

}

double OGaugeSpeed::getMinValue() const
{
    return minValue;
}

double OGaugeSpeed::getMaxValue() const
{
    return maxValue;
}

double OGaugeSpeed::getValue() const
{
    return value;
}

int OGaugeSpeed::getPrecision() const
{
    return precision;
}

int OGaugeSpeed::getScaleMajor() const
{
    return scaleMajor;
}

int OGaugeSpeed::getScaleMinor() const
{
    return scaleMinor;
}

int OGaugeSpeed::getStartAngle() const
{
    return startAngle;
}

int OGaugeSpeed::getEndAngle() const
{
    return endAngle;
}

bool OGaugeSpeed::getAnimation() const
{
    return animation;
}

double OGaugeSpeed::getAnimationStep() const
{
    return animationStep;
}

int OGaugeSpeed::getRingWidth() const
{
    return ringWidth;
}

int OGaugeSpeed::getRingStartPercent() const
{
    return ringStartPercent;
}

int OGaugeSpeed::getRingMidPercent() const
{
    return ringMidPercent;
}

int OGaugeSpeed::getRingEndPercent() const
{
    return ringEndPercent;
}

QColor OGaugeSpeed::getRingColorStart() const
{
    return ringColorStart;
}

QColor OGaugeSpeed::getRingColorMid() const
{
    return ringColorMid;
}

QColor OGaugeSpeed::getRingColorEnd() const
{
    return ringColorEnd;
}

QColor OGaugeSpeed::getPointerColor() const
{
    return pointerColor;
}

QColor OGaugeSpeed::getTextColor() const
{
    return textColor;
}

void OGaugeSpeed::setRange(double minValue, double maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;

}

void OGaugeSpeed::setRange(int minValue, int maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;

}

void OGaugeSpeed::setMinValue(double minValue)
{
    this->minValue = minValue;

}

void OGaugeSpeed::setMaxValue(double maxValue)
{
    this->maxValue = maxValue;

}

void OGaugeSpeed::setValue(double value)
{
    this->value = value;
    this->currentValue = value;
    lcd->display(value);
    update();

}

void OGaugeSpeed::setValue(int value)
{
    this->value = value;
    this->currentValue = value;
    lcd->display(value);
    update();

}

void OGaugeSpeed::setPrecision(int precision)
{
    this->precision = precision;

}

void OGaugeSpeed::setScaleMajor(int scaleMajor)
{
    this->scaleMajor = scaleMajor;

}

void OGaugeSpeed::setScaleMinor(int scaleMinor)
{
    this->scaleMinor = scaleMinor;

}

void OGaugeSpeed::setStartAngle(int startAngle)
{
    this->startAngle = startAngle;

}

void OGaugeSpeed::setEndAngle(int endAngle)
{
    this->endAngle = endAngle;

}

void OGaugeSpeed::setAnimation(bool animation)
{
    this->animation = animation;

}

void OGaugeSpeed::setAnimationStep(double animationStep)
{
    this->animationStep = animationStep;

}

void OGaugeSpeed::setRingWidth(int ringWidth)
{
    this->ringWidth = ringWidth;

}

void OGaugeSpeed::setRingStartPercent(int ringStartPercent)
{
    this->ringStartPercent = ringStartPercent;

}

void OGaugeSpeed::setRingMidPercent(int ringMidPercent)
{
    this->ringMidPercent = ringMidPercent;

}

void OGaugeSpeed::setRingEndPercent(int ringEndPercent)
{
    this->ringEndPercent = ringEndPercent;

}

void OGaugeSpeed::setRingColorStart(const QColor &ringColorStart)
{
    this->ringColorStart = ringColorStart;

}

void OGaugeSpeed::setRingColorMid(const QColor &ringColorMid)
{
    this->ringColorMid = ringColorMid;

}

void OGaugeSpeed::setRingColorEnd(const QColor &ringColorEnd)
{
    this->ringColorEnd = ringColorEnd;

}

void OGaugeSpeed::setPointerColor(const QColor &pointerColor)
{
    this->pointerColor = pointerColor;

}

void OGaugeSpeed::setTextColor(const QColor &textColor)
{
    this->textColor = textColor;

}

