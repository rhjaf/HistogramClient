
#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QtNetwork/QUdpSocket>

class Receiver : public QObject
{
    Q_OBJECT
public:
    Receiver(QObject *parent= nullptr,QHostAddress host=QHostAddress::LocalHost,qint16 port = 8090);
public:
    void start();

signals:
    void dataReady(QByteArray data);

private slots:
    void readData();

private:
    QUdpSocket *m_socket;






};

#endif // RECEIVER_H
