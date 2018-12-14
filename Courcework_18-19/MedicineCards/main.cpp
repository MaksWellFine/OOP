#include "loginwindow.h"
#include "registrationwindow.h"
#include "serialcommunicationwithcard.h"
#include "widgetschedule.h"
#include "widgetspecialty.h"
#include <QApplication>
#include <hospitaldatabasehelper.h>
#include <QMessageBox>
#include <iostream>
#include <QtSerialPort/QtSerialPort>

using namespace std;

QString Privilegies[]{ "Admin", "Recorder", "Doctor", "Patient" };

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HospitalDatabaseHelper db;
    db.InitializeDatabase();
    User::ConnectDatabase(&db);

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QList<QString> portNames;
    for(int i = 0; i < ports.length(); i++)
        portNames.append(ports[i].portName());
    SerialCommunicationWithCard serial(portNames);

    //serial.AddCardAddListener([](QString str)-> void{ qDebug() << "Connected card: " << str; });
    //serial.RequestCard();

    QList<User> users = db.GetUsers("");
    RegistrationWindow* reg;
    LoginWindow* log;
    //log.show();
    if(db.GetUsers(HospitalDatabaseHelper::ARG_USERS_PRIVILEGIES+"%2=1").length()==0)
    {
        reg = new RegistrationWindow(&serial);
        reg->show();
    }
    else
    {
        log = new LoginWindow(&serial);
        log->show();
    }


    return a.exec();
}
