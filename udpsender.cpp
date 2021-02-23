#include "udpsender.h"

UdpSender::UdpSender():
    m_address("127.0.0.1")
{
    p_socket = new QUdpSocket(this);

}

void UdpSender::sendData(QByteArray msg)
{
    p_socket->writeDatagram(msg, m_address, 10000);
}
