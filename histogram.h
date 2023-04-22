
#ifndef HISTOGRAM_H
#define HISTOGRAM_H


#include <QObject>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <QChartView>

class Histogram : public QObject
{
    Q_OBJECT
    QChart *m_histogram;
    QChartView *m_chartview;
    QHash<QString, int> m_counts;
    QBarSet *m_set = new QBarSet("Counts");
    QStringList m_categories;
    QBarSeries *m_series;
    QValueAxis *m_axisY;
public:
    explicit Histogram(QChart *histogramWidget,QChartView *chartView,QObject *parent = nullptr);

public slots:
    virtual void updatePlot(QByteArray data);
    virtual void replot();


};

#endif // HISTOGRAM_H
