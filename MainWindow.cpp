#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int i;
    ui->setupUi(this);

    for (i=0;i<NoOfChoppers;i++) {
        Chop[i] = new Chopper();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetupGUI()
{
    // The display widget is big and awkward.
    // No clever way to populate the widgets so here we go.
    // Ratio
    m_Ratio[0] = ui->Ratio_1;
    m_Ratio[1] = ui->Ratio_2;
    m_Ratio[2] = ui->Ratio_3;
    m_Ratio[3] = ui->Ratio_4;
    m_Ratio[4] = ui->Ratio_5;
    m_Ratio[5] = ui->Ratio_6;
    m_Ratio[6] = ui->Ratio_7;

    m_NomSpeed[0] = ui->NomSpeed_1;
    m_NomSpeed[1] = ui->NomSpeed_2;
    m_NomSpeed[2] = ui->NomSpeed_3;
    m_NomSpeed[3] = ui->NomSpeed_4;
    m_NomSpeed[4] = ui->NomSpeed_5;
    m_NomSpeed[5] = ui->NomSpeed_6;
    m_NomSpeed[6] = ui->NomSpeed_7;

    m_ActSpeed[0] = ui->ActSpeed_1;
    m_ActSpeed[1] = ui->ActSpeed_2;
    m_ActSpeed[2] = ui->ActSpeed_3;
    m_ActSpeed[3] = ui->ActSpeed_4;
    m_ActSpeed[4] = ui->ActSpeed_5;
    m_ActSpeed[5] = ui->ActSpeed_6;
    m_ActSpeed[6] = ui->ActSpeed_7;

    m_NomPhase[0] = ui->NomPhase_1;
    m_NomPhase[1] = ui->NomPhase_2;
    m_NomPhase[2] = ui->NomPhase_3;
    m_NomPhase[3] = ui->NomPhase_4;
    m_NomPhase[4] = ui->NomPhase_5;
    m_NomPhase[5] = ui->NomPhase_6;
    m_NomPhase[6] = ui->NomPhase_7;

    m_ActPhase[0] = ui->ActPhase_1;
    m_ActPhase[1] = ui->ActPhase_2;
    m_ActPhase[2] = ui->ActPhase_3;
    m_ActPhase[3] = ui->ActPhase_4;
    m_ActPhase[4] = ui->ActPhase_5;
    m_ActPhase[5] = ui->ActPhase_6;
    m_ActPhase[6] = ui->ActPhase_7;

    m_MeanDev[0] = ui->MeanDev_1;
    m_MeanDev[1] = ui->MeanDev_2;
    m_MeanDev[2] = ui->MeanDev_3;
    m_MeanDev[3] = ui->MeanDev_4;
    m_MeanDev[4] = ui->MeanDev_5;
    m_MeanDev[5] = ui->MeanDev_6;
    m_MeanDev[6] = ui->MeanDev_7;

    m_GateWidth[0] = ui->GateWidth_1;
    m_GateWidth[1] = ui->GateWidth_2;
    m_GateWidth[2] = ui->GateWidth_3;
    m_GateWidth[3] = ui->GateWidth_4;
    m_GateWidth[4] = ui->GateWidth_5;
    m_GateWidth[5] = ui->GateWidth_6;
    m_GateWidth[6] = ui->GateWidth_7;

    m_Outage[0] = ui->Outage_1;
    m_Outage[1] = ui->Outage_2;
    m_Outage[2] = ui->Outage_3;
    m_Outage[3] = ui->Outage_4;
    m_Outage[4] = ui->Outage_5;
    m_Outage[5] = ui->Outage_6;
    m_Outage[6] = ui->Outage_7;

    m_DCSupply[0] = ui->DCSupply_1;
    m_DCSupply[1] = ui->DCSupply_2;
    m_DCSupply[2] = ui->DCSupply_3;
    m_DCSupply[3] = ui->DCSupply_4;
    m_DCSupply[4] = ui->DCSupply_5;
    m_DCSupply[5] = ui->DCSupply_6;
    m_DCSupply[6] = ui->DCSupply_7;

    m_LastCommand[0] = ui->LastCommand_1;
    m_LastCommand[1] = ui->LastCommand_2;
    m_LastCommand[2] = ui->LastCommand_3;
    m_LastCommand[3] = ui->LastCommand_4;
    m_LastCommand[4] = ui->LastCommand_5;
    m_LastCommand[5] = ui->LastCommand_6;
    m_LastCommand[6] = ui->LastCommand_7;

    m_DriveMode[0] = ui->DriveMode_1;
    m_DriveMode[1] = ui->DriveMode_2;
    m_DriveMode[2] = ui->DriveMode_3;
    m_DriveMode[3] = ui->DriveMode_4;
    m_DriveMode[4] = ui->DriveMode_5;
    m_DriveMode[5] = ui->DriveMode_6;
    m_DriveMode[6] = ui->DriveMode_7;

    m_DriveCurrent[0] = ui->DriveCurrent_1;
    m_DriveCurrent[1] = ui->DriveCurrent_2;
    m_DriveCurrent[2] = ui->DriveCurrent_3;
    m_DriveCurrent[3] = ui->DriveCurrent_4;
    m_DriveCurrent[4] = ui->DriveCurrent_5;
    m_DriveCurrent[5] = ui->DriveCurrent_6;
    m_DriveCurrent[6] = ui->DriveCurrent_7;
}

void MainWindow::SetupSerial()
{
    // Should get this from configuNomPhasen
    m_ChopperPortName = "/dev/ttyChopper";
    m_BaudRate = QSerialPort::Baud57600;
    m_DataBits = QSerialPort::Data8;
    m_Parity   = QSerialPort::NoParity;
    m_StopBits = QSerialPort::OneStop;
    m_FlowControl = QSerialPort::NoFlowControl;

    m_IncomingChopper = "";
    m_IncomingHost = "";

    qDebug() << "Comms opening serial port " + m_ChopperPortName;
    m_ChopperPort = new QSerialPort();
    m_ChopperPort->setPortName(m_ChopperPortName);
    m_ChopperPort->setBaudRate(m_BaudRate);
    m_ChopperPort->setDataBits(m_DataBits);
    m_ChopperPort->setParity(m_Parity);
    m_ChopperPort->setStopBits(m_StopBits);
    m_ChopperPort->setFlowControl(m_FlowControl);

    if (!m_ChopperPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Cannot open serial port: " + m_ChopperPortName + "\n";
    } else {
        qDebug() << "Opened serial port " + m_ChopperPortName + "\n";
    }
    connect(m_ChopperPort,SIGNAL(readyRead()), this, SLOT(onReadChopper()));
}

// From cute "GetBlock"
void MainWindow::RequestBlock(int index)
{
    if (index < 0 || index > NoOfChoppers) return; //
    m_OutgoingChopper = "#" + QByteArray::number(index) + "0000000$";
    qDebug() << "> " << m_OutgoingChopper;
    m_ChopperPort->write(m_OutgoingChopper);
}

// Refresh data items in the grid
void MainWindow::Refresh()
{

}

// From cute "GetDataString"
void MainWindow::onReadChopper()
{
    QByteArray input;

    input = m_ChopperPort->readAll();
    m_IncomingChopper.append(input);
    if (m_IncomingChopper.contains('$')) {
        qDebug() << "> " << m_IncomingChopper;
        QStringList list  = m_IncomingChopper.split('$');
        if (list[0].length()==0) {
            m_IncomingChopper = "";
        } else {
            // Process the whole block
            DecodeBlock();
        }
    }
}

/*
 *  Package structure:
 *
 *  #Diddddxx   D:    Device number
 *              i:    data identifier
 *              dddd: package data (hex)
 *              xx:   checksum
 */
void MainWindow::DecodeBlock()
{

    unsigned int chksum_rd, chksum_calc;
    // Assume we're just parsing what's in m_IncomingChopper
    QStringList list = m_IncomingChopper.split('#');

    // Iterate over the elements of the list
    for (const QString &str : list) {
        qDebug() << str;

        chksum_rd = str.mid(6,2).toInt(NULL,16);
        chksum_calc = DoCheckSum("#"+str.mid(0,6));
        if (chksum_rd == chksum_calc) {
            // Could/should probably validate the checksum
            AnalyzePackage(str);
        }
    }
}

unsigned int MainWindow::DoCheckSum(const QString pkg)
{
    int i, k, sum;
    std::string str;
    char ch;

    sum = 0;
    str = pkg.toStdString();
    for(i=0;i<pkg.length();i++) {
        ch = str[i];
        k = (int) ch;
        if ((k>=35) && (k<=80)) sum+=k;
    }
    return (sum % 255);
}

void MainWindow::AnalyzePackage(const QString pkg)
{
    unsigned int num;
    char data_id;
    unsigned short package_data;
    num = pkg.mid(0,1).toUInt();
    data_id = pkg.at(1).toLatin1();
    package_data = pkg.mid(2,4).toUShort(NULL,16);
    if (num > NoOfChoppers) { // system level
        return; // Out of bounds
    } else if (num == 0) {
        switch(data_id) {
        case IDREF_Command:
            break;
        case IDREF_CGate:
            break;
        case IDREF_RefSpeed:
            break;
        case IDREF_PhaseLW1:
            break;
        case IDREF_PhaseHW1:
            break;
        case IDREF_PhaseLW2:
            break;
        case IDREF_PhaseHW2:
            break;
        case IDREF_PhaseLW3:
            break;
        case IDREF_PhaseHW3:
            break;
        case IDREF_PhaseLW4:
            break;
        case IDREF_PhaseHW4:
            break;
        case IDREF_PhaseLW5:
            break;
        case IDREF_PhaseHW5:
            break;
        case IDREF_PhaseLW6:
            break;
        case IDREF_PhaseHW6:
            break;
        case IDREF_PhaseLW7:
            break;
        case IDREF_PhaseHW7:
            break;
        }
        return; //
    } else {
        switch(data_id) {
        case ID_Command:     // Command word
            Chop[num]->Command = package_data;
            break;
        case ID_Status:      // Status word
            Chop[num]->oldstatus = Chop[num]->status;
            Chop[num]->status = package_data;
            break;
        case ID_RefSpeed:    // Nominal speed
            Chop[num]->RefSpeed = package_data;
            break;
        case ID_ActSpeed:    // Actual speed
            Chop[num]->OldSpeed = Chop[num]->ActSpeed;
            Chop[num]->ActSpeed = package_data;
            break;
        case ID_Ratio:       // Ratio to nominal speed
            Chop[num]->Ratio = package_data;
            break;
        case ID_NomPhLW:     // Nominal phase / low  word
            Chop[num]->NomPhaseLW = package_data;
            break;
        case ID_NomPhHW:     // Nominal phase / high word
            Chop[num]->NomPhaseHW = package_data;
            break;
        case ID_Gate:        // Gate window
            Chop[num]->GateWidth = package_data;
            break;
        case ID_ActPhLW:     // Actual  phase / low  word
            Chop[num]->ActPhaseLW = package_data;
            break;
        case ID_ActPhHW:     // Actual  phase / high word
            Chop[num]->ActPhaseHW = package_data;
            break;
        case ID_DriveCurr:   // Drive current
            Chop[num]->DriveCurrent = package_data;
            break;
        case ID_AZVolt:      // Auto zero voltage of magnetic bearing
            Chop[num]->AZVoltage = package_data;
            break;
        }
    }
}

void MainWindow::onErrorChopper(QSerialPort::SerialPortError error)
{

}
