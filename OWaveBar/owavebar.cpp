#include "owavebar.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>
OWaveBar::OWaveBar(QWidget *parent) :
    QWidget(parent)
{
    barTimer = new QTimer(this);
    headTimer = new QTimer(this);


    connect(barTimer,SIGNAL(timeout()),this,SLOT(updateBar()));
    connect(headTimer,SIGNAL(timeout()),this,SLOT(updateHead()));
    barTimer->setInterval(20);
    headTimer->setInterval(50);


}

OWaveBar::~OWaveBar()
{

}

void OWaveBar::resizeEvent(QResizeEvent *)
{
    qDebug()<<"resizeEvent";

    //int minValue;                   //最小值 需要转换
    //int maxValue;                   //最大值 需要转换
    //int value;                      //目标值 需要转换

    //double step;                    //步长 需要转换


    stepToPerPix = maxValue / step;//总步数
    stepToPerPix = height() / stepToPerPix ;//步数对应的像素值

    if(stepToPerPix < 0.001)
    {
        stepToPerPix = 0.001;
    }

    //更新headY、barY的坐标值

    if(barTimer->isActive())
    {
        //todo...
        //barY = height();

    }
    else
    {
        barY = height();

    }

    if(headTimer->isActive())
    {
        //todo...


    }
    else
    {
        headY = height() - headHeight;

    }



}
void OWaveBar::paintEvent(QPaintEvent *)
{
    //qDebug()<<"OWaveBar barY" << this->geometry().height() << this->geometry().width();

    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制渐变背景
    drawBg(&painter);
    //绘制柱状条块
    drawBar(&painter);
    //绘制顶部条块
    drawHead(&painter);
}

void OWaveBar::drawBg(QPainter *painter)
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

void OWaveBar::drawBar(QPainter *painter)
{
    painter->save();
    //qDebug()<<"OWaveBar Y" << height() - space;

    QRectF barRect(QPointF(space, barY), QPointF(width() - space, height() - space));
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor);
    painter->drawRect(barRect);
    painter->restore();
}

void OWaveBar::drawHead(QPainter *painter)
{
    painter->save();
    QRectF headRect(QPointF(space, headY), QPointF(width() - space, headY - headHeight));
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor);
    painter->drawRect(headRect);
    painter->restore();
}

void OWaveBar::updateBar()
{
    //stepToPerPix
    //barY += step;
    barY += stepToPerPix;

    //超过底部则停止
    int bottomY = height() - space - headHeight;

    if (barY >= bottomY) {
        if (barTimer->isActive()) {
            barTimer->stop();
        }

        barY = bottomY;
    }

    this->update();
}

void OWaveBar::updateHead()
{
    headY += stepToPerPix;

    //超过底部则停止
    int bottomY = height() - space;

    if (headY >= bottomY) {
        if (headTimer->isActive()) {
            headTimer->stop();
        }

        headY = bottomY;
    }

    this->update();
}

int OWaveBar::getMinValue() const
{
    return minValue;
}

int OWaveBar::getMaxValue() const
{
    return maxValue;
}

int OWaveBar::getValue() const
{
    return value;
}

double OWaveBar::getStep() const
{
    return step;
}

int OWaveBar::getSpace() const
{
    return space;
}

int OWaveBar::getHeadHeight() const
{
    return headHeight;
}

QColor OWaveBar::getBgColorStart() const
{
    return bgColorStart;
}

QColor OWaveBar::getBgColorEnd() const
{
    return bgColorEnd;
}

QColor OWaveBar::getBarColor() const
{
    return barColor;
}

QSize OWaveBar::sizeHint() const
{
    return QWidget::sizeHint();
}

QSize OWaveBar::minimumSizeHint() const
{
    return QWidget::minimumSizeHint();
}

void OWaveBar::setRange(int minValue, int maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;

}

void OWaveBar::setMinValue(int minValue)
{
    this->minValue = minValue;

}

void OWaveBar::setMaxValue(int maxValue)
{
    this->maxValue = maxValue;

}

void OWaveBar::setValue(int value)
{
    if(value < minValue || value > maxValue)
        return;


    this->value = value;

    barY = height() * (double)((maxValue - value)/(double)maxValue);


    if((headY/height()) > ((maxValue - value) / (double)maxValue))
    {
        headY = barY -  headHeight;
    }

    qDebug()<<"setValue"<<barY;


}

void OWaveBar::setStep(double step)
{
    this->step = step;

}

void OWaveBar::setSpace(int space)
{
    this->space = space;

}

void OWaveBar::setHeadHeight(int headHeight)
{
    this->headHeight = headHeight;

}

void OWaveBar::setBgColorStart(const QColor &bgColorStart)
{
    this->bgColorStart = bgColorStart;

}

void OWaveBar::setBgColorEnd(const QColor &bgColorEnd)
{
    this->bgColorEnd = bgColorEnd;

}

void OWaveBar::setBarColor(const QColor &barColor)
{
    this->barColor = barColor;

}

void OWaveBar::start()
{

    barTimer->start();
    headTimer->start();
}

