#ifndef CHOPPER_H
#define CHOPPER_H
#include "Chop_Def.h"
#include <QObject>
#include <QByteArray>
#include <QtSerialPort/QSerialPort>

class Chopper
{
public:
    Chopper();

    bool online;
    bool coinc_active;
    int chnum;
    QString name;
    QString DataBlock;     // Block of data received from uC
    unsigned short status;
    unsigned short oldstatus;
    unsigned short Command;
    unsigned short RefSpeed;
    unsigned short Ratio;  // Ratio: hi byte = numerator, lo byte = denominator
    float NomSpeed;        // Nominal speed = refspeed * ratio
    unsigned short ActSpeed; // Actual chopper speed in rpm
    unsigned short OldSpeed; // Previous speed in rpm
    unsigned char NomPhaseLW;
    unsigned char NomPhaseHW;
    unsigned char ActPhaseLW;
    unsigned char ActPhaseHW;
    // OutageCounter
    unsigned short GateWidth; // Gate Window
    unsigned short DriveCurrent; // Encoded drive current
    unsigned short AZVoltage;    // Encoded auto-zero voltage
    unsigned short OldAZVoltage;
    // Statistics
    // ActPhaseFile

    QString RatioString;
    QString ActSpeedString;
    QString NomSpeedString;
    QString NomPhaseString;
    QString ActPhaseString;
    QString MeanDevString;
    QString GateWidthString;
    QString OutageString;
    QString LastCommandString;


    QSerialPort * m_SerialPort; // Serialport
    QByteArray m_Outgoing;
    QByteArray m_Incoming;

    bool SendPackage();
    bool RecvPackage();
    bool GetBlock();
    bool DecodeBlock();

    void tics2us();
    void tics2degree();
    void ratio2string();
    void command2string();

};

#endif // CHOPPER_H
