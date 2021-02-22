#ifndef PACKETSWAPPER_H
#define PACKETSWAPPER_H

#include <QMutex>
#include <vector>
#include "packet.h"
#include "packetudp.h"

class PacketSwapper
{
public:
    PacketSwapper(Packet* packet, Packet* packet1);
    bool createPacketUDP();
    void checkUSB0();
    void checkUSB1();
private:


    bool is_newPacketUSB0;
    bool is_newPacketUSB1;

    std::vector<uchar> m_buff_usb0;
    std::vector<uchar> m_buff_usb1;
    PacketUDP m_packetUDP;
    Packet* p_packet;
    Packet* p_packet1;
    QMutex mutex;
    QMutex mutex1;

};

#endif // PACKETSWAPPER_H
