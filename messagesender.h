#ifndef MESSAGESENDER_H
#define MESSAGESENDER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include "packetswapper.h"

class MessageSender : public QObject
{
    Q_OBJECT
public:
    MessageSender(PacketSwapper* packetSwapper);
public slots:
    void slotUpdateUSB0() {
        //qDebug() << "This is from slotUpdateUSB0";
        p_packetSwapper->checkUSB0();
    }

    void slotUpdateUSB1() {
        //qDebug() << "This is from slotUpdateUSB1";
        p_packetSwapper->checkUSB1();
    }

    void slotSendData() {
        //qDebug() << "This is from slotSendData";
        p_packetSwapper->createPacketUDP();
    }

private:
    PacketSwapper* p_packetSwapper;
    QTimer* p_QTimerUSB0;
    QTimer* p_QTimerUSB1;
    QTimer* p_QTimerUDP;

};

#endif // MESSAGESENDER_H
