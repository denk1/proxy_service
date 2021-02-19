#include <QDebug>
#include "producer_thread.h"



void ProducerThread::run()
{
    serial.setPortName("/home/suvairin/virtual-tty");
    if(!serial.setBaudRate(QSerialPort::Baud1200 , QSerialPort::Input))
        qDebug() << serial.errorString();
    if(!serial.setDataBits(QSerialPort::Data7))
        qDebug() << serial.errorString();
    if(!serial.setParity(QSerialPort::EvenParity))
        qDebug() << serial.errorString();
    if(!serial.setFlowControl(QSerialPort::HardwareControl))
        qDebug() << serial.errorString();
    if(!serial.setStopBits(QSerialPort::OneStop))
        qDebug() << serial.errorString();
    if(!serial.open(QIODevice::ReadOnly))
        qDebug() << serial.errorString();

    qDebug() << serial.bytesAvailable();
    qDebug() << "the end of initialization";
    qDebug() << "doWork()";
    while(serial.isOpen()) {
        qDebug() << "step";
        numRead  = serial.read(buffer, 50);

        // Do whatever with the array

        numReadTotal += numRead;
        if (numRead == 0 && !serial.waitForReadyRead())
            break;

    }
    serial.close();
    qDebug() << "the serial port is closed";
}

