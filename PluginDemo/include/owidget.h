#ifndef OWIDGET_H
#define OWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT OWidget : public QWidget
{
    Q_OBJECT

public:
    OWidget(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e);

};

#endif
