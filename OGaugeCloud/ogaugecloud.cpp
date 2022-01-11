#include "ogaugecloud.h"
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
OGaugeCloud::OGaugeCloud(QWidget *parent) :
    QWidget(parent)
{
}

OGaugeCloud::~OGaugeCloud()
{

}

void OGaugeCloud::enterEvent(QEvent *e)
{
    //qDebug()<<"enterEvent";


}

void OGaugeCloud::leaveEvent(QEvent *e)
{
    //qDebug()<<"leaveEvent";


}

void OGaugeCloud::mousePressEvent(QMouseEvent *e)
{
    //qDebug()<<"mousePressEvent";
    lastPoint = e->pos();
    pressed = true;
    update();


}

void OGaugeCloud::mouseReleaseEvent(QMouseEvent *e)
{
    //qDebug()<<"mouseReleaseEvent";
    pressed = false;
    update();



}
void OGaugeCloud::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //以中心点为基准,分别计算八方位区域和中间区域
    QPointF center = this->rect().center();
    double centerSize = (double)side / ((double)100 / 30);
    double iconSize = (double)side / ((double)100 / 10);
    double offset1 = 3.6;
    double offset2 = 2.65;

    //中间区域
    centerRect = QRectF(center.x() - centerSize / 2, center.y() - centerSize / 2, centerSize, centerSize);
    //左侧图标区域
    leftRect = QRectF(center.x() - iconSize * offset1, center.y() - iconSize / 2, iconSize, iconSize);
    //上侧图标区域
    topRect = QRectF(center.x() - iconSize / 2, center.y() - iconSize * offset1, iconSize, iconSize);
    //右侧图标区域
    rightRect = QRectF(center.x() + iconSize * (offset1 - 1), center.y() - iconSize / 2, iconSize, iconSize);
    //下侧图标区域
    bottomRect = QRectF(center.x() - iconSize / 2, center.y() + iconSize * (offset1 - 1), iconSize, iconSize);
    //左上角图标区域
    leftTopRect = QRectF(center.x() - iconSize * offset2, center.y() - iconSize * offset2, iconSize, iconSize);
    //右上角图标区域
    rightTopRect = QRectF(center.x() + iconSize * (offset2 - 1), center.y() - iconSize * offset2, iconSize, iconSize);
    //左下角图标区域
    leftBottomRect = QRectF(center.x() - iconSize * offset2, center.y() + iconSize * (offset2 - 1), iconSize, iconSize);
    //右下角图标区域
    rightBottomRect = QRectF(center.x() + iconSize * (offset2 - 1), center.y() + iconSize * (offset2 - 1), iconSize, iconSize);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    if (cloudStyle == CloudStyle_Black) {
        //绘制外圆背景
        drawCircle(&painter, 99, bgColor);
        //绘制圆弧
        drawArc(&painter);
        //绘制中间圆盘背景
        drawCircle(&painter, 83, baseColor);
        //绘制内圆背景
        drawCircle(&painter, 40, arcColor);
        //绘制内圆边框
        drawCircle(&painter, 33, borderColor);
        //绘制内圆
        drawCircle(&painter, 30, (pressed && centerRect.contains(lastPoint)) ? bgColor : baseColor);
    } else if (cloudStyle == CloudStyle_White) {
        //绘制外圆背景
        drawCircle(&painter, 99, QColor(249, 249, 249));

        //设置圆锥渐变
        QConicalGradient gradient(0, 0, 100);
        gradient.setColorAt(0, QColor(34, 163, 169));
        gradient.setColorAt(0.4, QColor(240, 201, 136));
        gradient.setColorAt(0.7, QColor(211, 77, 37));
        gradient.setColorAt(1, QColor(34, 163, 169));

        //绘制彩色外圆
        drawCircle(&painter, 90, gradient);
        //绘制中间圆盘背景
        drawCircle(&painter, 83, QColor(245, 245, 245));
        //绘制内圆背景
        drawCircle(&painter, 33, QColor(208, 208, 208));
        //绘制内圆边框
        drawCircle(&painter, 32, QColor(208, 208, 208));
        //绘制内圆
        drawCircle(&painter, 30, (pressed && centerRect.contains(lastPoint)) ? QColor(255, 255, 255) : QColor(245, 245, 245));
    } else if (cloudStyle == CloudStyle_Blue) {
        //设置圆锥渐变
        QConicalGradient gradient(0, 0, 100);
        gradient.setColorAt(0, QColor(34, 163, 169));
        gradient.setColorAt(0.4, QColor(240, 201, 136));
        gradient.setColorAt(0.7, QColor(211, 77, 37));
        gradient.setColorAt(1, QColor(34, 163, 169));

        //绘制色彩外圆
        drawCircle(&painter, 99, gradient);
        //绘制中间圆盘背景
        drawCircle(&painter, 91, QColor(31, 66, 98));
        //绘制内圆背景
        drawCircle(&painter, 33, QColor(23, 54, 81));
        //绘制内圆边框
        drawCircle(&painter, 30, QColor(150, 150, 150));
        //绘制内圆
        drawCircle(&painter, 30, (pressed && centerRect.contains(lastPoint)) ? QColor(35, 82, 133) : QColor(34, 73, 115));
    } else if (cloudStyle == CloudStyle_Purple) {
        //设置圆锥渐变
        QConicalGradient gradient(0, 0, 100);
        gradient.setColorAt(0, QColor(87, 87, 155));
        gradient.setColorAt(0.4, QColor(129, 82, 130));
        gradient.setColorAt(0.7, QColor(54, 89, 166));
        gradient.setColorAt(1, QColor(87, 87, 155));

        //绘制色彩外圆
        drawCircle(&painter, 99, gradient);
        //绘制中间圆盘背景
        drawCircle(&painter, 91, QColor(55, 55, 92));
        //绘制内圆背景
        drawCircle(&painter, 33, QColor(49, 48, 82));
        //绘制内圆边框
        drawCircle(&painter, 30, QColor(82, 78, 131));
        //绘制内圆
        drawCircle(&painter, 30, (pressed && centerRect.contains(lastPoint)) ? QColor(85, 81, 137) : QColor(62, 59, 103));
    }

    //绘制八方位+中间图标
    drawText(&painter);

#if 0
    //重置坐标系,并绘制八方位区域及中间区域,判断是否正确
    painter.resetMatrix();
    painter.resetTransform();
    painter.setPen(Qt::white);
    painter.drawRect(centerRect);
    painter.drawRect(leftRect);
    painter.drawRect(topRect);
    painter.drawRect(rightRect);
    painter.drawRect(bottomRect);
    painter.drawRect(leftTopRect);
    painter.drawRect(rightTopRect);
    painter.drawRect(leftBottomRect);
    painter.drawRect(rightBottomRect);
#endif
}

void OGaugeCloud::drawCircle(QPainter *painter, int radius, const QBrush &brush)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(brush);

    //绘制圆
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void OGaugeCloud::drawArc(QPainter *painter)
{
    int radius = 91;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    QPen pen;
    pen.setWidthF(10);
    pen.setColor(arcColor);
    painter->setPen(pen);

    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    painter->drawArc(rect, 0 * 16, 360 * 16);

    painter->restore();
}

void OGaugeCloud::drawText(QPainter *painter)
{
    bool ok;
    int radius = 100;
    painter->save();

    //判断当前按下坐标是否在中心区域,按下则文本不同颜色
    if (pressed && centerRect.contains(lastPoint)) {
        emit mousePressed(8);
        painter->setPen(pressColor);
    } else {
        painter->setPen(textColor);
    }

    QFont font;
    font.setPixelSize(25);
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,0))
    font.setHintingPreference(QFont::PreferNoHinting);
#endif
    painter->setFont(font);

    //绘制中间图标
    QRectF centerRect(-radius, -radius, radius * 2, radius * 2);
    QString centerText = this->centerText.replace("0x", "");
    QChar centerChar = QChar(centerText.toInt(&ok, 16));
    painter->drawText(centerRect, Qt::AlignCenter, centerChar);

    //绘制八方位图标
    radius = 70;
    int offset = 15;
    int steps = 8;
    double angleStep = 360.0 / steps;

    font.setPixelSize(20);
    painter->setFont(font);

    //从下侧图标开始绘制,顺时针旋转
    QRect iconRect(-offset / 2, radius - offset, offset, offset);
    QString iconText = this->iconText.replace("0x", "");
    QChar iconChar = QChar(iconText.toInt(&ok, 16));
    for (int i = 0; i < steps; i++) {
        //判断鼠标按下的是哪个区域
        if (pressed) {
            bool contains = false;
            if (bottomRect.contains(lastPoint) && i == 0) {
                contains = true;
            } else if (leftBottomRect.contains(lastPoint) && i == 1) {
                contains = true;
            } else if (leftRect.contains(lastPoint) && i == 2) {
                contains = true;
            } else if (leftTopRect.contains(lastPoint) && i == 3) {
                contains = true;
            } else if (topRect.contains(lastPoint) && i == 4) {
                contains = true;
            } else if (rightTopRect.contains(lastPoint) && i == 5) {
                contains = true;
            } else if (rightRect.contains(lastPoint) && i == 6) {
                contains = true;
            } else if (rightBottomRect.contains(lastPoint) && i == 7) {
                contains = true;
            }

            if (contains) {
                painter->setPen(pressColor);
                emit mousePressed(i);
            } else {
                painter->setPen(textColor);
            }
        } else {
            painter->setPen(textColor);
        }

        painter->drawText(iconRect, Qt::AlignCenter, iconChar);
        painter->rotate(angleStep);
    }

    painter->restore();
}

QColor OGaugeCloud::getBgColor() const
{
    return bgColor;
}

QColor OGaugeCloud::getBaseColor() const
{
    return baseColor;
}

QColor OGaugeCloud::getArcColor() const
{
    return arcColor;
}

QColor OGaugeCloud::getBorderColor() const
{
    return borderColor;
}

QColor OGaugeCloud::getTextColor() const
{
    return textColor;
}

QColor OGaugeCloud::getPressColor() const
{
    return pressColor;
}

QString OGaugeCloud::getIconText() const
{
    return iconText;
}

QString OGaugeCloud::getCenterText() const
{
    return centerText;
}

OGaugeCloud::CloudStyle OGaugeCloud::getCloudStyle() const
{
    return cloudStyle;
}

QSize OGaugeCloud::sizeHint() const
{
    return QWidget::sizeHint();
}

QSize OGaugeCloud::minimumSizeHint() const
{
    return QWidget::minimumSizeHint();
}

void OGaugeCloud::setBgColor(const QColor &bgColor)
{
    this->bgColor = bgColor;
}

void OGaugeCloud::setBaseColor(const QColor &baseColor)
{
    this->baseColor = baseColor;

}

void OGaugeCloud::setArcColor(const QColor &arcColor)
{
    this->arcColor = arcColor;

}

void OGaugeCloud::setBorderColor(const QColor &borderColor)
{
    this->borderColor = borderColor;

}

void OGaugeCloud::setTextColor(const QColor &textColor)
{
    this->textColor = textColor;

}

void OGaugeCloud::setPressColor(const QColor &pressColor)
{
    this->pressColor = pressColor;

}

void OGaugeCloud::setIconText(const QString &iconText)
{
    this->iconText = iconText;

}

void OGaugeCloud::setCenterText(const QString centerText)
{
    this->centerText = centerText;
}

void OGaugeCloud::setCloudStyle(const OGaugeCloud::CloudStyle &cloudStyle)
{
    this->cloudStyle = cloudStyle;

}
