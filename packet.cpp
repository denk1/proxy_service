#include "packet.h"

Packet::Packet(uchar* header, uchar* data, size_t length):
    m_header(header),
    m_data(data),
    m_length(length)
{

}
