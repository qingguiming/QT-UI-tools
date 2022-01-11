#ifndef OANIMATIONBUTTON_H
#define OANIMATIONBUTTON_H



/**
 * 1:可设置显示的图像和底部的文字
 */

#include <QWidget>
#include <QVariant>

class QPropertyAnimation;

#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT OAnimationButton : public QWidget
{
    Q_OBJECT
public:
    OAnimationButton(QWidget *parent = 0);
    ~OAnimationButton();

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void paintEvent(QPaintEvent *);

private:
    bool enter;                         //是否进入
    bool leave;                         //是否离开
    int pixWidth;                       //图片宽度
    int pixHeight;                      //图片高度
    int oldWidth;                       //图片旧宽度
    int oldHeight;                      //图片旧高度

    QPropertyAnimation*enterAnimation; //进入动画
    QPropertyAnimation*leaveAnimation; //离开动画

    int targetWidth;                    //目标宽度
    int targetHeight;                   //目标高度
    QString text;                       //显示文字
    QString image;                      //图像路径

private slots:
    void enterImageChanged(QVariant index);
    void leaveImageChanged(QVariant index);

public slots:
    //设置显示的文字
    void setText(QString text);
    //设置显示的图像
    void setImage(QString image);
};


#endif
