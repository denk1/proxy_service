#ifndef PACKETUDP_H
#define PACKETUDP_H
#include "PacketUSB0.h"

union PacketUDP {
    PacketUDP() {
        packet.header[0] = 0x55;
        packet.header[1] = 0x77;
        packet.index = 0;
    }
    struct Packet {
        uchar header[2];
        uchar index;
        uchar data[14];
    } packet;
    uchar raw_data[17];
};

#endif // PACKETUDP_H
