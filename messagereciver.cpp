#include "messagereciver.h"
#include <QDebug>
#include <algorithm>
#include "crc16modeprobe.h"


MessageReciver::MessageReciver(QString port_name, Packet& packet, PacketSwapper* packetSwapper):m_serial(port_name),
    b_completed_frame(false),
    m_packet(packet),
    m_packetFinder(m_packet.getHeader(), packet.getSize()),
    is_end_part_header(false),
    ptr_packetSwapper(packetSwapper)
{

    m_serial.setPortName("/home/suvairin/ttySerial1");
    if(!m_serial.setBaudRate(QSerialPort::Baud1200))
        qDebug() << m_serial.errorString();
    if(!m_serial.setDataBits(QSerialPort::Data7))
        qDebug() << m_serial.errorString();
    if(!m_serial.setParity(QSerialPort::EvenParity))
        qDebug() << m_serial.errorString();
    if(!m_serial.setFlowControl(QSerialPort::HardwareControl))
        qDebug() << m_serial.errorString();
    if(!m_serial.setStopBits(QSerialPort::OneStop))
        qDebug() << m_serial.errorString();
    if(!m_serial.open(QIODevice::ReadOnly))
        qDebug() << m_serial.errorString();

    QObject::connect(&m_serial, &QSerialPort::readyRead, this, &MessageReciver::readingData);

    QObject::connect(&m_serial,
                     static_cast<void(QSerialPort::*)(QSerialPort::SerialPortError)>
                     (&QSerialPort::error),
                     [&](QSerialPort::SerialPortError error)
    {
        //this is called when a serial communication error occurs
        qDebug() << "An error occured: " << error;
        exit(-1);
    });

}

MessageReciver::~MessageReciver()
{
    m_serial.close();
}

unsigned short MessageReciver::getCRC(uchar* data, size_t size)
{
    unsigned short *result;
    uchar temp[2];
    std::copy(data + size - 2, data + size, temp);
    result = reinterpret_cast<unsigned short*>(temp);
    return *result;
}

unsigned short MessageReciver::calcCRC(uchar *data, size_t size)
{
    return CRC16(data + 3, 5);
}

void MessageReciver::setData(uchar* in_ptr_data) {
    bool result = false;
    std::copy(in_ptr_data, in_ptr_data + m_packet.getSize(), m_packet.getData());
    qDebug() << "the packet has been written down";
    if(getCRC(m_packet.getData(), m_packet.getSize()) == calcCRC(m_packet.getData(), m_packet.getSize()))
        result = true;
    qDebug() << result;
 }

void MessageReciver::readingData()
{
    int length = m_serial.bytesAvailable();
    qDebug() << "New data available: " << m_serial.bytesAvailable();
    qDebug() << "Previous data available: " << m_buff.size();
    QByteArray data = m_serial.readAll();
    qDebug() << data;
    std::vector<uchar> v_buff;
    if(m_buff.size() > 0) {
        if(m_buff.size() + length >= m_packet.getSize()) {
            int common_size = m_buff.size() + length;
            int trim = common_size % m_packet.getSize();

            for(int i = 0; i < length - trim; i++) {
                m_buff.push_back(data[i]);
            }
            v_buff.resize(m_buff.size());
            std::copy(m_buff.begin(), m_buff.end(), v_buff.begin());

            m_buff.clear();

            for(int i = length - trim; i < length; i++) {
                m_buff.push_back(data[i]);
            }

        } else {

            for(int i = 0; i < length; i++) {
                m_buff.push_back(data[i]);
            }
        }
    }
    else if (length == 1) {
        m_buff.push_back(data[0]);
        if(m_buff.size() == m_packet.getSize()) {
            auto it = v_buff.begin();
            v_buff.insert(it, m_buff.begin(), m_buff.end());
        }
    }
    else {
        if(length >= m_packet.getSize()) {
            int trim = length % m_packet.getSize();
            for(int pos = 0; pos < length - trim; pos++) {
                v_buff.push_back(data[pos]);
            }

            for (int i = length - trim; i < length; i++) {
                m_buff.push_back(data[i]);
            }
        } else {
            for(int i = 0; i < length; i++) {
                m_buff.push_back(data[i]);
            }
        }
    }

    m_packetFinder.setPacket(&v_buff[0], v_buff.size());

    if(is_end_part_header && m_packetFinder.is_head_of_part_header()) {
        auto it = v_buff.begin();
        v_buff.insert(it, m_header[0]);
    }

    while(m_packetFinder()){

        qDebug() << "it's OK!";
        size_t pos = m_packetFinder.getCurPos();

        if(pos + m_packet.getSize() <= v_buff.size()){
            setData(&v_buff[pos]);
            m_packetFinder.setPosition(pos + m_packet.getSize());

        }
        else {
            int plenty_count = v_buff.size() - pos;
            if(plenty_count + m_buff.size() >=  m_packet.getSize()) {
                int diff = plenty_count + m_buff.size() -  m_packet.getSize();
                auto it_v_buff = v_buff.end();
                plenty_count = plenty_count > (int)m_buff.size() ? m_buff.size() : plenty_count;
                v_buff.insert(it_v_buff, &m_buff[0], &m_buff[0] + plenty_count - diff);
                m_buff.erase(m_buff.begin(), m_buff.begin() + plenty_count - diff);
            }
            else {
                auto it_m_buff = m_buff.begin();
                m_buff.insert(it_m_buff, v_buff.begin() + pos, v_buff.end());
                break;
            }
        }
    }
}
