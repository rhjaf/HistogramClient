
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QtCharts>
#include <iostream>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout* vLayout = new QVBoxLayout();
    QWidget* centeralWidget = new QWidget();



    QFrame *infoFrame = new QFrame();
    QHBoxLayout *infoLayout = new QHBoxLayout();
    infoFrame->setLayout( infoLayout );
    QLabel* frequencylabel = new QLabel("1000");
    frequencylabel->setObjectName("frequencylabel");
    QLabel* frequencylabelms = new QLabel("ms");
    QPushButton* frequencybutton = new QPushButton("Start");
    frequencybutton->setObjectName("frequencybtn");
    QSlider *frequencyslider = new QSlider(Qt::Orientation::Horizontal);
    frequencyslider->setObjectName("frequencyslider");
    frequencyslider->setRange(50,1000);
    frequencyslider->setSingleStep(50);
    frequencyslider->setValue(1000);
    infoLayout->addWidget( frequencyslider );
    infoLayout->addWidget( frequencylabel );
    infoLayout->addWidget( frequencylabelms );
    infoLayout->addWidget( frequencybutton );
    infoFrame->setLayout( infoLayout );



    //histogram
    QChart *chart = new QChart();
    chart->setObjectName("histogramchart");
    chart->setTitle("Frequency count");

    QChartView *chartView = new QChartView(chart);
    chartView->setObjectName("histogramchartview");
    chartView->setRenderHint(QPainter::Antialiasing);





    vLayout->addWidget( infoFrame );
    vLayout->addWidget(chartView);

    centeralWidget->setLayout( vLayout );


    this->setCentralWidget(centeralWidget);



}

MainWindow::~MainWindow()
{
    delete ui;
}

