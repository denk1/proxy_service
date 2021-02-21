#include "packet.h"
#include "crc16modeprobe.h"

Packet::Packet(uchar* header, uchar* data, size_t length):
    m_data(data),
    m_length(length),
    m_header(header),
    m_is_new_packet(false),
    m_sz_payload(m_length - 5)
{

}

void Packet::setData(uchar *data)
{
    m_mutex.lock();
    std::copy(data, data + getSize(), getData());
    m_mutex.unlock();
    m_is_new_packet = true;
}

unsigned short Packet::getCRC()
{
    unsigned short *result;
    uchar temp[2];
    std::copy(m_data + m_length - 2, m_data + m_length, temp);
    result = reinterpret_cast<unsigned short*>(temp);
    return *result;
}

unsigned short Packet::calcCRC()
{
    return CRC16(m_data + 3, 5);
}
