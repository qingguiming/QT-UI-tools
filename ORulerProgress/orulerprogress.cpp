#include "orulerprogress.h"
#include <QPainter>
ORulerProgress::ORulerProgress(QWidget *parent) :
    QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 30;
    precision = 0;
    longStep = 10;
    shortStep = 2;
    rulerTop = true;
    animation = false;
    animationStep = 0;

    bgColor = Qt::gray;
    lineColor = Qt::white;
    progressColor = Qt::blue;
    reverse = false;
    currentValue = 30;

}

void ORulerProgress::mousePressEvent(QMouseEvent *)
{

}

void ORulerProgress::mouseMoveEvent(QMouseEvent *)
{

}

void ORulerProgress::setPressedValue(QPoint pressedPoint)
{

}
void ORulerProgress::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制渐变背景
    drawBg(&painter);
    //绘制进度
    drawProgress(&painter);
    //绘制标尺
    if (rulerTop) {
        drawRulerTop(&painter);
    } else {
        drawRulerBottom(&painter);
    }
}

void ORulerProgress::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);
    painter->setBrush(bgColor);
    painter->drawRect(rect());
    painter->restore();
}

void ORulerProgress::drawProgress(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(progressColor);

    double length = width();
    double increment = length / (maxValue - minValue);
    double initX = (currentValue - minValue) * increment;

    QRect rect(0, 0, initX, height());
    painter->drawRect(rect);
    painter->restore();
}

void ORulerProgress::drawRulerTop(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);

    double initX = 0;

    //绘制横向标尺上部分底部线
    double initTopY = 0;
    QPointF lineTopLeftPot = QPointF(initX, initTopY);
    QPointF lineTopRightPot = QPointF(width() - initX, initTopY);
    painter->drawLine(lineTopLeftPot, lineTopRightPot);

    //绘制上部分及下部分横向标尺刻度
    double length = width();
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 15;
    int shortLineLen = 10;

    //根据范围值绘制刻度值及刻度值 长线条需要移动10像素 短线条需要移动5像素
    for (int i = minValue; i <= maxValue; i = i + shortStep) {
        if (i % longStep == 0) {
            QPointF topPot = QPointF(initX, initTopY);
            QPointF bottomPot = QPointF(initX, initTopY + longLineLen);
            painter->drawLine(topPot, bottomPot);

            //第一个值和最后一个值不要绘制
            if (i == minValue || i == maxValue) {
                initX += increment * shortStep;
                continue;
            }

            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);
            double textWidth = fontMetrics().width(strValue);
            double textHeight = fontMetrics().height();

            QPointF textPot = QPointF(initX - textWidth / 2, initTopY + textHeight + longLineLen);
            painter->drawText(textPot, strValue);
        } else {
            if (i % (longStep / 2) == 0) {
                shortLineLen = 10;
            } else {
                shortLineLen = 6;
            }

            QPointF topPot = QPointF(initX, initTopY);
            QPointF bottomPot = QPointF(initX, initTopY + shortLineLen);
            painter->drawLine(topPot, bottomPot);
        }

        initX += increment * shortStep;
    }

    painter->restore();
}

void ORulerProgress::drawRulerBottom(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);

    double initX = 0;

    //绘制横向标尺下部分底部线
    double initBottomY = height();
    QPointF lineBottomLeftPot = QPointF(initX, initBottomY);
    QPointF lineBottomRightPot = QPointF(width() - initX, initBottomY);
    painter->drawLine(lineBottomLeftPot, lineBottomRightPot);

    //绘制上部分及下部分横向标尺刻度
    double length = width();
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 15;
    int shortLineLen = 10;

    //根据范围值绘制刻度值及刻度值 长线条需要移动10像素 短线条需要移动5像素
    for (int i = minValue; i <= maxValue; i = i + shortStep) {
        if (i % longStep == 0) {
            QPointF topPot = QPointF(initX, initBottomY);
            QPointF bottomPot = QPointF(initX, initBottomY - longLineLen);
            painter->drawLine(topPot, bottomPot);

            //第一个值和最后一个值不要绘制
            if (i == minValue || i == maxValue) {
                initX += increment * shortStep;
                continue;
            }

            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);
            double textWidth = fontMetrics().width(strValue);
            double textHeight = fontMetrics().height();

            QPointF textPot = QPointF(initX - textWidth / 2, initBottomY - textHeight / 2 - longLineLen);
            painter->drawText(textPot, strValue);
        } else {
            if (i % (longStep / 2) == 0) {
                shortLineLen = 10;
            } else {
                shortLineLen = 6;
            }

            QPointF topPot = QPointF(initX, initBottomY);
            QPointF bottomPot = QPointF(initX, initBottomY - shortLineLen);
            painter->drawLine(topPot, bottomPot);
        }

        initX += increment * shortStep;
    }

    painter->restore();
}

void ORulerProgress::updateValue()
{

}

double ORulerProgress::getMinValue() const
{
    return minValue;
}

double ORulerProgress::getMaxValue() const
{
    return maxValue;
}

double ORulerProgress::getValue() const
{
    return value;
}

int ORulerProgress::getPrecision() const
{
    return precision;
}

int ORulerProgress::getLongStep() const
{
    return longStep;
}

int ORulerProgress::getShortStep() const
{
    return shortStep;
}

bool ORulerProgress::getRulerTop() const
{
    return rulerTop;
}

bool ORulerProgress::getAnimation() const
{
    return animation;
}

double ORulerProgress::getAnimationStep() const
{
    return animationStep;
}

QColor ORulerProgress::getBgColor() const
{
    return bgColor;
}

QColor ORulerProgress::getLineColor() const
{
    return lineColor;
}

QColor ORulerProgress::getProgressColor() const
{
    return progressColor;
}



void ORulerProgress::setRange(double minValue, double maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;

}

void ORulerProgress::setRange(int minValue, int maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}

void ORulerProgress::setMinValue(double minValue)
{
    this->minValue = minValue;

}

void ORulerProgress::setMaxValue(double maxValue)
{
    this->maxValue = maxValue;

}

void ORulerProgress::setValue(double value)
{
    if(value < minValue) this->value = minValue;
    if(value > maxValue) this->value = maxValue;
    this->value = value;
    this->currentValue = value;
    update();


}

void ORulerProgress::setValue(int value)
{
    if(value < minValue) this->value = minValue;
    if(value > maxValue) this->value = maxValue;
    this->value = value;
    this->currentValue = value;

    update();
}

void ORulerProgress::setPrecision(int precision)
{
    this->precision = precision;

}

void ORulerProgress::setLongStep(int longStep)
{
    this->longStep = longStep;

}

void ORulerProgress::setShortStep(int shortStep)
{
    this->shortStep = shortStep;

}

void ORulerProgress::setRulerTop(bool rulerTop)
{
    this->rulerTop = rulerTop;

}

void ORulerProgress::setAnimation(bool animation)
{
    this->animation = animation;

}

void ORulerProgress::setAnimationStep(double animationStep)
{
    this->animationStep = animationStep;

}

void ORulerProgress::setBgColor(const QColor &bgColor)
{
    this->bgColor = bgColor;

}

void ORulerProgress::setLineColor(const QColor &lineColor)
{
    this->lineColor = lineColor;

}

void ORulerProgress::setProgressColor(const QColor &progressColor)
{
    this->progressColor = progressColor;

}
