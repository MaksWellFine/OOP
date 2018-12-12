#include "loginwindow.h"
#include "registrationwindow.h"
#include "widgetspecialty.h"
#include <QApplication>
#include <hospitaldatabasehelper.h>
#include <QMessageBox>
#include <iostream>

using namespace std;

QString Privilegies[]{ "Admin", "Recorder", "Doctor", "Patient" };

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HospitalDatabaseHelper db;
    db.InitializeDatabase();
    User::ConnectDatabase(&db);


    QList<User> users = db.GetUsers("");
    RegistrationWindow reg;
    LoginWindow log;
    if(db.GetUsers(HospitalDatabaseHelper::ARG_USERS_PRIVILEGIES+"%2=1").length()==0)
        reg.show();
    else
        log.show();


    return a.exec();
}
