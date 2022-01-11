#include "obattery.h"
#include <QPainter>

OBattery::OBattery(QWidget *parent) :
    QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 30;
    alarmValue = 20;
    step = 1;
    borderRadius = 10;
    bgRadius = 10;
    headRadius = 10;

    borderColorStart = Qt::white;
    borderColorEnd = Qt::black;

    alarmColorStart = Qt::red;
    alarmColorEnd = Qt::darkRed;

    normalColorStart = Qt::green;
    normalColorEnd = Qt::darkGreen;

    isForward = false;
    currentValue = 30;
    batteryRect = QRectF(15,15,60,200);


}

OBattery::~OBattery()
{

}
void OBattery::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制边框
    drawBorder(&painter);
    //绘制背景
    drawBg(&painter);
    //绘制头部
    drawHead(&painter);
}

void OBattery::drawBorder(QPainter *painter)
{
    painter->save();

    double headWidth = width() / 10;
    double batteryWidth = width() - headWidth;

    //绘制电池边框
    QPointF topLeft(5, 5);
    QPointF bottomRight(batteryWidth, height() - 5);
    batteryRect = QRectF(topLeft, bottomRight);

    painter->setPen(QPen(borderColorStart, 5));
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(batteryRect, borderRadius, borderRadius);

    painter->restore();
}

void OBattery::drawBg(QPainter *painter)
{
    painter->save();

    QLinearGradient batteryGradient(QPointF(0, 0), QPointF(0, height()));
    if (currentValue <= alarmValue) {
        batteryGradient.setColorAt(0.0, alarmColorStart);
        batteryGradient.setColorAt(1.0, alarmColorEnd);
    } else {
        batteryGradient.setColorAt(0.0, normalColorStart);
        batteryGradient.setColorAt(1.0, normalColorEnd);
    }

    int margin = qMin(width(), height()) / 20;
    double unit = (batteryRect.width() - (margin * 2)) / 100;
    double width = currentValue * unit;
    QPointF topLeft(batteryRect.topLeft().x() + margin, batteryRect.topLeft().y() + margin);
    QPointF bottomRight(width + margin + 5, batteryRect.bottomRight().y() - margin);
    QRectF rect(topLeft, bottomRight);

    painter->setPen(Qt::NoPen);
    painter->setBrush(batteryGradient);
    painter->drawRoundedRect(rect, bgRadius, bgRadius);

    painter->restore();
}

void OBattery::drawHead(QPainter *painter)
{
    painter->save();

    QPointF headRectTopLeft(batteryRect.topRight().x(), height() / 3);
    QPointF headRectBottomRight(width(), height() - height() / 3);
    QRectF headRect(headRectTopLeft, headRectBottomRight);

    QLinearGradient headRectGradient(headRect.topLeft(), headRect.bottomLeft());
    headRectGradient.setColorAt(0.0, borderColorStart);
    headRectGradient.setColorAt(1.0, borderColorEnd);

    painter->setPen(Qt::NoPen);
    painter->setBrush(headRectGradient);
    painter->drawRoundedRect(headRect, headRadius, headRadius);

    painter->restore();
}

void OBattery::updateValue()
{

}

double OBattery::getMinValue() const
{
    return minValue;
}

double OBattery::getMaxValue() const
{
    return maxValue;
}

double OBattery::getValue() const
{
    return value;
}

double OBattery::getAlarmValue() const
{
    return alarmValue;
}

double OBattery::getStep() const
{
    return step;
}

int OBattery::getBorderRadius() const
{
    return borderRadius;
}

int OBattery::getBgRadius() const
{
    return bgRadius;
}

int OBattery::getHeadRadius() const
{
    return headRadius;
}

QColor OBattery::getBorderColorStart() const
{
    return borderColorStart;
}

QColor OBattery::getBorderColorEnd() const
{
    return borderColorEnd;
}

QColor OBattery::getAlarmColorStart() const
{
    return alarmColorStart;
}

QColor OBattery::getAlarmColorEnd() const
{
    return alarmColorEnd;
}

QColor OBattery::getNormalColorStart() const
{
    return normalColorStart;
}

QColor OBattery::getNormalColorEnd() const
{
    return normalColorEnd;
}

QSize OBattery::sizeHint() const
{
    return QSize(100,250);
}

QSize OBattery::minimumSizeHint() const
{
    return QSize(100,250);

}

void OBattery::setRange(double minValue, double maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;

}

void OBattery::setRange(int minValue, int maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}

void OBattery::setMinValue(double minValue)
{
    this->minValue = minValue;

}

void OBattery::setMaxValue(double maxValue)
{
    this->maxValue = maxValue;

}

void OBattery::setValue(double value)
{
    if(value < minValue) value = minValue;
    if(value > maxValue) value = maxValue;

    this->value = value;
    this->currentValue = value;
    update();

}

void OBattery::setValue(int value)
{
    if(value < minValue) value = minValue;
    if(value > maxValue) value = maxValue;

    this->value = value;
    this->currentValue = value;
    update();
}

void OBattery::setAlarmValue(double alarmValue)
{
    this->alarmValue = alarmValue;
    update();


}

void OBattery::setAlarmValue(int alarmValue)
{
    this->alarmValue = alarmValue;
    update();


}

void OBattery::setStep(double step)
{
    this->step = step;

}

void OBattery::setStep(int step)
{
    this->step = step;

}

void OBattery::setBorderRadius(int borderRadius)
{
    this->borderRadius = borderRadius;

}

void OBattery::setBgRadius(int bgRadius)
{
    this->bgRadius = bgRadius;

}

void OBattery::setHeadRadius(int headRadius)
{
    this->headRadius = headRadius;

}

void OBattery::setBorderColorStart(const QColor &borderColorStart)
{
    this->borderColorStart = borderColorStart;

}

void OBattery::setBorderColorEnd(const QColor &borderColorEnd)
{
    this->borderColorEnd = borderColorEnd;

}

void OBattery::setAlarmColorStart(const QColor &alarmColorStart)
{
    this->alarmColorStart = alarmColorStart;

}

void OBattery::setAlarmColorEnd(const QColor &alarmColorEnd)
{
    this->alarmColorEnd = alarmColorEnd;

}

void OBattery::setNormalColorStart(const QColor &normalColorStart)
{
    this->normalColorStart = normalColorStart;

}

void OBattery::setNormalColorEnd(const QColor &normalColorEnd)
{
    this->normalColorEnd = normalColorEnd;

}

