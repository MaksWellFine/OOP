#ifndef SERIALCOMMUNICATIONWITHCARD_H
#define SERIALCOMMUNICATIONWITHCARD_H

#include <QtSerialPort/QtSerialPort>


class SerialCommunicationWithCard: public QSerialPort
{
    Q_OBJECT

public:
    typedef void(OnCardAddFunct)(QString);

    SerialCommunicationWithCard(QList<QString> availablePortNames);
    virtual ~SerialCommunicationWithCard(){};    

private:
    const static QString codingKey;
    const static int readInterval;

    QSerialPort* serial;
    QTimer *timer;
    QThread *thread;

    QList<QString> availablePorts;
    bool isPortOpened =false;
    int nowCheckPort = 0;
    bool isWrite = false;
    QDateTime writeTime;
    QDateTime readTime;

    QList<char> readData;

    QList<QByteArray> writeQueue;

    QList<OnCardAddFunct* > listeners;

    void ShowStatusMessage(const QString &message);
    void CheckComPort(int indx);
    void OnPortOpened();
    void OperateReadData();
    QString EncodingData(QList<char> data, bool isCode = false);

public:
    const static QString NO_CARD_CONNECTED;

    void AddCardAddListener(OnCardAddFunct* funct);
    void RemoveCardAddListener(OnCardAddFunct* funct);
    void RequestCard();

public slots:    
    void CloseSerialPort();
    void WriteData(const QByteArray &data, bool addToQueue = false);
    void HandleError(QSerialPort::SerialPortError error);
    void ReadData();
};

#endif // SERIALCOMMUNICATIONWITHCARD_H
