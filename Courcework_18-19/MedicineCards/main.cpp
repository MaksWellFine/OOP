#include "loginwindow.h"
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



    QMessageBox msg;

    User user("a1b2c34");
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
    LoginWindow w;
    w.show();    

    return a.exec();
}
