#pragma once

#ifndef USER_H
#define USER_H

#include "hospitaldatabasehelper.h"
#include "databaseresponse.h"
#include "doctor.h"

#include <QString>
#include <QDateTime>

class HospitalDatabaseHelper;
class Doctor;
class User
{
    static HospitalDatabaseHelper* helper;        

    Doctor* doctor = nullptr;

    QString cardId = DEFAULT_CARD_ID_VAL;
    bool isCardConnected = false;

    QString login="";
    QString password="";
    QString surname="";
    QString name="";
    QString fatherName="";
    QDate dateOfBirthd;
    QString address="";
    QString phoneNumber="";
    int privilegies=0;

    bool isLogined;    

public:
    const static int privilegiesCount = 4;
    const static QString DATE_OF_BIRTHD_FORMAT;
    const static QString DEFAULT_CARD_ID_VAL;
    enum Privilegies{ Admin=0, Recorder=1, Doctor=2, Patient=3 };

    User(User *user);
    User(QString cardId);
    User(QString login, QString password);
    User(QString login, QString password, QString surname, QString name, QString fatherName,
         QDate dateOfBirthd, QString address, QString phoneNumber, int privilegies = 0);

    void AddPrivilegyAdmin();
    void AddPrivilegyRecorder();
    void AddPrivilegyDoctor(QString speciality = "", QList<struct WorkTime> workTimes = {});
    void AddPrivilegyPatient();
    void RemovePrivilegy(Privilegies privilegy);
    bool IsPrivilegyExist(Privilegies pr);

    void ConnectCard(QString id, bool isCheckUnique = false);
    bool IsCardConnected();

    QString GetCardId();
    QString GetLogin();
    QString GetPassword();
    QString GetSurname();
    QString GetName();
    QString GetFatherName();
    QDate GetDateOfBirthd();
    QString GetAddress();
    QString GetPhoneNumber();
    int GetPrivilegies();

    void SetPassword(QString str);
    void SetSurname(QString str);
    void SetName(QString str);
    void SetFatherName(QString str);
    void SetDateOfBirthd(QDate date);
    void SetAddress(QString str);
    void SetPhoneNumber(QString numberStr);

    bool IsLogined();
    bool Login();

    class Doctor* GetDoctor();

    static void ConnectDatabase(HospitalDatabaseHelper *database);
    HospitalDatabaseHelper* GetDatabase();

    bool SaveToDB();
    bool LoadFromDB();

    QString ToShortStr();

private:
    void AddPrivilegy(Privilegies privilegy);
};

#endif // USER_H
