#include "ogaugepercent.h"
#include <QtMath>
#include <QPainter>

OGaugePercent::OGaugePercent(QWidget *parent) :
    QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 0;

    scaleMajor = 5;
    scaleMinor = 2;

    startAngle = 60;
    endAngle = 300;

    arcColor = Qt::cyan;
    scaleColor = Qt::yellow;
    scaleNumColor = Qt::white;
    textColor = Qt::red;

    titleColor = Qt::blue;
    baseColor = Qt::green;
    bgColor = Qt::gray;

    title = "title";
}
void OGaugePercent::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    if (bgColor != Qt::transparent) {
        painter.setPen(Qt::NoPen);
        painter.fillRect(this->rect(), bgColor);
    }

    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制圆弧
    drawArc(&painter);
    //绘制圆弧进度小球
    drawCircle(&painter);
    //绘制刻度线
    drawScale(&painter);
    //绘制刻度值
    drawScaleNum(&painter);
    //绘制当前值
    drawValue(&painter);
    //绘制标题
    drawTitle(&painter);
}

void OGaugePercent::drawArc(QPainter *painter)
{
    int radius = 95;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    QPen pen;
    pen.setWidthF(5);
    pen.setCapStyle(Qt::RoundCap);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = endAngle - startAngle ;
    double angleCurrent = angleAll * ((value - minValue) / (maxValue - minValue));
    double angleOther = angleAll - angleCurrent;
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);

    //绘制当前进度圆弧
    pen.setColor(arcColor);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);

    //绘制剩余进度圆弧
    pen.setColor(scaleColor);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void OGaugePercent::drawCircle(QPainter *painter)
{
    int radius = 6;
    int offset = 83;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(arcColor);

    painter->rotate(startAngle);
    double degRotate = (endAngle - startAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void OGaugePercent::drawScale(QPainter *painter)
{
    int radius = 90;
    painter->save();

    painter->rotate(startAngle);
    int steps = (scaleMajor * scaleMinor);
    double angleStep = (endAngle - startAngle) / steps;

    QPen pen;
    pen.setColor(scaleColor);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(1.0);
    painter->setPen(pen);

    for (int i = 0; i <= steps; i++) {
        painter->drawLine(0, radius - 5, 0, radius);
        painter->rotate(angleStep);
    }

    painter->restore();
}

void OGaugePercent::drawScaleNum(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setPen(scaleNumColor);

    double startRad = (360 - startAngle - 90) * (M_PI / 180);
    double deltaRad = (endAngle - startAngle) * (M_PI / 180) / scaleMajor;

    for (int i = 0; i <= scaleMajor; i++) {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 1.0 * i * ((maxValue - minValue) / scaleMajor) + minValue;

        QString strValue = QString("%1").arg((double)value, 0, 'f', precision);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void OGaugePercent::drawValue(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(30);
    painter->setFont(font);

    QRectF textRect(-radius, 0, radius * 2, radius / 3);
    QString strValue = QString("%1%").arg((double)value, 0, 'f', precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void OGaugePercent::drawTitle(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(titleColor);

    QFont font;
    font.setPixelSize(20);
    painter->setFont(font);

    QRectF textRect(-radius, radius / 3, radius * 2, radius / 3);
    painter->drawText(textRect, Qt::AlignCenter, title);

    painter->restore();
}

double OGaugePercent::getMinValue() const
{
    return minValue;
}

double OGaugePercent::getMaxValue() const
{
    return maxValue;
}

double OGaugePercent::getValue() const
{
    return value;
}

int OGaugePercent::getPrecision() const
{
    return precision;
}

int OGaugePercent::getScaleMajor() const
{
    return scaleMajor;
}

int OGaugePercent::getScaleMinor() const
{
    return scaleMinor;
}

int OGaugePercent::getStartAngle() const
{
    return startAngle;
}

int OGaugePercent::getEndAngle() const
{
    return endAngle;
}

QColor OGaugePercent::getArcColor() const
{
    return arcColor;
}

QColor OGaugePercent::getScaleColor() const
{
    return scaleColor;
}

QColor OGaugePercent::getScaleNumColor() const
{
    return scaleNumColor;
}

QColor OGaugePercent::getTextColor() const
{
    return textColor;
}

QColor OGaugePercent::getTitleColor() const
{
    return titleColor;
}

QColor OGaugePercent::getBaseColor() const
{
    return baseColor;
}

QColor OGaugePercent::getBgColor() const
{
    return bgColor;
}

QString OGaugePercent::getTitle() const
{
    return title;
}



void OGaugePercent::setRange(double minValue, double maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;

}

void OGaugePercent::setRange(int minValue, int maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}

void OGaugePercent::setMinValue(double minValue)
{
    this->minValue = minValue;
}

void OGaugePercent::setMaxValue(double maxValue)
{
    this->maxValue = maxValue;

}

void OGaugePercent::setValue(double value)
{


    if(value < minValue) this->value = minValue;
    if(value > maxValue) this->value = maxValue;

    this->value = value;
    update();


}

void OGaugePercent::setValue(int value)
{
    if(value < minValue) this->value = minValue;
    if(value > maxValue) this->value = maxValue;

    this->value = value;
    update();
}

void OGaugePercent::setPrecision(int precision)
{
    this->precision = precision;

}

void OGaugePercent::setScaleMajor(int scaleMajor)
{
    this->scaleMajor = scaleMajor;

}

void OGaugePercent::setScaleMinor(int scaleMinor)
{
    this->scaleMinor = scaleMinor;

}

void OGaugePercent::setStartAngle(int startAngle)
{
    this->startAngle = startAngle;

}

void OGaugePercent::setEndAngle(int endAngle)
{
    this->endAngle = endAngle;

}

void OGaugePercent::setArcColor(const QColor &arcColor)
{
    this->arcColor = arcColor;

}

void OGaugePercent::setScaleColor(const QColor &scaleColor)
{
    this->scaleColor = scaleColor;

}

void OGaugePercent::setScaleNumColor(const QColor &scaleNumColor)
{
    this->scaleNumColor = scaleNumColor;

}

void OGaugePercent::setTextColor(const QColor &textColor)
{
    this->textColor = textColor;

}

void OGaugePercent::setTitleColor(const QColor &titleColor)
{
    this->titleColor = titleColor;

}

void OGaugePercent::setBaseColor(const QColor &baseColor)
{
    this->baseColor = baseColor;

}

void OGaugePercent::setBgColor(const QColor &bgColor)
{
    this->bgColor = bgColor;

}

void OGaugePercent::setTitle(const QString &title)
{
    this->title = title;

}

