#include "serialcommunicationwithcard.h"
#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include <QtSerialPort/QtSerialPort>

const QString SerialCommunicationWithCard::codingKey = "whd22fke";
const int SerialCommunicationWithCard::readInterval = 200;
const QString SerialCommunicationWithCard::NO_CARD_CONNECTED = "_";

SerialCommunicationWithCard::SerialCommunicationWithCard(QList<QString> availablePortNames)
{
    availablePorts = availablePortNames;
    serial = new QSerialPort(this);    

    thread = new QThread(this);
    connect(thread, &QThread::started, [=](){
        timer = new QTimer(thread);
        timer->setInterval(100);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(ReadData()));
        timer->start();
    });
    thread->start();

    isWrite = true;
}

SerialCommunicationWithCard::~SerialCommunicationWithCard()
{
}

void SerialCommunicationWithCard::Disconnect()
{
    WriteData(QByteArray::fromStdString("-"));
    //thread->requestInterruption();
    //CloseSerialPort();
}

void SerialCommunicationWithCard::CheckComPort(int indx)
{
    nowCheckPort++;
    if(indx >= availablePorts.length())
    {
        ShowStatusMessage("Неможливо знайти зчитувач карток! Перевірте чи він підключений!");
        return;
    }
    CloseSerialPort();
    serial->setPortName(availablePorts[indx]);    
    if (!serial->isOpen() && serial->open(QIODevice::ReadWrite))
    {
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        serial->clear(Direction::Input);

        WriteData(QByteArray::fromStdString("?"));
    }else{
        CheckComPort(nowCheckPort);
    }
}

void SerialCommunicationWithCard::CloseSerialPort()
{
    isPortOpened = false;
    if (serial->isOpen())    
        serial->close();    

    //ShowStatusMessage(tr("Disconnected"));
}

void SerialCommunicationWithCard::WriteData(const QByteArray &data, bool addToQueue)
{
    if(!addToQueue)
    {
        serial->clear(Direction::Output);
        serial->write(data);

        writeTime = QDateTime::currentDateTime();
        isWrite = true;
    }else
        writeQueue.append(data);
}

void SerialCommunicationWithCard::ReadData()
{        
    if(isPortOpened)
    {
        if(writeQueue.length() > 0)
        {
            for(int i = 0; i < writeQueue.length(); i++)
                WriteData(writeQueue[i]);
            writeQueue.clear();
        }
    }

    if((isWrite && QDateTime::currentDateTime().toMSecsSinceEpoch() - writeTime.toMSecsSinceEpoch() > readInterval) ||
            (isPortOpened && QDateTime::currentDateTime().toMSecsSinceEpoch() - readTime.toMSecsSinceEpoch() > readInterval))
    {
        isWrite = false;
        QByteArray data = serial->readAll();
        //qDebug()<<"read "<<QString::fromStdString(data.toStdString());

        if(!isPortOpened)
        {
            QString readStr = QString::fromStdString(data.toStdString());
            if(readStr == "CardReader\n")
                OnPortOpened();
            else
                CheckComPort(nowCheckPort);
        }else
        {
            readTime = QDateTime::currentDateTime();
            for(int i = 0; i < data.length(); i++)
                if(data.at(i) != '\n')
                {
                    readData.append(data.at(i));
                }
                else{
                    OperateReadData();
                    readData.clear();
                }
        }
    }
}

void SerialCommunicationWithCard::OperateReadData()
{
    QString decodedData = EncodingData(readData);
    QString result = NO_CARD_CONNECTED;
    if(decodedData != "_")
    {
        result = decodedData;
        //qDebug()<<decodedData;
    }
    for(int i = 0; i < listeners.length(); i++)
        listeners[i](result);
}

QString SerialCommunicationWithCard::EncodingData(QList<char> data, bool isCode)
{
    QString encodedStr = "";
    for(int i = 0; i < data.length(); i++)
        if(isCode)
            encodedStr.append(QChar((data.at(i)+codingKey.at(i%codingKey.length()).toLatin1())%256));
        else
            encodedStr.append(QChar((data.at(i)-codingKey.at(i%codingKey.length()).toLatin1()+256)%256));
    return encodedStr;
}

void SerialCommunicationWithCard::HandleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        CloseSerialPort();
        ShowStatusMessage("Зчитувач карток відключено! Підключіть зчитувач і перезапустіть програму.");
    }    
}


void SerialCommunicationWithCard::ShowStatusMessage(const QString &message)
{
    QMessageBox msg;
    msg.setText(QString::fromStdString(message.toStdString()));
    msg.exec();
    //qDebug() << message;
}

void SerialCommunicationWithCard::OnPortOpened()
{
    isPortOpened = true;
    WriteData(QByteArray::fromStdString("+"));
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(HandleError(QSerialPort::SerialPortError)));

    QMessageBox msg;
    msg.setText("Зчитувач карток підключено!");
    msg.exec();
}

void SerialCommunicationWithCard::AddCardAddListener(OnCardAddFunct* funct)
{
    listeners.append(funct);
}

void SerialCommunicationWithCard::RemoveCardAddListener(OnCardAddFunct* funct)
{
    if(listeners.contains(funct))
        listeners.removeOne(funct);
}

void SerialCommunicationWithCard::RequestCard()
{
    WriteData(QByteArray::fromStdString("="), true);
}
