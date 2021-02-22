#ifndef PACKET_H
#define PACKET_H

#include <QMutex>
#include "PacketUSB0.h"

class Packet
{
public:
    Packet(uchar* header, uchar* data, size_t length);
    uchar* getData() {
        return m_data;
    }

    void setData(uchar* data);

    size_t getSize() {
        return m_length;
    }

    uchar* getHeader() {
        return m_header;
    }

    unsigned short getCRC();

    bool isCorrectCRC16() {
        return getCRC() == calcCRC();
    }

    unsigned short calcCRC();

    void lock() {
        m_mutex.lock();
    }

    void unlock() {
        m_mutex.unlock();
    }

    void setOldData() {
        m_is_new_packet = false;
    }

    int getSizePayload() {
        return m_sz_payload;
    }

    uchar* getPayloadData() {
        return m_data + 3;
    }

    bool isUpdated() {
        return m_is_new_packet;
    }

    void setAdmitedStatus() {
        m_is_new_packet = true;
    }

private:
    uchar* const m_data;
    const size_t m_length;
    uchar* const m_header;
    QMutex m_mutex;
    bool m_is_new_packet;
    const int m_sz_payload;
};

#endif // PACKET_H
