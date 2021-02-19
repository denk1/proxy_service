#ifndef MESSAGERECIVER_H
#define MESSAGERECIVER_H

#include <QObject>
#include <QSerialPort>
#include <QString>
#include <vector>
#include "PacketUSB0.h"
#include "packetfinder.h"
#include "packet.h"
#include "packetswapper.h"

class MessageReciver : public QObject
{
    Q_OBJECT
public:
    MessageReciver(QString port_name, Packet& packet, PacketSwapper* packetSwapper);
    ~MessageReciver();
    unsigned short getCRC(uchar* data, size_t size);
    unsigned short calcCRC(uchar* data, size_t size);
    void setData(uchar* in_ptr_data);
private:
    QSerialPort m_serial;
    bool b_completed_frame;
    Packet& m_packet;
    PacketFinder m_packetFinder;
    std::vector<uchar> m_buff;
    bool is_end_part_header;
    uchar* m_header;
    PacketSwapper* ptr_packetSwapper;

private slots:
    void readingData();

};

#endif // MESSAGERECIVER_H
