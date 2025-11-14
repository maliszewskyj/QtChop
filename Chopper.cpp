#include "Chopper.h"

Chopper::Chopper()
{

}

bool Chopper::SendPackage()
{
    m_SerialPort->write(m_Outgoing);
    if (!m_SerialPort->waitForBytesWritten(3000)) {
        //onPostError("Write timeout");
        return false;
    }
    return true;
}

bool Chopper::RecvPackage()
{
    QByteArray input;
    m_Incoming = "";
    do {
        if (m_SerialPort->waitForReadyRead(3000)) {
            input = m_SerialPort->readAll();
            m_Incoming.append(input);
        } else {
            // timeout or error
            return false;
        }
    } while (!m_Incoming.contains('$'));
    return true;
}

// Package structure
// #1100064B$
// ^^^^   ^ ^
// ||||   | |
// ||||   | +- Message terminator
// ||||   +--- Checksum (2 byte)
// |||+------- Data (4 byte)
// ||+-------- Data Identifier
// |+--------- Device number
// +---------- Package start
bool Chopper::GetBlock()
{
    m_Outgoing = "#" + QByteArray::number(chnum) + "0000000$";
    if (!SendPackage()) {
        // Could not send
        return false;
    }
    if (!RecvPackage()) {
        // Could not receive data
        return false;
    }
    return true;
}

bool Chopper::DecodeBlock()
{
    char devno;
    char devid;
    short data;
    int checksum;
    bool ok;
    if (m_Incoming.at(0) == '%') m_Incoming.remove(0,1);

    QList<QByteArray> parts = m_Incoming.split('%');
    for (const QByteArray part : parts) {
        // Should check length of package
        devno = part.at(0);
        devid = part.at(1);
        data = part.sliced(2,4).toShort(NULL,16);
        checksum = part.sliced(6,2).toInt(NULL,16);
    }

    return true;
}

