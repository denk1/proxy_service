#include <QCoreApplication>
#include <QDebug>
#include "PacketUSB0.h"
#include "PacketUSB1.h"
#include "messagereciver.h"
#include "messagesender.h"
#include "packetswapper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PacketUSB0 packetUSB0;
    PacketUSB1 packetUSB1;

    qDebug() << "it is starting the app";
    size_t s = sizeof(packetUSB0.raw_data);

    size_t s1 = sizeof(packetUSB1.raw_data);

    Packet packet0(packetUSB0.packet.header, packetUSB0.raw_data, s);

    Packet packet1(packetUSB1.packet.header, packetUSB1.raw_data, s1);
    PacketSwapper packetSwapper(&packet0, &packet1);
    // Please uncomment for working with 2 ports
    //MessageReciver messageReciever("/home/suvairin/ttySerial2", packet1, &packetSwapper);
    MessageReciver messageReciever1("/home/suvairin/ttySerial1", packet1, &packetSwapper);
    MessageSender messageSender(&packetSwapper);
    return a.exec();
}
