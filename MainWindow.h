#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QRegularExpression>
#include <QDebug>
#include "Chop_Def.h"
#include "Chopper.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString m_ChopperPortName;
    QString m_HostPortName;
    QSerialPort * m_ChopperPort;
    QSerialPort * m_HostPort;

    QSerialPort::BaudRate m_BaudRate;
    QSerialPort::DataBits m_DataBits;
    QSerialPort::Parity   m_Parity;
    QSerialPort::StopBits m_StopBits;
    QSerialPort::FlowControl m_FlowControl;

    QString m_IncomingChopper;
    QByteArray m_OutgoingChopper;
    QString m_IncomingHost;
    QByteArray m_OutgoingHost;

    Chopper * Chop[NoOfChoppers];

    void SetupSerial();

    void RequestBlock(int index);
    void DecodeBlock();
    unsigned int DoCheckSum(const QString pkg);
    void AnalyzePackage(const QString pkg);
public slots:
    void Refresh();
    void onReadChopper();
    void onErrorChopper(QSerialPort::SerialPortError error);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
