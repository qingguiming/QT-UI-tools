#include "owavedouble.h"
#include <QPainter>
#include <QTimer>
OWaveDouble::OWaveDouble(QWidget *parent) :
    QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;

    step = 1;
    space = 1;
    currentValue = 0.0;
    timer = new QTimer(this);
    timer->setInterval(40);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateValue()));
}

OWaveDouble::~OWaveDouble()
{

}

void OWaveDouble::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制渐变背景
    drawBg(&painter);
    //绘制柱状条块
    drawBar(&painter);
}

void OWaveDouble::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void OWaveDouble::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor);

    //找到中心点Y轴坐标
    double centerY = (double) height() / 2;
    //每一格递增量
    double increment = (double)(height() - 2 * space) / (maxValue - minValue);
    //找到当前值的起始和结束Y轴坐标 上下两半所以 /2
    double startY = centerY - (currentValue / 2) * increment;
    double endY = centerY + (currentValue / 2) * increment;
    QRectF barRect(QPointF(space, startY), QPointF(width() - space, endY));
    painter->drawRect(barRect);
    painter->restore();
}


void OWaveDouble::updateValue()
{

    currentValue += step;

    if(currentValue > maxValue)
    {
        currentValue = maxValue;

        if(timer->isActive())
        {
            timer->stop();
        }
    }

    if(currentValue < minValue)
    {
        currentValue = minValue;
        if(timer->isActive())
        {
            timer->stop();
        }
    }

    update();


}

void OWaveDouble::stop()
{
    timer->stop();

}

void OWaveDouble::start()
{
    timer->start();

}

int OWaveDouble::getMinValue() const
{
    return minValue;
}

int OWaveDouble::getMaxValue() const
{
    return maxValue;
}

int OWaveDouble::getValue() const
{
    return value;
}

int OWaveDouble::getStep() const
{
    return step;
}

int OWaveDouble::getSpace() const
{
    return space;
}

QColor OWaveDouble::getBgColorStart() const
{
    return bgColorStart;
}

QColor OWaveDouble::getBgColorEnd() const
{
    return bgColorEnd;
}

QColor OWaveDouble::getBarColor() const
{
    return barColor;
}

QSize OWaveDouble::sizeHint() const
{
    return QWidget::sizeHint();
}

QSize OWaveDouble::minimumSizeHint() const
{
    return QWidget::minimumSizeHint();
}

void OWaveDouble::setRange(int minValue, int maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;

}

void OWaveDouble::setMinValue(int minValue)
{
    this->minValue = minValue;

}

void OWaveDouble::setMaxValue(int maxValue)
{
    this->maxValue = maxValue;

}

void OWaveDouble::setValue(int value)
{
    this->value = value;
    currentValue = value;

}

void OWaveDouble::setStep(int step)
{
    this->step = step;

}

void OWaveDouble::setSpace(int space)
{
    this->space = space;

}

void OWaveDouble::setBgColorStart(const QColor &bgColorStart)
{
    this->bgColorStart = bgColorStart;

}

void OWaveDouble::setBgColorEnd(const QColor &bgColorEnd)
{
    this->bgColorEnd = bgColorEnd;

}

void OWaveDouble::setBarColor(const QColor &barColor)
{
    this->barColor = barColor;

}
