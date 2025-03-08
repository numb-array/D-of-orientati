#include "serial.h"

Serial::Serial(QWidget *parent)
    : QMainWindow(parent)
{
    /**************************菜单*******************/

    QMenuBar* bar= menuBar();
    //将菜单栏放入窗口
    setMenuBar(bar);
    QMenu* fileMenu= bar->addMenu("帮助");
    QAction* openaction =fileMenu->addAction("联系");
    connect(openaction,&QAction::triggered,[=](){
//        QDialog* dlg2=new QDialog(this);
//        dlg2->show();
//        //防止内存泄漏55号
//        dlg2->resize(200,200);
//        dlg2->setAttribute(Qt::WA_DeleteOnClose);
//       QLabel* relation=new QLabel("邮箱3499649346@qq.com",this);
        QMessageBox::critical(this,"联系方式","3499649346@qq.com");
    });

    setWindowTitle("东华大学材料学院取向测量仪");
    setFixedSize(1200,750);

    /*******************************选项设置*************************/

    portNumber = new QComboBox(this);
    baudRate = new QComboBox(this);
    dataSize = new QComboBox(this);
    stopSize = new QComboBox(this);
    check = new QComboBox(this);
    receiveMode = new QComboBox(this);
    sendMode = new QComboBox(this);
    baudRate->addItem("4800");
    baudRate->addItem("9600");
    baudRate->addItem("19200");
    dataSize->addItem("8");
    stopSize->addItem("1");
    stopSize->addItem("1.5");
    stopSize->addItem("2");
    sendMode->addItem("hex");
    receiveMode->addItem("HEX");
    receiveMode->addItem("文本");
    sendMode->addItem("文本");

    QLabel* portLabel = new QLabel("串口号", this);
    QLabel* baudLabel = new QLabel("波特率",this);
    QLabel* dataLabel = new QLabel("数据位",this);
    QLabel* stopLabel = new QLabel("停止位",this);
    QLabel* sendModeLabel = new QLabel("发送格式",this);
    check->addItem("无");
    check->addItem("奇校验");
    check->addItem("偶校验");
    QLabel* checkLabel = new QLabel("校验位",this);
    QLabel* receiveModeLabel = new QLabel("接收格式",this);
    receiveMode->setFixedSize(200,50);
    check->setFixedSize(200,50);
    check->move(550,20);
    checkLabel->move(780,20);

    /*********************接收******************/

    receiveMode->move(550,100);
    receiveModeLabel->move(780,100);
    receiveAera = new QPlainTextEdit(this);
    receiveAera->setFixedSize(200,50);
    receiveAera->move(550,180);
    QLabel* receivelable = new QLabel("接收区",this);
    receivelable->move(780,180);
    receiveAera->setReadOnly(true);


   QVector<QComboBox*> setups;
   setups.push_back(portNumber);
   setups.push_back(baudRate);
   setups.push_back(dataSize);
   setups.push_back(stopSize);
   setups.push_back(sendMode);

   QVector<QLabel*> labels;
   labels.push_back(portLabel);
   labels.push_back(baudLabel);
   labels.push_back(dataLabel);
   labels.push_back(stopLabel);
   labels.push_back(sendModeLabel);


        for (int i = 0; i < setups.size(); ++i) {
            setups[i]->setFixedSize(200, 50);
            setups[i]->move(850, 20 + i * 80);
            labels[i]->move(1080,25+i*80);
        }


        ///////////////////发送//////////
        QPlainTextEdit* sendAera = new QPlainTextEdit(this);
        sendAera->setFixedSize(200,50);
        sendAera->move(850,420);
        QLabel* HZ = new QLabel("单位Hz",this);
        HZ->move(1080,460);
        QLabel* HZ3 = new QLabel("20<或<20K",this);
        HZ3->move(1080,440);
        QLabel* HZ1= new QLabel("输入频率",this);
        HZ1->move(1080,420);

        /********占空比***********/
        QPlainTextEdit* rateAera = new QPlainTextEdit(this);
        rateAera->setFixedSize(200,50);
        rateAera->move(850,580);
        QLabel* ra1 = new QLabel("0<或<1",this);
        ra1->move(1080,600);
        QLabel* ra2= new QLabel("占空比",this);
        ra2->move(1080,580);
        /*********************************/

        QPushButton* clearSend=new  QPushButton("清空",this);
        clearSend->setFixedSize(100, 50);
        clearSend->move(850, 500);
        connect(clearSend,&QPushButton::clicked,[=](){
           sendAera->clear();
        });
        QPushButton* sendButton=new QPushButton("发送",this);
        sendButton->setFixedSize(100, 50);
        sendButton->move(975, 500);
       // sendButton->setDisabled(true);
        connect(sendButton,&QPushButton::clicked,[&](){
            QString data = sendAera->toPlainText();
                           if (sendMode->currentText() == "HEX") {
                               QByteArray arr;
                               for (int i = 0; i<data.size(); i++){
                                   if (data[i] == ' ') continue;
                                   int num = data.mid(i, 2).toUInt(nullptr, 16);       //将数据转为16进制
                                   i++;
                                   arr.append(num);
                               }
                               qDebug()<<"111";
                               serialPort->write(arr);
                           }else {
                               serialPort->write(data.toLocal8Bit().data());           //转为utf-8格式字符串写入
                               //serialPort->clear();
                               qDebug()<<"asc";
                           }
        });

                           /****************************占空比清除和发送***************/
                           QPushButton* clearSend1=new  QPushButton("清空",this);
                           clearSend1->setFixedSize(100, 50);
                           clearSend1->move(850, 660);
                           connect(clearSend1,&QPushButton::clicked,[=](){
                              rateAera->clear();// ->clear();
                           });
                           QPushButton* sendButton1=new QPushButton("发送",this);
                           sendButton1->setFixedSize(100, 50);
                           sendButton1->move(975, 660);
                           //sendButton1->setDisabled(true);
                           connect(sendButton1,&QPushButton::clicked,[=](){
                               QString data1 = rateAera->toPlainText();
                                              if (sendMode->currentText() == "HEX") {
                                                  QByteArray arr;
                                                  for (int i = 0; i<data1.size(); i++){
                                                      if (data1[i] == ' ') continue;
                                                      int num = data1.mid(i, 2).toUInt(nullptr, 16);       //将数据转为16进制
                                                      i++;
                                                      arr.append(num);
                                                  }
                                                  serialPort->write(arr);
                                              }else {
                                                  serialPort->write(data1.toLocal8Bit().data());           //转为utf-8格式字符串写入
                                                  //serialPort->clear();
                                                  qDebug()<<"asc";
                                              }

                                              });
                           /************开启定时***************/

                           id=startTimer(1000);
                           BeginUSART(this);

}

/****************串口********************/

void Serial::USART(QString port, QString baud, QString data,QString stop,QString check) {
    QSerialPort::BaudRate Baud;     //波特率
    QSerialPort::DataBits Data;     //数据位
    QSerialPort::StopBits Stop;     //停止位
    QSerialPort::Parity Check;      //校验位

    if (baud == "4800")  Baud = QSerialPort::Baud4800;
    else if (baud == "9600") Baud = QSerialPort::Baud9600;
    else if (baud == "19200")  Baud = QSerialPort::Baud19200;

    if (data == "8") Data = QSerialPort::Data8;

    if (stop == "1") Stop = QSerialPort::OneStop;
    else if (stop == "1.5")Stop = QSerialPort::OneAndHalfStop;
    else if (stop == "2") Stop = QSerialPort::TwoStop;

    if (check == "无") Check = QSerialPort::NoParity;
    else if (check == "奇校验") Check = QSerialPort::OddParity;
    else if (check =="偶校验") Check = QSerialPort::EvenParity;

    serialPort= new QSerialPort(this);
    //为串口设置配置
    serialPort->setBaudRate(Baud);
    serialPort->setPortName(port);
    serialPort->setDataBits(Data);
    serialPort->setParity(Check);
    serialPort->setStopBits(Stop);
    //打开串口
    if (serialPort->open(QSerialPort::ReadWrite)) {
        //配置信号槽,一旦收到数据则开始读取
        QObject::connect(serialPort, &QSerialPort::readyRead, [&]() {
            auto data = serialPort->readAll();
            if (receiveMode->currentText() == "HEX") {      //字节模式
                QString hex = data.toHex(' ');
                receiveAera->appendPlainText(hex);
            }
            else {                                          //文本模式
                QString str = QString(data);
                receiveAera->appendPlainText(str);
            }
            });
    }else {
        QMessageBox::critical(this, QString::fromLocal8Bit("串口打开失败"), QString::fromLocal8Bit("请确认串口是否正确连接"));
    }
}

//刷新可用串口
void Serial::RefreshPort(void) {
    QVector<QString> temp;
    //获取当前可用串口号
    for (const QSerialPortInfo& info : QSerialPortInfo::availablePorts()) {
        temp.push_back(info.portName());
    }
    //排序现有的串口号,用于比较和原有的差距
    std::sort(temp.begin(), temp.end());//qsort被弃用,奇怪的是没有用std命名空间，加了头文件algorithm
    if (temp != ports) {  //如果可用串口号有变化
        portNumber->clear();  //清除原有列表
        ports = temp;         //更新串口列表
        for (auto& a : ports) {     //更新新串口
            portNumber->addItem(a);
        }
    }
}

void Serial::timerEvent(QTimerEvent* e) {
//    QVector<QString> temp;
//    for(const QSerialPortInfo& info:QSerialPortInfo::availablePorts()){
//        temp.push_back(info.portName());
//    }
//    qSort(temp.begin(),temp.end());
//    if(temp!=ports){

//    }
    if(e->timerId()==id) RefreshPort();    //更新端口
}

/************************* *******************/

void Serial::BeginUSART(QWidget* parent) {
    QPushButton* startUSART = new QPushButton("串口连接",parent);
    QPushButton* endUSART = new QPushButton("断开连接",parent);
    endUSART->setFixedSize(150, 50);
    endUSART->move(600, 660);
    startUSART->setFixedSize(150, 50);
    startUSART->move(450,660);
    endUSART->setDisabled(true);        //一开始没有连接串口,因此关闭按钮初始化为无效
    //为关闭连接按钮配置信号槽
    QObject::connect(endUSART, &QPushButton::clicked, [&]() {
        endUSART->setDisabled(true);        //使关闭连接按钮失效
        startUSART->setDisabled(false);     //使连接按钮生效
        sendButton->setDisabled(true);      //使发送按钮失效
        serialPort->close();                //断开串口连接
        });
    //为连接按钮配置信号槽
    QObject::connect(startUSART, &QPushButton::clicked, [&]() {
        QString port = portNumber->currentText();
        QString baud = baudRate->currentText();
        QString data = dataSize->currentText();
        QString stop = stopSize->currentText();
        QString ch = check->currentText();
        QString receive = receiveMode->currentText();
        QString send = sendMode->currentText();
        if (port != "") {       //当串口号不为空,即有效时
            endUSART->setDisabled(false);   //使关闭连接按钮生效
            sendButton->setDisabled(false); //使发送按钮生效
            startUSART->setDisabled(true);  //使连接按钮失效
            USART(port,baud,data,stop,ch);  //连接串口
        }
        });
}
Serial::~Serial()
{

}

