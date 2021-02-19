#include <QCoreApplication>
#include <QDebug>
#include "PacketUSB0.h"
#include "PacketUSB1.h"
#include "messagereciver.h"
#include "packetswapper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "it is starting the app";
    PacketUSB0 packetUSB0;
    PacketUSB1 packetUSB1;
    PacketSwapper packetSwapper;
    size_t s = sizeof(packetUSB0.raw_data);

    size_t s1 = sizeof(packetUSB1.raw_data);

    Packet packet0(packetUSB0.packet.header, packetUSB0.raw_data, s);

    Packet packet1(packetUSB1.packet.header, packetUSB1.raw_data, s1);
    //MessageReciver messageReciever0("/home/suvairin/ttySerial1", packet0);
    MessageReciver messageReciever1("/home/suvairin/ttySerial1", packet1, &packetSwapper);
    //MessageReciver messageReciever1()

    return a.exec();
}
