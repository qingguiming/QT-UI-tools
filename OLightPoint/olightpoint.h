#ifndef OLIGHTPOINT_H
#define OLIGHTPOINT_H



/**
 * 呼吸点控件
 * 1:可设置呼吸间隔
 * 2:可设置颜色透明渐变步长
 * 3:可设置背景颜色
 */

#include <QWidget>


#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT OLightPoint : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int step READ getStep WRITE setStep)
    Q_PROPERTY(int interval READ getInterval WRITE setInterval)
    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)

public:
    explicit OLightPoint(QWidget *parent = 0);
    ~OLightPoint();

protected:
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);

private:
    int step;                       //颜色透明渐变步长
    int interval;                   //定时器间隔
    QColor bgColor;                 //背景颜色

    QTimer *timer;                  //绘制定时器
    int offset;                     //偏移量
    bool add;                       //是否增加

public:
    int getStep()                   const;
    int getInterval()               const;
    QColor getBgColor()             const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public slots:
    //设置颜色透明渐变步长
    void setStep(int step);

    //设置定时器间隔
    void setInterval(int interval);

    //设置背景颜色
    void setBgColor(const QColor &bgColor);

};


#endif
