#ifndef PACKET_H
#define PACKET_H
#include "PacketUSB0.h"

class Packet
{
public:
    Packet(uchar* header, uchar* data, size_t length);
    uchar* getData() {
        return m_data;
    }

    size_t getSize() {
        return m_length;
    }

    uchar* getHeader() {
        return m_header;
    }

private:
    uchar* m_data;
    size_t m_length;
    uchar *m_header;
};

#endif // PACKET_H
