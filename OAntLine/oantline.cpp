#include "oantline.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"


OAntLine::OAntLine(QWidget *parent) : QWidget(parent)
{
    lineLen = 6;
    lineWidth = 2;
    lineStep = 1;
    lineSpeed = 100;

    lineColor = QColor(0, 0, 0);
    lineStyle = LineStyle_Circle;

    dashes = lineLen;
    spaces = lineLen;
    dashPattern.clear();
    for (int i = 0; i < 20; ++i) {
        dashPattern << lineLen;
    }

    //启动定时器更新线条
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start(lineSpeed);
}

OAntLine::~OAntLine()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void OAntLine::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    //设置画笔宽度+颜色+点阵样式
    QPen pen;
    pen.setWidth(lineWidth);
    pen.setColor(lineColor);
    pen.setDashPattern(dashPattern);
    painter.setPen(pen);

    //根据不同的样式绘制不同的线条
    if (lineStyle == LineStyle_Rect) {
        painter.drawRect(0, 0, width, height);
    } else if (lineStyle == LineStyle_RoundedRect) {
        painter.drawRoundedRect(0, 0, width, height, 5, 5);
    } else if (lineStyle == LineStyle_Ellipse) {
        painter.drawEllipse(0, 0, width, height);
    } else if (lineStyle == LineStyle_Circle) {
        painter.drawEllipse(width / 2 - side / 2, 0, side, side);
    }
}

void OAntLine::updateValue()
{
    //当蚂蚁线走到末尾,则重新赋值
    if (dashes == lineLen && spaces == lineLen) {
        dashes = 0;
        spaces = 0;
    }

    if (dashes == 0 && spaces < lineLen) {
        spaces = spaces + lineStep;
    } else if (spaces == lineLen && dashes < lineLen) {
        dashes = dashes + lineStep;
    }

    //每次只需要将前面两个长度更新就行
    dashPattern[0] = dashes;
    dashPattern[1] = spaces;

    update();
}

int OAntLine::getLineLen() const
{
    return this->lineLen;
}

int OAntLine::getLineWidth() const
{
    return this->lineWidth;
}

int OAntLine::getLineStep() const
{
    return this->lineStep;
}

int OAntLine::getLineSpeed() const
{
    return this->lineSpeed;
}

QColor OAntLine::getLineColor() const
{
    return this->lineColor;
}

OAntLine::LineStyle OAntLine::getLineStyle() const
{
    return this->lineStyle;
}

QSize OAntLine::sizeHint() const
{
    return QSize(100, 100);
}

QSize OAntLine::minimumSizeHint() const
{
    return QSize(20, 20);
}

void OAntLine::setLineLen(int lineLen)
{
    if (this->lineLen != lineLen) {
        this->lineLen = lineLen;

        dashes = lineLen;
        spaces = lineLen;
        dashPattern.clear();
        for (int i = 0; i < 20; ++i) {
            dashPattern << lineLen;
        }

        update();
    }
}

void OAntLine::setLineWidth(int lineWidth)
{
    if (this->lineWidth != lineWidth) {
        this->lineWidth = lineWidth;
        update();
    }
}

void OAntLine::setLineStep(int lineStep)
{
    if (this->lineStep != lineStep) {
        this->lineStep = lineStep;
        update();
    }
}

void OAntLine::setLineSpeed(int lineSpeed)
{
    if (this->lineSpeed != lineSpeed) {
        this->lineSpeed = lineSpeed;
        update();
    }
}

void OAntLine::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}

void OAntLine::setLineStyle(const OAntLine::LineStyle &lineStyle)
{
    if (this->lineStyle != lineStyle) {
        this->lineStyle = lineStyle;
        update();
    }
}



