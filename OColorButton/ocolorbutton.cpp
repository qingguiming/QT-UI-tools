#include "ocolorbutton.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>

OColorButton::OColorButton(QWidget *parent) :
    QWidget(parent)
{
    borderRadius = 3;
    borderWidth = 1;
    borderColor = Qt::gray;
    showSuperText = true;
    superText = "";
    textAlign  = TextAlign_Top_Left;
    textColor = Qt::black;

    normalColor = Qt::red;
    pressedColor = Qt::lightGray;
    colorMode = ColorMode_Replace;
    isPressed = false;
    canMove = false;
    installEventFilter(this);


}

void OColorButton::mousePressEvent(QMouseEvent *)
{
    //isPressed = true;
}
bool OColorButton::eventFilter(QObject *watched, QEvent *event)
{
//    if (!isEnabled()) {
//        return QWidget::eventFilter(watched, event);
//    }

    static QPoint lastPoint;

    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        if (this->rect().contains(e->pos()) && (e->button() == Qt::LeftButton)) {
            lastPoint = e->pos();
            isPressed = true;
            update();
        }
    } else if (event->type() == QEvent::MouseMove && isPressed && canMove) {
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        int dx = e->pos().x() - lastPoint.x();
        int dy = e->pos().y() - lastPoint.y();
        this->move(this->x() + dx, this->y() + dy);
        return true;
    } else if (event->type() == QEvent::MouseButtonRelease && isPressed) {
        isPressed = false;
        update();
    }

    return QWidget::eventFilter(watched, event);
}

void OColorButton::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制文字
    drawText(&painter);
}

void OColorButton::drawBg(QPainter *painter)
{
    painter->save();

    //设置边框颜色及宽度
    QPen pen;
    pen.setColor(borderColor);
    pen.setWidthF(borderWidth);
    painter->setPen(pen);

    //绘制区域要减去边框宽度
    QRect rect;
    rect.setX(borderWidth);
    rect.setY(borderWidth);
    rect.setWidth(width() - borderWidth * 2);
    rect.setHeight(height() - borderWidth * 2);

    //如果背景图片存在则显示背景图片,否则显示背景色
    if (!bgImage.isNull()) {
        //等比例缩放绘制
        QPixmap img = bgImage.scaled(rect.width(), rect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap((this->rect().width() - img.width()) / 2, (this->rect().height() - img.height()) / 2, img);
    } else {
        if (colorMode == ColorMode_Normal) {
            if (isPressed) {
                painter->setBrush(QBrush(pressedColor));
            } else {
                painter->setBrush(QBrush(normalColor));
            }
        } else if (colorMode == ColorMode_Replace) {
            QLinearGradient gradient(QPoint(0, 0), QPoint(0, height()));

            if (isPressed) {
                gradient.setColorAt(0.0, pressedColor);
                gradient.setColorAt(0.49, pressedColor);
                gradient.setColorAt(0.50, normalColor);
                gradient.setColorAt(1.0, normalColor);
            } else {
                gradient.setColorAt(0.0, normalColor);
                gradient.setColorAt(0.49, normalColor);
                gradient.setColorAt(0.50, pressedColor);
                gradient.setColorAt(1.0, pressedColor);
            }

            painter->setBrush(gradient);
        } else if (colorMode == ColorMode_Shade) {
            QLinearGradient gradient(QPoint(0, 0), QPoint(0, height()));

            if (isPressed) {
                gradient.setColorAt(0.0, pressedColor);
                gradient.setColorAt(1.0, normalColor);
            } else {
                gradient.setColorAt(0.0, normalColor);
                gradient.setColorAt(1.0, pressedColor);
            }

            painter->setBrush(gradient);
        }

        painter->drawRoundedRect(rect, borderRadius, borderRadius);
    }

    painter->restore();
}

void OColorButton::drawText(QPainter *painter)
{
    if (!bgImage.isNull()) {
        return;
    }

    painter->save();

    //如果要显示角标,则重新计算显示文字的区域
    if (showSuperText) {
        int offset = 3;
        QRect rect;
        rect.setX(borderWidth * offset);
        rect.setY(borderWidth);
        rect.setWidth(width() - borderWidth * offset * 2);
        rect.setHeight(height() - borderWidth * 2);

        Qt::Alignment alignment = Qt::AlignCenter;
        if (superTextAlign == TextAlign_Top_Left) {
            alignment = Qt::AlignTop | Qt::AlignLeft;
        } else if (superTextAlign == TextAlign_Top_Center) {
            alignment = Qt::AlignTop | Qt::AlignHCenter;
        } else if (superTextAlign == TextAlign_Top_Right) {
            alignment = Qt::AlignTop | Qt::AlignRight;
        } else if (superTextAlign == TextAlign_Center_Left) {
            alignment = Qt::AlignLeft | Qt::AlignVCenter;
        } else if (superTextAlign == TextAlign_Center_Center) {
            alignment = Qt::AlignHCenter | Qt::AlignVCenter;
        } else if (superTextAlign == TextAlign_Center_Right) {
            alignment = Qt::AlignRight | Qt::AlignVCenter;
        } else if (superTextAlign == TextAlign_Bottom_Left) {
            alignment = Qt::AlignBottom | Qt::AlignLeft;
        } else if (superTextAlign == TextAlign_Bottom_Center) {
            alignment = Qt::AlignBottom | Qt::AlignHCenter;
        } else if (superTextAlign == TextAlign_Bottom_Right) {
            alignment = Qt::AlignBottom | Qt::AlignRight;
        }

        //绘制角标
        painter->setPen(superTextColor);
        painter->setFont(superTextFont);
        painter->drawText(rect, alignment, superText);
    }

    int offset = 5;
    QRect rect;
    rect.setX(borderWidth * offset);
    rect.setY(borderWidth);
    rect.setWidth(width() - borderWidth * offset * 2);
    rect.setHeight(height() - borderWidth * 2);

    Qt::Alignment alignment = Qt::AlignCenter;
    if (textAlign == TextAlign_Top_Left) {
        alignment = Qt::AlignTop | Qt::AlignLeft;
    } else if (textAlign == TextAlign_Top_Center) {
        alignment = Qt::AlignTop | Qt::AlignHCenter;
    } else if (textAlign == TextAlign_Top_Right) {
        alignment = Qt::AlignTop | Qt::AlignRight;
    } else if (textAlign == TextAlign_Center_Left) {
        alignment = Qt::AlignLeft | Qt::AlignVCenter;
    } else if (textAlign == TextAlign_Center_Center) {
        alignment = Qt::AlignHCenter | Qt::AlignVCenter;
    } else if (textAlign == TextAlign_Center_Right) {
        alignment = Qt::AlignRight | Qt::AlignVCenter;
    } else if (textAlign == TextAlign_Bottom_Left) {
        alignment = Qt::AlignBottom | Qt::AlignLeft;
    } else if (textAlign == TextAlign_Bottom_Center) {
        alignment = Qt::AlignBottom | Qt::AlignHCenter;
    } else if (textAlign == TextAlign_Bottom_Right) {
        alignment = Qt::AlignBottom | Qt::AlignRight;
    }

    painter->setPen(textColor);
    painter->setFont(textFont);
    painter->drawText(rect, alignment, text);

    painter->restore();
}

int OColorButton::getBorderRadius() const
{
    return borderRadius;
}

int OColorButton::getBorderWidth() const
{
    return borderWidth;
}

QColor OColorButton::getBorderColor() const
{
    return borderColor;
}

bool OColorButton::getShowSuperText() const
{
    return showSuperText;
}

QString OColorButton::getSuperText() const
{
    return superText;
}

QFont OColorButton::getSuperTextFont() const
{
    return superTextFont;
}

OColorButton::TextAlign OColorButton::getSuperTextAlign() const
{
    return superTextAlign;
}

QColor OColorButton::getSuperTextColor() const
{
    return superTextColor;
}

QString OColorButton::getText() const
{
    return text;
}

QFont OColorButton::getTextFont() const
{
    return textFont;
}

OColorButton::TextAlign OColorButton::getTextAlign() const
{
    return textAlign;
}

QColor OColorButton::getTextColor() const
{
    return textColor;
}

QColor OColorButton::getNormalColor() const
{
    return normalColor;
}

QColor OColorButton::getPressedColor() const
{
    return pressedColor;
}

bool OColorButton::getCanMove() const
{
    return canMove;
}

QPixmap OColorButton::getBgImage() const
{
    return bgImage;
}

OColorButton::ColorMode OColorButton::getColorMode() const
{
    return colorMode;
}

QSize OColorButton::sizeHint() const
{
    return QSize(100,25);
}

QSize OColorButton::minimumSizeHint() const
{
    return QSize(100,25);

}

void OColorButton::setBorderRadius(int borderRadius)
{
    this->borderRadius = borderRadius;
}

void OColorButton::setBorderWidth(int borderWidth)
{
    this->borderWidth = borderWidth;

}

void OColorButton::setBorderColor(const QColor &borderColor)
{
    this->borderColor = borderColor;

}

void OColorButton::setShowSuperText(bool showSuperText)
{
    this->showSuperText = showSuperText;

}

void OColorButton::setSuperText(const QString &superText)
{
    this->superText = superText;

}

void OColorButton::setSuperTextFont(const QFont &superTextFont)
{
    this->superTextFont = superTextFont;

}

void OColorButton::setSuperTextAlign(const OColorButton::TextAlign &superTextAlign)
{
    this->superTextAlign = superTextAlign;

}

void OColorButton::setSuperTextColor(const QColor &superTextColor)
{
    this->superTextColor = superTextColor;

}

void OColorButton::setText(const QString &text)
{
    this->text = text;

}

void OColorButton::setTextFont(const QFont &textFont)
{
    this->textFont = textFont;

}

void OColorButton::setTextAlign(const OColorButton::TextAlign &textAlign)
{
    this->textAlign = textAlign;

}

void OColorButton::setTextColor(const QColor &textColor)
{
    this->textColor = textColor;

}

void OColorButton::setNormalColor(const QColor &normalColor)
{
    this->normalColor = normalColor;

}

void OColorButton::setPressedColor(const QColor &pressedColor)
{
    this->pressedColor = pressedColor;

}

void OColorButton::setCanMove(bool canMove)
{
    this->canMove = canMove;

}

void OColorButton::setBgImage(const QPixmap &bgImage)
{
    this->bgImage = bgImage;

}

void OColorButton::setColorMode(const OColorButton::ColorMode &colorMode)
{
    this->colorMode = colorMode;

}

