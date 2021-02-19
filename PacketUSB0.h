#ifndef PACKETUSB0_H
#define PACKETUSB0_H

#include <cstddef>

typedef unsigned char uchar;

union PacketUSB0 {
    PacketUSB0() {
        packet.header[0] = 0x76;
        packet.header[1] = 0x77;
    }
    struct Packet {
        uchar header[2];
        uchar index;
        uchar data[9];
        unsigned short crc16;
    } packet;
    uchar raw_data[14];
};

#endif // PACKETUSB0_H
