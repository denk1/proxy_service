#include "packetswapper.h"

PacketSwapper::PacketSwapper():
    m_income_packet(m_packetUSB0.packet.header, m_packetUSB0.raw_data, sizeof(m_packetUSB0.raw_data)),
    m_income_packet1(m_packetUSB0.packet.header, m_packetUSB1.raw_data, sizeof(m_packetUSB0.raw_data)),
    m_outcome_packet(m_packetUSB1.packet.header, m_packetUDP.raw_data, sizeof(m_packetUDP.raw_data))


{
    PacketUSB0 packetUSB0;
    PacketUSB1 packetUSB1;
    size_t s = sizeof(packetUSB0.raw_data);

    size_t s1 = sizeof(packetUSB1.raw_data);

    Packet packet0(packetUSB0.packet.header, packetUSB0.raw_data, s);

    Packet packet1(packetUSB1.packet.header, packetUSB1.raw_data, s1);
}

void PacketSwapper::setValuePacketUSB0(uchar *data)
{
    m_mutex.lock();
    m_mutex.unlock();
}

void PacketSwapper::setValuePacketUSB1(uchar *data)
{
    m_mutex1.lock();
    m_mutex1.unlock();
}
