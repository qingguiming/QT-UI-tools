#ifndef OTILEDBG_H
#define OTILEDBG_H

/**
 * 平铺背景控件
 * 1:可设置交替背景颜色
 */

#include <QWidget>


#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif
class QDESIGNER_WIDGET_EXPORT OTiledBg : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color1 READ getColor1 WRITE setColor1)
    Q_PROPERTY(QColor color2 READ getColor2 WRITE setColor2)
    Q_PROPERTY(QPixmap bgPix READ getBgPix WRITE setBgPix)

public:
    explicit OTiledBg(QWidget *parent = 0);

protected:
    void drawBg();
    void paintEvent(QPaintEvent *);

private:
    QColor color1;              //颜色1
    QColor color2;              //颜色2
    QPixmap bgPix;              //背景图片

public:
    QColor getColor1()          const;
    QColor getColor2()          const;
    QPixmap getBgPix()          const;

    QSize sizeHint()            const;
    QSize minimumSizeHint()     const;

public slots:
    //设置颜色1
    void setColor1(const QColor &color1);
    //设置颜色2
    void setColor2(const QColor &color2);
    //设置背景图片
    void setBgPix(const QPixmap &bgPix);
};


#endif
