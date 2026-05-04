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

void MainWindow::SetupSerial()
{
    // Should get this from configuration
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
    m_ChopperPort->write(m_OutgoingChopper);
}

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
        QStringList list  = m_IncomingChopper.split('$');
        if (list[0].length()==0) {
            m_IncomingChopper = "";
        } else {
            // Process the whole block
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
            break;
        case ID_NomPhHW:     // Nominal phase / high word
            break;
        case ID_Gate:        // Gate window
            Chop[num]->GateWidth = package_data;
            break;
        case ID_ActPhLW:     // Actual  phase / low  word
            break;
        case ID_ActPhHW:     // Actual  phase / high word
            break;
        case ID_DriveCurr:   // Drive current
            Chop[num]->DriveCurrent = package_data;
            break;
        case ID_AZVolt:      // Auto zero voltage of magnetic bearing
            break;
        }
    }
}

void MainWindow::onErrorChopper(QSerialPort::SerialPortError error)
{

}
