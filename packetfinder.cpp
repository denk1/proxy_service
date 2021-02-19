#include "packetfinder.h"
#include <cassert>

PacketFinder::PacketFinder(uchar header[2], size_t length):
     m_header(header),
     m_cur_pos(0),
     is_there_header(false),
     m_length(length)
{

}

bool PacketFinder::operator()()
{
    assert ((size_of_data % m_length ) == 0);
    for(size_t i = m_cur_pos; i < size_of_data; i++) {
        if (m_header[0] == m_packet[i] && m_header[1] == m_packet[i + 1]) {
            m_cur_pos = i;
            is_there_header = true;
            return true;
        }
    }
    return false;
}

void PacketFinder::setPacket(uchar *packet, size_t in_size_of_data)
{
    m_cur_pos = 0;
    m_packet = packet;
    size_of_data = in_size_of_data;
}

bool PacketFinder::is_end_of_part_header()
{
    return m_header[1] == m_packet[0];
}

bool PacketFinder::is_head_of_part_header()
{
    return m_header[0] == m_packet[m_length - 1];
}
