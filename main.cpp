
#include "mainwindow.h"
#include "qthread.h"
#include "receiver.h"
#include "histogram.h"
#include <QApplication>
#include <QMutex>
#include <QChart>
#include <QPushButton>
#include <QChartView>
#include <QTimer>
#include <QSlider>
#include <QObject>
#include <QLabel>
#include <QtNetwork/QUdpSocket>


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow window;
    window.setWindowTitle( "Client Histogram" );


    QThread rthread;
    QTimer   *rtimer = new QTimer();
    rtimer->setInterval(1000);
    Receiver* receiver = new Receiver();
    receiver->moveToThread(&rthread);
    rthread.start();
    window.show();

    QChartView *histogramchartview = window.findChild<QChartView*>("histogramchartview");
    QChart *histogramchart = histogramchartview->chart();
    QLabel *frequencylabel = window.findChild<QLabel*>("frequencylabel");
    QPushButton *frequencybutton = window.findChild<QPushButton*>("frequencybtn");
    QSlider *frequencyslider = window.findChild<QSlider*>("frequencyslider");
    Histogram *histogram = new Histogram(histogramchart,histogramchartview);

    QObject::connect(frequencybutton,&QPushButton::clicked,[&](){
        rtimer->stop();
        rtimer->setInterval(frequencyslider->value());
        rtimer->start();
    });
    QObject::connect(frequencyslider,&QSlider::valueChanged,[&](){frequencylabel->setText(QString::number(frequencyslider->value()));});

    QObject::connect(receiver,&Receiver::dataReady,histogram,&Histogram::updatePlot);
    QObject::connect( rtimer, &QTimer::timeout, histogram,&Histogram::replot );

    rtimer->start();



    return a.exec();

}
