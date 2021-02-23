#include <cstring>
#include <algorithm>
#include <QDebug>
#include "packetswapper.h"



PacketSwapper::PacketSwapper(Packet* packet, Packet* packet1):
    is_newPacketUSB0(false),
    is_newPacketUSB1(false),
    p_packet(packet),
    p_packet1(packet1)

{
    m_buff_usb0.resize(p_packet->getSizePayload());
    m_buff_usb1.resize(p_packet1->getSizePayload());
}

bool PacketSwapper::createPacketUDP() {
   memset(m_packetUDP.packet.data, 0, 14);
   p_packet->lock();
   mutex.lock();

   if(is_newPacketUSB0) {
       std::copy(m_buff_usb0.begin(), m_buff_usb0.end() , m_packetUDP.packet.data);
       is_newPacketUSB0 = false;
   }


   mutex.unlock();
   p_packet->unlock();

   p_packet1->lock();
   mutex1.lock();

   if(is_newPacketUSB1) {
        std::copy(m_buff_usb1.begin(), m_buff_usb1.end() , m_packetUDP.packet.data + p_packet->getSizePayload());
        is_newPacketUSB1 = false;
   }


   mutex1.unlock();
   p_packet1->unlock();
   QByteArray byteArray;
   uchar* ptr_packet = reinterpret_cast<uchar*>(&m_packetUDP.packet);

   for(size_t i = 0; i < sizeof (m_packetUDP.packet); i++) {
       byteArray.append(ptr_packet[i]);
   }
   // sending result data
   m_udpSender.sendData(byteArray);
   m_packetUDP.packet.index++;
   return true;
}

void PacketSwapper::checkUSB0()
{
    if(p_packet->isUpdated()) {
        mutex.lock();
        std::copy(p_packet->getPayloadData(), p_packet->getPayloadData() + p_packet->getSizePayload(), m_buff_usb0.begin());
        qDebug() << "it is from a mesagesender";
        qDebug() << m_buff_usb0;
        is_newPacketUSB0 = true;
        p_packet->setOldData();
        mutex.unlock();
    }
}

void PacketSwapper::checkUSB1()
{
    if(p_packet1->isUpdated()) {
        mutex1.lock();
        std::copy(p_packet1->getPayloadData(), p_packet1->getPayloadData() + p_packet1->getSizePayload(), m_buff_usb1.begin());
        is_newPacketUSB1 = true;
        p_packet1->setOldData();
        mutex1.unlock();
    }
}
