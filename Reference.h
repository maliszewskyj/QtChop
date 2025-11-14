#ifndef REFERENCE_H
#define REFERENCE_H

#include "Chop_Def.h"
#include <QObject>

class Reference
{
public:
    Reference();

    QString name;
    bool online;
    QString DataBlock;
    unsigned short Command;
    unsigned short RefSpeed;
    unsigned short GateWidth;
    unsigned short NomPhase[NoOfChoppers];
    unsigned short RadialSensor; // Enum 1..NoOfChoppers
    unsigned short LeadingChopper; // Enum 1..NoOfChoppers
    unsigned short CoincDelay;
};

#endif // REFERENCE_H
