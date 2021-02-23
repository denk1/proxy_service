#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QObject>
#include <QUdpSocket>

class UdpSender : public QObject
{
    Q_OBJECT
public:
    UdpSender();
    void sendData(QByteArray msg);
private:
    QUdpSocket* p_socket;
    QHostAddress m_address;
};

#endif // UDPSENDER_H
