#ifndef PACKETFINDER_H
#define PACKETFINDER_H
#include "PacketUSB0.h"

class PacketFinder
{
public:
    PacketFinder(uchar header[2], size_t length);
    bool operator()();
    size_t getCurPos() const {
        return m_cur_pos;
    }

    void setPosition(size_t pos) {
        m_cur_pos = pos;
    }

    void setPacket(uchar* packet, size_t in_size_of_data);
    bool is_end_of_part_header();
    bool is_head_of_part_header();
    bool isThereHeader() {
        return is_there_header;
    }

private:
    uchar* m_packet;
    uchar* m_header;
    size_t m_length;
    size_t m_cur_pos;
    size_t size_of_data;
    bool is_there_header;
};

#endif // PACKETFINDER_H
