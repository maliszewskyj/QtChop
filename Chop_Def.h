#ifndef CHOP_DEF_H
#define CHOP_DEF_H

#define INSTRUMENT   "DCS"
#define NoOfChoppers 7
#define ReferenceNo  0
#define F_Quartz     48E6
#define F_DoubleQuartz F_Quartz*2
#define F_HalfQuartz   F_Quartz/2

#define Baud_Chopper 56200
#define Baud_Host    56200

#define SerInSize     5000 // Size of serial input buffer
#define SerOutSize    5000 // Size of serial output buffer

#define MBSpeed       200.0
#define SpeedMin     1200.0
#define SpeedMax    20000.0
#define SpeedLimit  20200.0

#define NumeratorMin    1
#define NumeratorMax   27
#define DenominatorMin  1
#define DenominatorMax 28

#define PhaseMin         0.01
#define PhaseMax       359.99

#define CoincDelayMin     0.0
#define CoincDelayMax 50000.0

#define GateMin          0.01
#define GateMax          1.00
#define AZLimit           2.5

// Commands used to control the drive and the magnetic bearings
#define CMD_NoComand  0
#define CMD_StopClose 1
#define CMD_DriveOff  2 // Switch drive generator off
#define CMD_RunModeCW 3 // Switch drive generator to run mode; clockwise
#define CMD_Stop      4 // Stops and aligns the disk
#define CMD_MBoff     5 // Switch magnetic bearing off
#define CMD_MBon      6 // Switch magnetic bearing on

// Constants representing the status of the chopper

#define STAT_OK       0x0001 // Set when the uC program is running
#define STAT_NomSpeed 0x0002 // Set when the nominal speed is reached
#define STAT_Gate     0x0004 // Set when the phase is within the gate
#define STAT_MBon     0x0008 // Set when the magnetic bearing is ON
#define STAT_DCon     0x0010 // Set when the DC supply voltage is ON
#define STAT_DriveON  0x0020 // Set when the drive is ON
#define STAT_DCMode   0x0040 // Set when drive current is DC for stat pos
#define STAT_StatPos  0x0100 // Set when stationary positioning is ON
#define STAT_SpeedOF  0x0400 // Set when actual speed exceeds limit
#define STAT_BearingF 0x0800 // Set when bearing failed at speed
#define STAT_AZOF     0x1000 // Set when AZ voltage exceeds limits

// Data identifiers for data transmission PC to SLAVE choppers
#define ID_Command     1  // Command word
#define ID_Status      2  // Status word
#define ID_RefSpeed    3  // Nominal speed
#define ID_ActSpeed    4  // Actual speed
#define ID_Ratio       5  // Ratio to nominal speed
#define ID_NomPhLW     6  // Nominal phase / low  word
#define ID_NomPhHW     7  // Nominal phase / high word
#define ID_Gate        8  // Gate window
#define ID_ActPhLW     9  // Actual  phase / low  word
#define ID_ActPhHW     A  // Actual  phase / high word
#define ID_DriveCurr   B  // Drive current
#define ID_AZVolt      C  // Auto zero voltage of magnetic bearing

// Data identifiers for data transmission PC to client computer
#define IDREF_Command  1 // Command Word
#define IDREF_CGate    2 // Gate of coincidence choppers
#define IDREF_RefSpeed 3 // Reference speed
#define IDREF_PhaseLW1 4 // Delay of ref mark; lo/hi word; chopper number
#define IDREF_PhaseHW1 5 //
#define IDREF_PhaseLW2 6
#define IDREF_PhaseHW2 7
#define IDREF_PhaseLW3 8
#define IDREF_PhaseHW3 9
#define IDREF_PhaseLW4 A
#define IDREF_PhaseHW4 B
#define IDREF_PhaseLW5 C
#define IDREF_PhaseHW5 D
#define IDREF_PhaseLW6 E
#define IDREF_PhaseHW6 F
#define IDREF_PhaseLW7 G
#define IDREF_PhaseHW7 H
#define IDREF_RadSense I // Number of "active" radial sensor
#define IDREF_CDelayLW J // Delay of coincidence signal
#define IDREF_CDelayHW K

// Timers
#define PROG_LogPeriod    900 // Regular log file entries (seconds)
#define PROG_InputPeriod  120 // Max time for inputs (seconds)
#define PROG_Statperiod   120 // Statistical evaluation of phases (seconds)
#define PROG_UpdatePeriod 200 // Period between data updates (n+1)*55 ms

#endif // CHOP_DEF_H
