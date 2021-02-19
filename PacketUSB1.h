#ifndef PACKETUSB1_H
#define PACKETUSB1_H

#include "PacketUSB0.h"

union PacketUSB1 {

    PacketUSB1() {
        packet.header[0] = 0x76;
        packet.header[1] = 0x78;
    }

    struct Packet {
        uchar header[2];
        uchar index;
        uchar data[5];
        unsigned short crc16;
    } packet;
    uchar raw_data[10];
};

#endif // PACKETUSB1_H
