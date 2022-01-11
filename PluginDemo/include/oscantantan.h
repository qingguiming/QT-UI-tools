#ifndef OSCANTANTAN_H
#define OSCANTANTAN_H


/**
 * 探探雷达控件 作者:东门吹雪(QQ:709102202) 整理:feiyangqingyun(QQ:517216493) 2019-10-01
 * 1:可设置中间图像
 * 2:可设置图像的边框宽度+边框颜色,产生圆形图像效果
 * 3:可设置扫描线的最大半径
 * 4:可设置扫描线的边框宽度
 * 5:可设置扩散圈的线条宽度
 * 6:可设置扫描线的每次移动的步长
 * 7:可设置扩散圈的每次移动的步长
 * 8:可设置扫描线的颜色
 * 9:可设置扩散圈的颜色
 */

#include <QWidget>

class QSequentialAnimationGroup;
class QTimer;


#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT OScanTanTan : public QWidget

{
    Q_OBJECT


public:


    explicit OScanTanTan(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);






};

#endif // SCANTANTAN_H

