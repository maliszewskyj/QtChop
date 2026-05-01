#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


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
void MainWindow::onErrorChopper(QSerialPort::SerialPortError error)
{

}
