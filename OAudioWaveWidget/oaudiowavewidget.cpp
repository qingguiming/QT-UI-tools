#include "oaudiowavewidget.h"
#include <QPainter>
#include <QPainterPath>
#include "smoothcurvegenerator.h"

OAudioWaveWidget::OAudioWaveWidget(QWidget *parent) :
    QWidget(parent)
{

    deep = 2.0;
    showLine = true;
    lineWidth = 2;
    waveStyle = WaveStyle_Smooth;
    length = 50;
    position = 0;
}

void OAudioWaveWidget::mousePressEvent(QMouseEvent *)
{

}

void OAudioWaveWidget::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制数据
    drawData(&painter);
    //绘制当前位置线条
    drawLine(&painter);

}

void OAudioWaveWidget::drawBg(QPainter *painter)
{
    painter->save();
    painter->fillRect(this->rect(), background);
    painter->restore();
}

void OAudioWaveWidget::drawData(QPainter *painter)
{
    if (data.count() == 0) {
        return;
    }

    painter->save();

    //获取最大值最小值
    float max = data.at(0);
    float min = data.at(0);
    int count = data.count();

    for (int i = 1; i < count; i++) {
        if (max < data.at(i)) {
            max = data.at(i);
        }

        if (min > data.at(i)) {
            min = data.at(i);
        }
    }

    //转化成当前屏幕的内的坐标大小
    max += deep;
    min -= deep;

    //自动转换数据到屏幕坐标位置
    QList<QPointF> points;
    for (int i = 0; i < count; i++) {
        double x = i * width() / count;
        double y = height() - (((data.at(i) - min) / (max - min)) * height());
        points.append(QPointF(x, y));
    }

    //绘制不同的风格
    if (waveStyle == WaveStyle_Line) {
        painter->setPen(foreground);
        for (int i = 0; i < count - 1; i++) {
            painter->drawLine(points.at(i), points.at(i + 1));
        }
    } else if (waveStyle == WaveStyle_Smooth) {
        painter->setPen(foreground);
        //QPainterPath path = SmoothCurveCreator::createSmoothCurve(points);
        QPainterPath path = SmoothCurveGenerator::generateSmoothCurve(points);

        painter->drawPath(path);
    } else if (waveStyle == WaveStyle_Bar) {
        double penWidth = width() / (count * 1.6);
        QPen pen;
        pen.setColor(foreground);
        pen.setWidthF(penWidth);
        pen.setCapStyle(Qt::RoundCap);
        painter->setPen(pen);

        for (int i = 0; i < count; i++) {
            QPointF point = points.at(i);
            double x = point.x() + penWidth / 1.2;
            painter->drawLine(QPointF(x, point.y()), QPointF(x, height()));
        }
    }

    painter->restore();

}

void OAudioWaveWidget::drawLine(QPainter *painter)
{
    if (!showLine || position > length || data.count() <= 0) {
        return;
    }

    painter->save();

    QPen pen;
    pen.setWidth(lineWidth);
    pen.setColor(lineColor);
    painter->setPen(pen);

    //计算当前位置对应的坐标
    int x = ((double)position / length) * width();
    painter->drawLine(x, 0, x, height());

    painter->restore();

}

double OAudioWaveWidget::getDeep() const
{
    return deep;
}

bool OAudioWaveWidget::getShowLine() const
{
    return showLine;
}

int OAudioWaveWidget::getLineWidth() const
{
    return lineWidth;
}

QColor OAudioWaveWidget::getLineColor() const
{
    return lineColor;
}

QColor OAudioWaveWidget::getForeground() const
{
    return lineColor;
}

QColor OAudioWaveWidget::getBackground() const
{
    return background;
}

OAudioWaveWidget::WaveStyle OAudioWaveWidget::getWaveStyle() const
{
    return waveStyle;
}

QSize OAudioWaveWidget::sizeHint() const
{
    return QWidget::sizeHint();
}

QSize OAudioWaveWidget::minimumSizeHint() const
{
    return QWidget::minimumSizeHint();

}

void OAudioWaveWidget::setDeep(double deep)
{
    this->deep = deep;
}

void OAudioWaveWidget::setShowLine(bool showLine)
{
    this->showLine = showLine;

}

void OAudioWaveWidget::setLineWidth(int lineWidth)
{
    this->lineWidth = lineWidth;

}

void OAudioWaveWidget::setLineColor(const QColor &lineColor)
{
    this->lineColor = lineColor;

}

void OAudioWaveWidget::setForeground(const QColor &foreground)
{
    this->foreground = foreground;

}

void OAudioWaveWidget::setBackground(const QColor &background)
{
    this->background = background;

}

void OAudioWaveWidget::setWaveStyle(const OAudioWaveWidget::WaveStyle &waveStyle)
{
    this->waveStyle = waveStyle;

}

void OAudioWaveWidget::setLength(int length)
{
    this->length = length;

}

void OAudioWaveWidget::setPosition(int position)
{
    this->position = position;
    update();

}

void OAudioWaveWidget::setData(const QList<float> &data)
{
    this->data = data;

}

void OAudioWaveWidget::clearData()
{
    data.clear();
}
