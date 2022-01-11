#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "mywidget.h"
#include <QList>
#include <QTime>
#include <QTimer>
#include <QDate>

double get_random_number(int i)
{
     qsrand(QTime(0,0,0).secsTo(QTime::currentTime()) + i*211);
     int a = qrand()%100;   //随机生成0到9的随机数

     //qDebug()<< a;
     return a*1.0;
 }

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //setMouseTracking(true);

    ui->setupUi(this);
//    _PlayPos = 0;
//    QList<float> audioData;
//    for(int i = 0; i < 50;i++)
//    {
//        float temp = get_random_number(i);
//        audioData.append(temp);
//    }

//    ui->oAudioWaveWidget->setData(audioData);
//    ui->oAudioWaveWidget->setLength(500);

//    QTimer *audioTimer = new QTimer();
//    audioTimer->setInterval(80);

//    connect(audioTimer,SIGNAL(timeout()),this,SLOT(timeout()));
//    audioTimer->start();




//    for(int i = 0; i < 2000;i++)
//    {
//        float temp = get_random_number(i);
//        qDebug()<<temp;
//        _WaveLineData.append(temp);
//    }

//    QTimer *waveLineTimer = new QTimer();
//    waveLineTimer->setInterval(500);

//    connect(waveLineTimer,&QTimer::timeout,this,[=](){
//        ui->oWaveLine->setData(_WaveLineData.mid(0,137));
//        _WaveLineData.remove(0,31);
//    });
//    connect(waveLineTimer,SIGNAL(timeout()),ui->oWaveLine,SLOT(updateData()));
//    waveLineTimer->start();


    ui->oAnimationButton->setImage(":/image/no.png");
    ui->oAnimationButton->setText("222");

    //轮播图


        QStringList list;
        list << ":/image/0.jpg" << ":/image/1.png" << ":/image/2.jpeg";
        QString str = list.join(";");
        ui->oAdsWidget->setImageNames(str);
//        ui->oAdsWidget->changedAds();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeout()
{
    ui->oAudioWaveWidget->setPosition(_PlayPos);
    _PlayPos += 1;
}

//void MainWindow::mousePressEvent(QMouseEvent *)
//{
//    qDebug()<<"MainWindow::mousePressEvent";
//}

void MainWindow::on_pushButton_clicked()
{
    ui->oWaveBar->setValue(80);
    ui->oWaveBar->start();

    ui->oWaveBar_2->setValue(400);
    ui->oWaveBar_2->start();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->oWaveDouble->setValue(50);
    ui->oWaveDouble->setStep(1);
    ui->oWaveDouble->start();

}

void MainWindow::on_pushButton_3_clicked()
{
    ui->oWaveDouble->setValue(20);
    ui->oWaveDouble->setStep(1);

    ui->oWaveDouble->start();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->oWavePlot->start();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->oWavePlot->stop();

}

//速度
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if(value < 1) value = 1;
    ui->oWavePlot->setInterval(1000 / value);
}
//高度
void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    if(value < 1) value = 1;
    ui->oWavePlot->setWaterHeight(value);
}
//密度
void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    if(value < 1) value = 1;
    ui->oWavePlot->setWaterDensity(value);
}

void MainWindow::on_pushButton_6_clicked()
{
    QStringList list;

    list << "2011"<<"build1";
    list << "2012"<<"build2";
    list << "2013"<<"build3";
    list << "2014"<<"build4";
    list << "2015"<<"build5";
    list << "2013"<<"build3";
    list << "2014"<<"build4";
    list << "2015"<<"build5";
    list << "2013"<<"build3";
    list << "2014"<<"build4";
    list << "2015"<<"build5";


    ui->oTimeAxisWidget->setInfos(list.join(','));
}

void MainWindow::on_pushButton_7_clicked()
{
}

void MainWindow::on_pushButton_8_clicked()
{
    QDate da = QDate::currentDate();
    ui->oShadowCalendar->updateCalendar(da);

}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    ui->oGaugeCompass->setValue(value);
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    ui->oRulerProgress->setValue(value);
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    ui->oGaugeSpeed->setValue(value);
}

void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    ui->oRulerProgress->setValue(value);
}

void MainWindow::on_horizontalSlider_6_actionTriggered(int action)
{
}

void MainWindow::on_tabWidget_currentChanged(int index)
{

}

void MainWindow::on_horizontalSlider_6_valueChanged(int value)
{
    ui->oGaugeCar->setValue(value);

}

void MainWindow::on_horizontalSlider_7_valueChanged(int value)
{
    ui->oProgressRing->setValue(value);
    ui->oProgressRing_2->setValue(value);
    ui->oProgressRing_3->setValue(value);

}

void MainWindow::on_pushButton_9_clicked()
{
    QList<QColor> colors;
    colors.append(Qt::red);
    colors.append(Qt::black);
    colors.append(Qt::blue);

    ui->oCustomPie->setColors(colors);

    ui->oCustomPie->appendPie("jige",40);
    ui->oCustomPie->appendPie("you",30);
    ui->oCustomPie->appendPie("liang",30);

    ui->oCustomPie->loadPercent();



}

void MainWindow::on_pushButton_10_clicked()
{
    ui->oImageAnimation->start();
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->oLightButton->startAlarm();
}

void MainWindow::on_horizontalSlider_8_valueChanged(int value)
{
    ui->oBattery->setValue(value);
}
