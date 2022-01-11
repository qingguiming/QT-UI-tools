#ifndef OMOVEWIDGET_H
#define OMOVEWIDGET_H

#include <QWidget>
#include <QPushButton>



/**
 * 通用控件移动类 作者:feiyangqingyun(QQ:517216493) 2019-9-28
 * 1:可以指定需要移动的widget
 * 2:可设置是否限定鼠标左键拖动
 * 3:支持任意widget控件
 */

#include <QWidget>


#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT OMoveWidget : public QPushButton
{
    Q_OBJECT
public:
    explicit OMoveWidget(QWidget *parent = 0);


};


#endif
