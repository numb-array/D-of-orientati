#ifndef SERIAL_H
#define SERIAL_H
#include <algorithm>
#include <QMainWindow>
#include <QtWidgets/QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include <QVector>
#include <QMessageBox>
#include <QDockWidget>
#include <QStatusBar>
#include <QMenuBar>
#include <QToolBar>
//using namespace std::sort
class Serial : public QMainWindow
{
    Q_OBJECT


public:
    Serial(QWidget *parent = 0);
    ~Serial();
    void RefreshPort(void);
   void timerEvent(QTimerEvent* e);
//    void ReceiveAeraInit(QWidget* parent);
//    void SendAeraInit(QWidget* parent);
//    void SetupInit(QWidget* parent);
    void BeginUSART(QWidget* parent);
    void USART(QString port, QString baud, QString data, QString stop, QString ch);
    QSerialPort* serialPort;
//    QSerialPort* serialPort;
    QVector<QString>ports;
  //  void BeginUSART(QWidget* parent);
private:
    int id;
    QComboBox* portNumber;
    QPushButton* sendButton;
    QComboBox* baudRate;
    QComboBox* dataSize;
    QComboBox* stopSize;
    QComboBox* sendMode;
    QComboBox* check;
    QComboBox* receiveMode;
    QPlainTextEdit* receiveAera;

};

#endif // SERIAL_H
