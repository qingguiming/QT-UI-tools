#include "oprogressring.h"
#include <QPainter>

OProgressRing::OProgressRing(QWidget *parent) :
    QWidget(parent)
{

    minValue = 0;
    maxValue = 100;
    value = 15;
    precision = 0;

    clockWise = true;
    showPercent = true;

    alarmMode = 1;
    startAngle = 60;

    ringPadding = 60;
    ringWidth = 30;

    animation  = true;
    animationStep = 1;

    bgColor = Qt::yellow;
    textColor = Qt::white;

    ringColor = Qt::green;
    ringBgColor = Qt::cyan;

    circleColor = Qt::lightGray;

    ringValue1 = 30;
    ringValue2 = 60;
    ringValue3 = 80;

    ringColor1 = Qt::gray;
    ringColor2 = Qt::darkRed;
    ringColor3 = Qt::darkYellow;

    currentValue = 15;


}
void OProgressRing::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制背景
    drawBg(&painter);
    //绘制进度
    drawRing(&painter);

    //绘制间隔,重新绘制一个圆遮住,产生间距效果
    if (ringPadding > 0) {
        drawPadding(&painter);
    }

    //绘制中间圆
    drawCircle(&painter);
    //绘制当前值
    drawValue(&painter);
}

void OProgressRing::drawBg(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    //这里有个技巧,如果没有间距则设置成圆环的背景色
    painter->setBrush(ringPadding == 0 ? ringBgColor : bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OProgressRing::drawRing(QPainter *painter)
{
    int radius = 99 - ringPadding;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(ringColor);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0;
    double angleCurrent = angleAll * ((currentValue - minValue) / (maxValue - minValue));
    double angleOther = angleAll - angleCurrent;

    //如果逆时针
    if (!clockWise) {
        angleCurrent = -angleCurrent;
        angleOther = -angleOther;
    }

    //动态设置当前进度颜色
    QColor color = ringColor;
    if (alarmMode == 1) {
        if (currentValue >= ringValue3) {
            color = ringColor3;
        } else if (currentValue >= ringValue2) {
            color = ringColor2;
        } else {
            color = ringColor1;
        }
    } else if (alarmMode == 2) {
        if (currentValue <= ringValue1) {
            color = ringColor1;
        } else if (currentValue <= ringValue2) {
            color = ringColor2;
        } else {
            color = ringColor3;
        }
    }

    //绘制当前值饼圆
    painter->setBrush(color);
    painter->drawPie(rect, (startAngle - angleCurrent) * 16, angleCurrent * 16);

    //绘制剩余值饼圆
    painter->setBrush(ringBgColor);
    painter->drawPie(rect, (startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void OProgressRing::drawPadding(QPainter *painter)
{
    int radius = 99 - ringWidth - ringPadding;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OProgressRing::drawCircle(QPainter *painter)
{
    //文字的区域要减去进度的宽度及间距
    int radius = 99 - ringWidth - (ringPadding * 2);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(circleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OProgressRing::drawValue(QPainter *painter)
{
    //文字的区域要减去进度的宽度及间距
    int radius = 99 - ringWidth - (ringPadding * 2);
    painter->save();
    painter->setPen(textColor);

    QFont font;
    int fontSize = radius - (showPercent ? 20 : 6);
    font.setPixelSize(fontSize);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue;
    if (showPercent) {
        double percent = (currentValue * 100) / (maxValue - minValue);
        strValue = QString("%1%").arg(percent, 0, 'f', precision);
    } else {
        strValue = QString("%1").arg(currentValue, 0, 'f', precision);
    }

    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void OProgressRing::updateValue()
{

}

double OProgressRing::getMinValue() const
{
    return minValue;
}

double OProgressRing::getMaxValue() const
{
    return maxValue;
}

double OProgressRing::getValue() const
{
    return value;
}

int OProgressRing::getPrecision() const
{
    return precision;
}

bool OProgressRing::getClockWise() const
{
    return clockWise;
}

bool OProgressRing::getShowPercent() const
{
    return showPercent;
}

int OProgressRing::getAlarmMode() const
{
    return alarmMode;
}

int OProgressRing::getStartAngle() const
{
    return startAngle;
}

int OProgressRing::getRingPadding() const
{
    return ringPadding;
}

int OProgressRing::getRingWidth() const
{
    return ringWidth;
}

bool OProgressRing::getAnimation() const
{
    return animation;
}

double OProgressRing::getAnimationStep() const
{
    return animationStep;
}

QColor OProgressRing::getBgColor() const
{
    return bgColor;
}

QColor OProgressRing::getTextColor() const
{
    return textColor;
}

QColor OProgressRing::getRingColor() const
{
    return ringColor;
}

QColor OProgressRing::getRingBgColor() const
{
    return ringBgColor;
}

QColor OProgressRing::getCircleColor() const
{
    return circleColor;
}

int OProgressRing::getRingValue1() const
{
    return ringValue1;
}

int OProgressRing::getRingValue2() const
{
    return ringValue2;
}

int OProgressRing::getRingValue3() const
{
    return ringValue3;
}

QColor OProgressRing::getRingColor1() const
{
    return ringColor1;
}

QColor OProgressRing::getRingColor2() const
{
    return ringColor2;
}

QColor OProgressRing::getRingColor3() const
{
    return ringColor2;
}

void OProgressRing::setRange(double minValue, double maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}

void OProgressRing::setRange(int minValue, int maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}

void OProgressRing::setMinValue(double minValue)
{
    this->minValue = minValue;

}

void OProgressRing::setMaxValue(double maxValue)
{
    this->maxValue = maxValue;

}

void OProgressRing::setValue(double value)
{
    if(value < minValue) value = minValue;
    if(value > maxValue) value = maxValue;

    this->value = value;
    this->currentValue = value;
    update();


}

void OProgressRing::setValue(int value)
{
    if(value < minValue) value = minValue;
    if(value > maxValue) value = maxValue;

    this->value = value;
    this->currentValue = value;
    update();
}

void OProgressRing::setPrecision(int precision)
{
    this->precision = precision;

}

void OProgressRing::setClockWise(bool clockWise)
{
    this->clockWise = clockWise;

}

void OProgressRing::setShowPercent(bool showPercent)
{
    this->showPercent = showPercent;

}

void OProgressRing::setAlarmMode(int alarmMode)
{
    this->alarmMode = alarmMode;

}

void OProgressRing::setStartAngle(int startAngle)
{
    this->startAngle = startAngle;

}

void OProgressRing::setRingPadding(int ringPadding)
{
    this->ringPadding = ringPadding;

}

void OProgressRing::setRingWidth(int ringWidth)
{
    this->ringWidth = ringWidth;

}

void OProgressRing::setAnimation(bool animation)
{
    this->animation = animation;

}

void OProgressRing::setAnimationStep(double animationStep)
{
    this->animationStep = animationStep;

}

void OProgressRing::setBgColor(const QColor &bgColor)
{
    this->bgColor = bgColor;

}

void OProgressRing::setTextColor(const QColor &textColor)
{
    this->textColor = textColor;

}

void OProgressRing::setRingColor(const QColor &ringColor)
{
    this->ringColor = ringColor;

}

void OProgressRing::setRingBgColor(const QColor &ringBgColor)
{
    this->ringBgColor = ringBgColor;

}

void OProgressRing::setCircleColor(const QColor &circleColor)
{
    this->circleColor = circleColor;

}

void OProgressRing::setRingValue1(int ringValue1)
{
    this->ringValue1 = ringValue1;

}

void OProgressRing::setRingValue2(int ringValue2)
{
    this->ringValue2 = ringValue2;

}

void OProgressRing::setRingValue3(int ringValue3)
{
    this->ringValue3 = ringValue3;

}

void OProgressRing::setRingColor1(const QColor &ringColor1)
{
    this->ringColor1 = ringColor1;

}

void OProgressRing::setRingColor2(const QColor &ringColor2)
{
    this->ringColor2 = ringColor2;

}

void OProgressRing::setRingColor3(const QColor &ringColor3)
{
    this->ringColor3 = ringColor3;

}

