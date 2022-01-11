#include "oadswidget.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QTimer>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QLabel>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QTimer>

OAdsWidget::OAdsWidget(QWidget *parent) :
    QWidget(parent)
{
    initWidget();
    initForm();
    initQss();
//    qDebug()<<width();
}

OAdsWidget::~OAdsWidget()
{

}

bool OAdsWidget::eventFilter(QObject *obj, QEvent *event)
{

    for(int i = 0 ; i <labs.size();i++)
    {
        if(obj == (QObject*)labs[i] && event->type() == QEvent::MouseButtonPress)
        {
//            qDebug()<<"eventFilter";
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
           if(mouseEvent->buttons()&Qt::LeftButton)
           {
//               qDebug()<<"eventFilter LeftButton" << i <<currentIndex;
               changedAds(i);

           }

        }
    }
    return QWidget::eventFilter(obj,event);
}

void OAdsWidget::enterEvent(QEvent *)
{
    if(hoverStop)
    {
        if(timer->isActive())
        {
            timer->stop();
        }
    }
//    qDebug()<<"enterEvent";

//    setCursor(Qt::CrossCursor);
}

void OAdsWidget::leaveEvent(QEvent *)
{
    if(hoverStop)
    {
        if(!timer->isActive())
        {
            timer->start();
        }
    }
}

void OAdsWidget::showEvent(QShowEvent *)
{

}
void OAdsWidget::paintEvent(QPaintEvent *)
{
    if (names.count() == 0) {
        return;
    }

    int width = this->width();
    int height = this->height();

    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
    painter.setPen(tipColor);

    //设置字体
    QFont font;
    font.setPixelSize(15);
    painter.setFont(font);

    //取出上一张图片+当前图片,并平滑缩放
//    qDebug()<<"paintEvent"<<previousIndex << currentIndex;
    QPixmap previousPix(names.at(previousIndex));
    QPixmap currentPix(names.at(currentIndex));
    previousPix = previousPix.scaled(width, height, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    currentPix = currentPix.scaled(width, height, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    int widthOffset = offset + width;
    if (leftToRight) {
        widthOffset = offset - width;
    }
//    qDebug()<< offset << widthOffset  << width;
    //绘制上一张图片
    painter.drawPixmap(offset, 0, previousPix);
    //绘制当前图片
    painter.drawPixmap(widthOffset, 0, currentPix);

    //绘制上一张图片提示信息,有可能上一张图片提示信息为空
    if (previousIndex <= tips.count() - 1) {
        painter.drawText(QRect(offset + 10, height - minHeight - 40, width - 20, 30), tips.at(previousIndex), option);
    }

    //绘制当前图片提示信息,有可能当前图片提示信息为空
    if (currentIndex <= tips.count() - 1) {
        painter.drawText(QRect(widthOffset + 10, height - minHeight - 40, width - 20, 30), tips.at(currentIndex), option);
    }
}

void OAdsWidget::initWidget()
{
    //放置指示器的窗体载体
    widgetNav = new QWidget(this);
    widgetNav->setObjectName(QString::fromUtf8("widgetNav"));

    //给指示器窗体加上左右布局
    layout = new QHBoxLayout(widgetNav);
    layout->setSpacing(3);
    widgetNav->setLayout(layout);

    //主布局,上下布局
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    //上部弹簧,用于将指示器区域弹到底部
    QSpacerItem *verticalSpacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalLayout->addItem(verticalSpacer);

    //将指示器窗体加入到主布局中下部
    verticalLayout->addWidget(widgetNav);

    //实例化左侧右侧弹簧
    spacerLeft = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    spacerRight = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

//    QLabel *l = new QLabel("123");
//    layout->addWidget(l);
}

void OAdsWidget::initForm()
{
    hoverStop = true;
    showNumber = false;

    minHeight = 6;
    minWidth = 16;
    maxWidth = 50;
    interval = 3000;
    navRadius = 3;

    navColor = QColor(220, 220, 220);
    textColor = QColor(20, 20, 20);
    tipColor = QColor(255, 255, 255);
    darkColor = QColor(255, 255, 255);

    imageNames.clear();
    imageTips.clear();

    navPosition = NavPosition_Right;
    navStyle = NavStyle_Ellipse;

    leftToRight = true;
    offset = 0;
    currentIndex = 0;
    previousIndex = 0;

    //定时器切换图片
    timer = new QTimer(this);
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(changedAds()));

    this->setMouseTracking(true);

    //定义动画组
    animationGroup = new QParallelAnimationGroup(this);

    //定义动画切换图片
    animationImage = new QPropertyAnimation(this, "");
    connect(animationImage, SIGNAL(valueChanged(const QVariant &)), this, SLOT(changedImage(const QVariant &)));
    animationImage->setEasingCurve(QEasingCurve::OutCirc);
    animationImage->setDuration(1000);
    animationGroup->addAnimation(animationImage);

    QSequentialAnimationGroup *sequentialGroup = new QSequentialAnimationGroup(animationGroup);

    //用于切换最小拉伸宽度
    animationMin = new QPropertyAnimation(sequentialGroup, "");
    connect(animationMin, SIGNAL(valueChanged(const QVariant &)), this, SLOT(changedMin(const QVariant &)));
    animationMin->setEasingCurve(QEasingCurve::OutCubic);
    animationMin->setDuration(500);

    //用于切换最大拉伸宽度
    animationMax = new QPropertyAnimation(sequentialGroup, "");
    connect(animationMax, SIGNAL(valueChanged(const QVariant &)), this, SLOT(changedMax(const QVariant &)));
    animationMax->setEasingCurve(QEasingCurve::OutCubic);
    animationMax->setDuration(500);

    //按钮切换串行运行
    sequentialGroup->addAnimation(animationMin);
    sequentialGroup->addAnimation(animationMax);
    animationGroup->addAnimation(sequentialGroup);
}

void OAdsWidget::initQss()
{
    //可自行拓展自定义样式
    if (navStyle == NavStyle_Dot) {
        qssNormal = QString("border:none;background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,"
                            "stop:0 #00FFFFFF,stop:0.4 #00FFFFFF,"
                            "stop:0.5 #00FFFFFF,stop:0.6 #00FFFFFF,stop:0.7 rgba(%1,%2,%3,%4));"
                            "color:rgba(%5,%6,%7,%8);border-radius:%9px;")
                .arg(navColor.red()).arg(navColor.green()).arg(navColor.blue()).arg(navColor.alpha())
                .arg(textColor.red()).arg(textColor.green()).arg(textColor.blue()).arg(navColor.alpha()).arg(navRadius);
        qssCurrent = QString("border:none;background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,"
                             "stop:0 rgba(%1,%2,%3,%4),stop:0.4 rgba(%1,%2,%3,%4),"
                             "stop:0.5 #00FFFFFF,stop:0.6 #00FFFFFF,stop:0.7 rgba(%1,%2,%3,%4));"
                             "color:rgba(%5,%6,%7,%8);border-radius:%9px;")
                .arg(darkColor.red()).arg(darkColor.green()).arg(darkColor.blue()).arg(darkColor.alpha())
                .arg(textColor.red()).arg(textColor.green()).arg(textColor.blue()).arg(navColor.alpha()).arg(navRadius);

    } else {
        qssNormal = QString("border:none;background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);border-radius:%9px;")
                .arg(navColor.red()).arg(navColor.green()).arg(navColor.blue()).arg(navColor.alpha())
                .arg(textColor.red()).arg(textColor.green()).arg(textColor.blue()).arg(navColor.alpha()).arg(navRadius);
        qssCurrent = QString("border:none;background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);border-radius:%9px;")
                .arg(darkColor.red()).arg(darkColor.green()).arg(darkColor.blue()).arg(darkColor.alpha())
                .arg(textColor.red()).arg(textColor.green()).arg(textColor.blue()).arg(textColor.alpha()).arg(navRadius);
    }
}

void OAdsWidget::changedAds()
{
    if (names.count() == 0) {
        return;
    }

    previousIndex = currentIndex;
    if (currentIndex < names.count() - 1) {
        currentIndex++;
    } else {
        currentIndex = 0;
    }
//    qDebug()<<"currentIndex" << currentIndex;
    update();
//    changedAds(labs.at(currentIndex));

    animationImage->setStartValue(0);
    animationImage->setEndValue(width());

    animationMin->setStartValue(minWidth);
    animationMin->setEndValue(maxWidth);


    animationMax->setStartValue(maxWidth);
    animationMax->setEndValue(minWidth);

    labs.at(currentIndex)->setStyleSheet(qssCurrent);


    animationGroup->start();

}

void OAdsWidget::changedAds(int index)
{
    if (names.count() == 0) {
        return;
    }

    if(currentIndex == index) return;

    if(currentIndex == 0)
    {
        previousIndex = names.count() - 1;
    }
    else
    {
        previousIndex = currentIndex - 1;
    }
    currentIndex = index;

    update();
//    changedAds(labs.at(currentIndex));

    animationImage->setStartValue(0);
    animationImage->setEndValue(width());

    animationMin->setStartValue(minWidth);
    animationMin->setEndValue(maxWidth);


    animationMax->setStartValue(maxWidth);
    animationMax->setEndValue(minWidth);

    labs.at(currentIndex)->setStyleSheet(qssCurrent);


    animationGroup->start();
}

void OAdsWidget::changedImage(const QVariant &variant)
{
    offset = variant.toInt();
    update();
}

void OAdsWidget::changedMin(const QVariant &variant)
{
    labs.at(currentIndex)->setFixedWidth(variant.toInt());
}

void OAdsWidget::changedMax(const QVariant &variant)
{
    for (int index = 0; index < labs.size(); index++)
    {
        if (currentIndex != index && labs[index]->width() > minWidth)
        {
//            qDebug()<<"changedMax currentIndex" << currentIndex;
           labs[index]->setFixedWidth(variant.toInt());
        }
    }

}

bool OAdsWidget::getHoverStop() const
{
    return hoverStop;
}

bool OAdsWidget::getShowNumber() const
{
    return showNumber;
}

int OAdsWidget::getMinHeight() const
{
    return minHeight;
}

int OAdsWidget::getMinWidth() const
{
    return minWidth;
}

int OAdsWidget::getMaxWidth() const
{
    return maxWidth;
}

int OAdsWidget::getInterval() const
{
    return interval;
}

int OAdsWidget::getNavRadius() const
{
    return navRadius;
}

QColor OAdsWidget::getNavColor() const
{
    return navColor;
}

QColor OAdsWidget::getTextColor() const
{
    return textColor;
}

QColor OAdsWidget::getTipColor() const
{
    return tipColor;
}

QColor OAdsWidget::getDarkColor() const
{
    return darkColor;
}

QString OAdsWidget::getImageNames() const
{
    return imageNames;
}

QString OAdsWidget::getImageTips() const
{
    return imageTips;
}

OAdsWidget::NavPosition OAdsWidget::getNavPosition() const
{
    return navPosition;
}

OAdsWidget::NavStyle OAdsWidget::getNavStyle() const
{
    return navStyle;
}

QSize OAdsWidget::sizeHint() const
{
    return QSize(100,100);
}

QSize OAdsWidget::minimumSizeHint() const
{
    return QSize(100,100);

}

void OAdsWidget::setHoverStop(bool hoverStop)
{
    this->hoverStop = hoverStop;
}

void OAdsWidget::setShowNumber(bool showNumber)
{
    this->showNumber = showNumber;

}

void OAdsWidget::setMinHeight(int minHeight)
{
    this->minHeight = minHeight;

}

void OAdsWidget::setMinWidth(int minWidth)
{
    this->minWidth = minWidth;

}

void OAdsWidget::setMaxWidth(int maxWidth)
{
    this->maxWidth = maxWidth;

}

void OAdsWidget::setInterval(int interval)
{
    this->interval = interval;

}

void OAdsWidget::setNavRadius(int navRadius)
{
    this->navRadius = navRadius;

}

void OAdsWidget::setNavColor(const QColor &navColor)
{
    this->navColor = navColor;

}

void OAdsWidget::setTextColor(const QColor &textColor)
{
    this->textColor = textColor;

}

void OAdsWidget::setTipColor(const QColor &tipColor)
{
    this->tipColor = tipColor;

}

void OAdsWidget::setDarkColor(const QColor &darkColor)
{
    this->darkColor = darkColor;

}

void OAdsWidget::setImageNames(const QString &imageNames)
{
    if (this->imageNames != imageNames)
    {

        this->imageNames = imageNames;

        //先清空原有所有指示器
        qDeleteAll(labs);
        labs.clear();

        if(navPosition != NavPosition_Left)
        {
            layout->addSpacerItem(spacerLeft);
        }

        //根据图片链表自动生成导航指示器和图片链表
        names = this->imageNames.split(";");
        for (int i = 0; i < names.count(); i++)
        {
            QLabel *lab = new QLabel;
            if(showNumber)
            {
                lab->setText(QString::number(i + 1));

            }

            layout->addWidget(lab);
            lab->setMinimumHeight(minHeight);
            lab->setMinimumWidth((minWidth));
            lab->setMaximumWidth(maxWidth);
            lab->setAlignment(Qt::AlignCenter);
            lab->setStyleSheet(qssNormal);
            lab->installEventFilter(this);

//            qDebug()<<QString::number(i + 1) << minHeight << minWidth << maxWidth;


            labs.append(lab);
        }

        if(navPosition != NavPosition_Right)
        {
            layout->addSpacerItem(spacerRight);
        }

        //立即显示第一张
        changedAds();
    }




}

void OAdsWidget::setImageTips(const QString &imageTips)
{
    this->imageTips = imageTips;

}

void OAdsWidget::setNavPosition(const OAdsWidget::NavPosition &navPosition)
{
    this->navPosition = navPosition;

}

void OAdsWidget::setNavStyle(const OAdsWidget::NavStyle &navStyle)
{
    this->navStyle = navStyle;

}

