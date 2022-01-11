#include "orulertemp.h"
#include <QPainter>

ORulerTemp::ORulerTemp(QWidget *parent) :
    QWidget(parent)
{
    minValue = 0;
    maxValue = 0;
    value = 1;
    precision = 0;
    longStep = 5;
    shortStep = 1;
    space = 1;
    animation = true;
    animationStep = 1;

    showUserValue = true;
    userValue = 1.0;
    userValueColor = Qt::red;

    bgColorStart = Qt::gray;
    bgColorEnd = Qt::lightGray;
    lineColor = Qt::yellow;
    barBgColor = Qt::blue;
    barColor = Qt::cyan;
    barPosition = BarPosition_Center;
    tickPosition = TickPosition_Both;

    barWidth = 16;
    barHeight = 200;
    radius = 35;
    targetX = 50;
    reverse = true;
    currentValue = 0.0;

}

void ORulerTemp::resizeEvent(QResizeEvent *)
{

}
void ORulerTemp::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);

    //绘制标尺及刻度尺
    if (tickPosition == TickPosition_Left) {
        drawRuler(&painter, 0);
    } else if (tickPosition == TickPosition_Right) {
        drawRuler(&painter, 1);
    } else if (tickPosition == TickPosition_Both) {
        drawRuler(&painter, 0);
        drawRuler(&painter, 1);
    }

    //绘制水银柱背景,包含水银柱底部圆
    drawBarBg(&painter);

    //绘制当前水银柱,包含水银柱底部圆
    drawBar(&painter);

    //绘制当前值
    drawValue(&painter);
}

void ORulerTemp::drawBg(QPainter *painter)
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

void ORulerTemp::drawBarBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barBgColor);

    barHeight = height() - space - 2 * radius;

    int barX = targetX - barWidth / 2;
    int barY = space;
    QRectF barRect(barX, barY, barWidth, barHeight);

    int circleX = targetX - radius;
    //偏移 2 个像素,使得看起来边缘完整
    int circleY = height() - radius * 2 - 2;
    int circleWidth = radius * 2;
    QRectF circleRect(circleX, circleY, circleWidth, circleWidth);

    QPainterPath path;
    path.addRect(barRect);
    path.addEllipse(circleRect);
    path.setFillRule(Qt::WindingFill);
    painter->drawPath(path);
    painter->restore();
}

void ORulerTemp::drawRuler(QPainter *painter, int type)
{
    painter->save();
    painter->setPen(lineColor);

    int barPercent = barWidth / 8;

    if (barPercent < 2) {
        barPercent = 2;
    }

    //绘制纵向标尺刻度
    double length = height() - 2 * space - 2 * radius;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);

    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 7;

    //绘制纵向标尺线 偏移 5 像素
    int offset = barWidth / 2 + 5;

    //左侧刻度尺需要重新计算
    if (type == 0) {
        offset = -offset;
        longLineLen = -longLineLen;
        shortLineLen = -shortLineLen;
    }

    double initX = targetX + offset;
    double initY = space + barPercent;
    QPointF topPot(initX, initY);
    QPointF bottomPot(initX, height() - 2 * radius - 5);
    painter->drawLine(topPot, bottomPot);

    //根据范围值绘制刻度值及刻度值
    for (int i = maxValue; i >= minValue; i = i - shortStep) {
        if (i % longStep == 0) {
            //绘制长线条
            QPointF leftPot(initX + longLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);

            //绘制文字
            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);
            double fontHeight = painter->fontMetrics().height();

            if (type == 0) {
                QRect textRect(initX - 45, initY - fontHeight / 3, 30, 15);
                painter->drawText(textRect, Qt::AlignRight, strValue);
            } else if (type == 1) {
                QRect textRect(initX + longLineLen + 5, initY - fontHeight / 3, 30, 15);
                painter->drawText(textRect, Qt::AlignLeft, strValue);
            }
        } else {
            //绘制短线条
            QPointF leftPot(initX + shortLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);
        }

        initY += increment * shortStep;
    }

    painter->restore();
}

void ORulerTemp::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor);

    //计算在背景宽度的基础上缩小的百分比, 至少为 2
    int barPercent = barWidth / 8;
    int circlePercent = radius / 6;

    if (barPercent < 2) {
        barPercent = 2;
    }

    if (circlePercent < 2) {
        circlePercent = 2;
    }

    //标尺刻度高度
    double length = height() - 2 * space - 2 * radius;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //计算标尺的高度
    int rulerHeight = height() - 1 * space - 2 * radius;

    int barX = targetX - barWidth / 2;
    int barY = rulerHeight - (currentValue - minValue) * increment;
    barRect = QRectF(barX + barPercent, barY + barPercent, barWidth - barPercent * 2, barHeight + radius - barY);



    int circleX = targetX - radius;
    //偏移 2 个像素,使得看起来边缘完整
    int circleY = height() - radius * 2 - 2;
    int circleWidth = radius * 2 - circlePercent * 2;
    circleRect = QRectF(circleX + circlePercent, circleY + circlePercent, circleWidth, circleWidth);

    QPainterPath path;
    path.addRect(barRect);
    path.addEllipse(circleRect);
    path.setFillRule(Qt::WindingFill);
    painter->drawPath(path);

    //绘制用户设定值三角号
//    if (showUserValue)
    if (false)
    {
        if (tickPosition == TickPosition_Left || tickPosition == TickPosition_Both) {
            QPolygon pts;
            int offset = 15;
            double initX = targetX - (barWidth / 2 + 5);
            double initY = rulerHeight - (userValue - minValue) * increment;
            pts.append(QPoint(initX, initY));
            pts.append(QPoint(initX - offset, initY - offset / 2));
            pts.append(QPoint(initX - offset, initY + offset / 2));
            painter->setBrush(userValueColor);
            painter->drawPolygon(pts);
        }

        if (tickPosition == TickPosition_Right || tickPosition == TickPosition_Both) {
            QPolygon pts;
            int offset = 15;
            double initX = targetX + (barWidth / 2 + 5);
            double initY = rulerHeight - (userValue - minValue) * increment;
            pts.append(QPoint(initX, initY));
            pts.append(QPoint(initX + offset, initY - offset / 2));
            pts.append(QPoint(initX + offset, initY + offset / 2));
            painter->setBrush(userValueColor);
            painter->drawPolygon(pts);
        }
    }

    painter->restore();
}

void ORulerTemp::drawValue(QPainter *painter)
{
    painter->save();

    QFont font;
    font.setPixelSize(circleRect.width() * 0.55);
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(circleRect, Qt::AlignCenter, QString("%1").arg(currentValue));

    painter->restore();
}

void ORulerTemp::updateValue()
{

}

double ORulerTemp::getMinValue() const
{
    return minValue;
}

double ORulerTemp::getMaxValue() const
{
    return maxValue;
}

double ORulerTemp::getValue() const
{
    return value;
}

int ORulerTemp::getPrecision() const
{
    return precision;
}

int ORulerTemp::getLongStep() const
{
    return longStep;
}

int ORulerTemp::getShortStep() const
{
    return shortStep;
}

int ORulerTemp::getSpace() const
{
    return space;
}

bool ORulerTemp::getAnimation() const
{
    return animation;
}

double ORulerTemp::getAnimationStep() const
{
    return animationStep;
}

bool ORulerTemp::getShowUserValue() const
{
    return showUserValue;
}

double ORulerTemp::getUserValue() const
{
    return userValue;
}

QColor ORulerTemp::getUserValueColor() const
{
    return userValueColor;
}

QColor ORulerTemp::getBgColorStart() const
{
    return bgColorStart;
}

QColor ORulerTemp::getBgColorEnd() const
{
    return bgColorEnd;
}

QColor ORulerTemp::getLineColor() const
{
    return lineColor;
}

QColor ORulerTemp::getBarBgColor() const
{
    return barBgColor;
}

QColor ORulerTemp::getBarColor() const
{
    return barColor;
}

ORulerTemp::BarPosition ORulerTemp::getBarPosition() const
{
    return barPosition;
}

ORulerTemp::TickPosition ORulerTemp::getTickPosition() const
{
    return tickPosition;
}

void ORulerTemp::setRange(double minValue, double maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;

}

void ORulerTemp::setRange(int minValue, int maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}

void ORulerTemp::setMinValue(double minValue)
{
    this->minValue = minValue;

}

void ORulerTemp::setMaxValue(double maxValue)
{
    this->maxValue = maxValue;
}

void ORulerTemp::setValue(double value)
{
    this->value = value;
    this->currentValue =  value;
    update();

}

void ORulerTemp::setValue(int value)
{
    this->value = value;
    this->currentValue =  value;
    update();


}

void ORulerTemp::setPrecision(int precision)
{
    this->precision = precision;

}

void ORulerTemp::setLongStep(int longStep)
{
    this->longStep = longStep;

}

void ORulerTemp::setShortStep(int shortStep)
{
    this->shortStep = shortStep;

}

void ORulerTemp::setSpace(int space)
{
    this->space = space;

}

void ORulerTemp::setAnimation(bool animation)
{
    this->animation = animation;

}

void ORulerTemp::setAnimationStep(double animationStep)
{
    this->animationStep = animationStep;

}

void ORulerTemp::setShowUserValue(bool showUserValue)
{
    this->showUserValue = showUserValue;

}

void ORulerTemp::setUserValue(double userValue)
{
    this->userValue = userValue;

}

void ORulerTemp::setUserValue(int userValue)
{
    this->userValue = userValue;

}

void ORulerTemp::setUserValueColor(const QColor &userValueColor)
{
    this->userValueColor = userValueColor;

}

void ORulerTemp::setBgColorStart(const QColor &bgColorStart)
{
    this->bgColorStart = bgColorStart;

}

void ORulerTemp::setBgColorEnd(const QColor &bgColorEnd)
{
    this->bgColorEnd = bgColorEnd;

}

void ORulerTemp::setLineColor(const QColor &lineColor)
{
    this->lineColor = lineColor;

}

void ORulerTemp::setBarBgColor(const QColor &barBgColor)
{
    this->barBgColor = barBgColor;

}

void ORulerTemp::setBarColor(const QColor &barColor)
{
    this->barColor = barColor;

}

void ORulerTemp::setBarPosition(const ORulerTemp::BarPosition &barPosition)
{
    this->barPosition = barPosition;

}

void ORulerTemp::setTickPosition(const ORulerTemp::TickPosition &tickPosition)
{
    this->tickPosition = tickPosition;

}


