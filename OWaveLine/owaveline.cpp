#include "owaveline.h"
#include <QPainter>
#include <QDebug>
OWaveLine::OWaveLine(QWidget *parent) :
    QWidget(parent)
{
}
void OWaveLine::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制线条
    drawLine(&painter);
}

void OWaveLine::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPoint(0, 0), QPoint(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void OWaveLine::drawLine(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(lineColor, 2));

    int count = dataVec.count();
    double increment = (double)width() / count;
    double initX = 0;
    QVector<QPointF> pointVec;

    for (int i = 0; i < count - 1; i++) {
        double currentValue = dataVec.at(i);
        double y1 = height() - (double)height() / maxValue * currentValue;
        double nextValue = dataVec.at(i + 1);
        double y2 = height() - (double)height() / maxValue * nextValue;
        QPointF point1(initX, y1);
        QPointF point2(initX + increment, y2);
        initX += increment;

        pointVec.append(point1);
        pointVec.append(point2);
    }

    painter->drawLines(pointVec);
    painter->restore();
}

void OWaveLine::updateData()
{
    update();
}

int OWaveLine::getMaxValue() const
{
    return maxValue;
}

int OWaveLine::getStep() const
{
    return step;
}

int OWaveLine::getSpace() const
{
    return space;
}

QColor OWaveLine::getBgColorStart() const
{
    return bgColorStart;
}

QColor OWaveLine::getBgColorEnd() const
{
    return bgColorEnd;
}

QColor OWaveLine::getLineColor() const
{
    return lineColor;
}

QSize OWaveLine::sizeHint() const
{
    return QWidget::sizeHint();
}

QSize OWaveLine::minimumSizeHint() const
{
    return QWidget::minimumSizeHint();
}

void OWaveLine::setData(const QVector<int> &dataVec)
{
    qDebug()<<"setData";
    this->dataVec = dataVec;
}

void OWaveLine::setMaxValue(int maxValue)
{
    this->maxValue = maxValue;
}

void OWaveLine::setStep(int step)
{
    this->step = step;
}

void OWaveLine::setSpace(int space)
{
    this->space = space;
}

void OWaveLine::setBgColorStart(const QColor &bgColorStart)
{
    this->bgColorStart = bgColorStart;
}

void OWaveLine::setBgColorEnd(const QColor &bgColorEnd)
{
    this->bgColorEnd = bgColorEnd;
}

void OWaveLine::setLineColor(const QColor &lineColor)
{
    this->lineColor = lineColor;
}

