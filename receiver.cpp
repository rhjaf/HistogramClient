
#include "receiver.h"
#include "iostream"
Receiver::Receiver(QObject *parent ,QHostAddress host,qint16 port):QObject(parent){
    m_socket = new QUdpSocket(this);
    m_socket->bind(host,port);
    connect(m_socket, &QUdpSocket::readyRead, this, &Receiver::readData);
}

void Receiver::readData()
    {
        while (m_socket->hasPendingDatagrams()) {
            QByteArray data;
            data.resize(m_socket->pendingDatagramSize());
            m_socket->readDatagram(data.data(), data.size());
            emit dataReady(data);
        }
    };
