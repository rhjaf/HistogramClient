
#include "histogram.h"
#include "receiver.h"
#include <QCategoryAxis>
#include <QBarCategoryAxis>
#include <iostream>

bool compare(QString a, QString b) {
    int x = stoi(a.toStdString().substr(0, a.toStdString().find("-")));
    int y = stoi(b.toStdString().substr(0, b.toStdString().find("-")));
    return (x < y);
}


Histogram::Histogram(QChart *histogramWidget,QChartView *chartView,QObject *parent)
    : m_histogram(histogramWidget),m_chartview(chartView),QObject(parent){

    for (int i = 0; i < 20; i++) {
        QString range = QString::number(i * 5 + 1) + "-" + QString::number((i + 1) * 5);
        m_counts[range] = 0;
    }
    m_categories = m_counts.keys();
    std::sort(m_categories.begin(), m_categories.end(),compare);
    for (const QString& range : m_categories) {
        histogramWidget->addAxis(new QCategoryAxis(), Qt::AlignRight);

    }
    m_series = new QBarSeries();

    histogramWidget->addSeries(m_series);
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(m_categories);
    histogramWidget->addAxis(axisX, Qt::AlignBottom);
    m_series->attachAxis(axisX);
    m_axisY = new QValueAxis();
    m_histogram->addAxis(m_axisY, Qt::AlignLeft);
    m_series->attachAxis(m_axisY);

    QObject::connect(m_series, &QBarSeries::hovered, [&]( bool status, int index,QBarSet *barSet) {
        if (status) {
            QString range = m_categories[index];
            int count = m_counts[range];
            chartView->setToolTip(QString("%1: %2").arg(range).arg(count));
            chartView->setCursor(Qt::PointingHandCursor);
        } else {
            chartView->setToolTip("");
            chartView->setCursor(Qt::ArrowCursor);
        }
    });

}

void Histogram::updatePlot(QByteArray data)
{
    QList<int> numbers;
    QStringList substrings = QString::fromUtf8(data).split(",");

    for (const QString& substring : substrings) {
        bool ok;
        int intValue = substring.toInt(&ok);
        if(intValue>0 && intValue<100)
            numbers.append(intValue);
    }

    for (int number : numbers) {
        int lowerBound = (number/5) * 5 + 1;
        int upperBound = (number/5+1) * 5;
        QString range = QString::number(lowerBound) + "-" + QString::number(upperBound);
        m_counts[range]++;
    }

}

void Histogram::replot()
{
    m_set->remove(0,m_set->count());
    for (const QString& range : m_categories)
        *m_set << m_counts[range];
    m_series->append(m_set);
    int maxCount = 0;
    for (auto it = m_counts.constBegin(); it != m_counts.constEnd(); ++it)
        maxCount = qMax(maxCount, it.value());
    m_axisY->setRange(0, maxCount);
}
