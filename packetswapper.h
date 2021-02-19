#ifndef PACKETSWAPPER_H
#define PACKETSWAPPER_H

#include <QMutex>
#include "packet.h"
#include "PacketUSB0.h"
#include "PacketUSB1.h"
#include "packetudp.h"

class PacketSwapper
{
public:
    PacketSwapper();
    void setValuePacketUSB0(uchar* data);
    void setValuePacketUSB1(uchar* data);
private:
    PacketUSB0 m_packetUSB0;
    PacketUSB1 m_packetUSB1;
    PacketUDP m_packetUDP;

    Packet m_income_packet;
    Packet m_income_packet1;
    Packet m_outcome_packet;

    QMutex m_mutex;
    QMutex m_mutex1;

    bool is_refreshUSB0;
    bool is_refreshUSB1;
};

#endif // PACKETSWAPPER_H
