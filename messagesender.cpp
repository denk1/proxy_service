#include "messagesender.h"

MessageSender::MessageSender(PacketSwapper* packetSwapper):
    p_packetSwapper(packetSwapper),
    p_QTimerUSB0(new QTimer(this)),
    p_QTimerUSB1(new QTimer(this)),
    p_QTimerUDP(new QTimer(this))
{
    connect(p_QTimerUSB0, SIGNAL(timeout()), SLOT(slotUpdateUSB0()));
    connect(p_QTimerUSB1, SIGNAL(timeout()), SLOT(slotUpdateUSB1()));
    connect(p_QTimerUDP,  SIGNAL(timeout()), SLOT(slotSendData()));
    p_QTimerUSB0->start(600);
    p_QTimerUSB1->start(500);
    p_QTimerUDP->start(1000);
}
