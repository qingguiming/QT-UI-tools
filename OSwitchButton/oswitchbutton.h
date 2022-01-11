#ifndef OSWITCHBUTTON_H
#define OSWITCHBUTTON_H



/**
 *
 * 1:可设置开关按钮的样式 圆角矩形/内圆形/外圆形/图片
 * 2:可设置选中和未选中时的背景颜色
 * 3:可设置选中和未选中时的滑块颜色
 * 4:可设置显示的文本
 * 5:可设置滑块离背景的间隔
 * 6:可设置圆角角度
 */

#include <QWidget>

class QTimer;

#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT OSwitchButton : public QWidget
{
    Q_OBJECT
    Q_ENUMS(ButtonStyle)
    Q_PROPERTY(bool checked READ getChecked WRITE setChecked)
    Q_PROPERTY(ButtonStyle buttonStyle READ getButtonStyle WRITE setButtonStyle)
    Q_PROPERTY(QColor bgColorOff READ getBgColorOff WRITE setBgColorOff)
    Q_PROPERTY(QColor bgColorOn READ getBgColorOn WRITE setBgColorOn)
    Q_PROPERTY(QColor sliderColorOff READ getSliderColorOff WRITE setSliderColorOff)
    Q_PROPERTY(QColor sliderColorOn READ getSliderColorOn WRITE setSliderColorOn)
    Q_PROPERTY(QColor textColorOff READ getTextColorOff WRITE setTextColorOff)
    Q_PROPERTY(QColor textColorOn READ getTextColorOn WRITE setTextColorOn)
    Q_PROPERTY(QString textOff READ getTextOff WRITE setTextOff)
    Q_PROPERTY(QString textOn READ getTextOn WRITE setTextOn)

    Q_PROPERTY(QString imageOff READ getImageOff WRITE setImageOff)
    Q_PROPERTY(QString imageOn READ getImageOn WRITE setImageOn)

    Q_PROPERTY(int space READ getSpace WRITE setSpace)
    Q_PROPERTY(int rectRadius READ getRectRadius WRITE setRectRadius)




public:
    enum ButtonStyle {
        ButtonStyle_Rect = 0,     //圆角矩形
        ButtonStyle_CircleIn = 1, //内圆形
        ButtonStyle_CircleOut = 2,//外圆形
        ButtonStyle_Image = 3     //图片
    };

    OSwitchButton(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawSlider(QPainter *painter);
    void drawText(QPainter *painter);
    void drawImage(QPainter *painter);

private:
    bool checked;               //是否选中
    ButtonStyle buttonStyle;    //开关按钮样式

    QColor bgColorOff;          //关闭时背景颜色
    QColor bgColorOn;           //打开时背景颜色

    QColor sliderColorOff;      //关闭时滑块颜色
    QColor sliderColorOn;       //打开时滑块颜色

    QColor textColorOff;        //关闭时文本颜色
    QColor textColorOn;         //打开时文本颜色

    QString textOff;            //关闭时显示的文字
    QString textOn;             //打开时显示的文字

    QString imageOff;           //关闭时显示的图片
    QString imageOn;            //打开时显示的图片

    int space;                  //滑块离背景间隔
    int rectRadius;             //圆角角度

    int step;                   //每次移动的步长
    int startX;                 //滑块开始X轴坐标
    int endX;                   //滑块结束X轴坐标
    QTimer *timer;              //定时器绘制

private slots:
    void updateValue();

public:
    bool getChecked()const
    {
        return checked;
    }
    ButtonStyle getButtonStyle()const
    {
        return buttonStyle;
    }

    QColor getBgColorOff()const
    {
        return bgColorOff;
    }
    QColor getBgColorOn()const
    {
        return bgColorOn;
    }

    QColor getSliderColorOff()const
    {
        return sliderColorOff;
    }
    QColor getSliderColorOn()const
    {
        return sliderColorOn;
    }

    QColor getTextColorOff()const
    {
        return textColorOff;
    }
    QColor getTextColorOn()const
    {
        return textColorOn;
    }

    QString getTextOff()const
    {
        return textOff;
    }
    QString getTextOn()const
    {
        return textOn;
    }

    QString getImageOff()const
    {
        return imageOff;
    }
    QString getImageOn()const
    {
        return imageOn;
    }

    int getSpace()const
    {
        return space;
    }
    int getRectRadius()const
    {
        return rectRadius;
    }

public Q_SLOTS:
    //设置是否选中
    void setChecked(bool checked);
    //设置风格样式
    void setButtonStyle(ButtonStyle buttonStyle);

    //设置背景颜色
    void setBgColorOff(QColor bgColorOff);
    void setBgColorOn(QColor bgColorOn);
    void setBgColor(QColor bgColorOff, QColor bgColorOn);
    //设置滑块颜色
    void setSliderColor(QColor sliderColorOff, QColor sliderColorOn);
    void setSliderColorOff(QColor sliderColorOff);
    void setSliderColorOn(QColor sliderColorOn);



    //设置文本颜色
    void setTextColor(QColor textColorOff, QColor textColorOn);
    void setTextColorOff(QColor textColorOff);
    void setTextColorOn(QColor textColorOn);

    //设置文本
    void setText(QString textOff, QString textOn);
    void setTextOff(QString textOff);
    void setTextOn(QString textOn);




    //设置背景图片
    void setImage(QString imageOff, QString imageOn);
    void setImageOff(QString imageOff);
    void setImageOn(QString imageOn);



    //设置间隔
    void setSpace(int space);
    //设置圆角角度
    void setRectRadius(int rectRadius);

Q_SIGNALS:
    void checkedChanged(bool checked);
};

#endif // SWITCHBUTTON_H


