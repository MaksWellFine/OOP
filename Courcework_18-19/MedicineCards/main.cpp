#include "loginwindow.h"
#include "registrationwindow.h"
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


    //LoginWindow w;
    //w.show();

    QList<User> users = db.GetUsers("");

    RegistrationWindow reg(nullptr, &users[0], &users[1]);
    reg.show();
    LoginWindow log;
    if(db.GetUsers(HospitalDatabaseHelper::ARG_USERS_PRIVILEGIES+"%2=1").length()==0)
        reg.show();
    else
        log.show();

    //QMessageBox msg;
    //msg.setText(db.GetError());
    //msg.exec();

    /*User user("a1b2c34");
    user.IsLogined();
    user.AddPrivilegy(User::Privilegies::Patient);
    user.SaveToDB();
    /*User user("qwert", "123");
    user.ConnectCard("a1b2c34", true);
    if(user.IsCardConnected()) user.SaveToDB();
    msg.setText(QString::number(user.IsCardConnected()));
    //user.AddPrivilegy(User::Privilegies::Recorder);
    user.SaveToDB();
    //msg.setText(db.GetError());
    msg.exec();
*/
    //if(db.IsErrorExists())
        //msg.setText(db.GetError());
    //else
        //msg.setText("ok");
/*    User user("qwert", "123", "q", "w", "e", QDate(2001,01,01), "wer", "09878");
    user.AddPrivilegy(User::Privilegies::Admin);
    user.AddPrivilegy(User::Privilegies::Patient);
    user.AddPrivilegy(User::Privilegies::Doctor);
    user.RemovePrivilegy(User::Privilegies::Patient);
    user.SaveToDB();

    User user1("asdfg", "123", "q1", "w1", "e1", QDate(2002,02,02), "asd", "04334");
    user1.SaveToDB();
    user1.AddPrivilegy(User::Privilegies::Patient);
    QString str = "";
    if(!user1.SaveToDB())
    {
        str = db.GetError();
        msg.setText(str);
        msg.exec();
    }
*/

    return a.exec();
}
