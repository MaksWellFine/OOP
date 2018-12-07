#pragma once

#ifndef USER_H
#define USER_H

#include "hospitaldatabasehelper.h"
#include "databaseresponse.h"

#include <QString>
#include <QDateTime>

class HospitalDatabaseHelper;

class User
{
    static HospitalDatabaseHelper* helper;

    const static QString DEFAULT_CARD_ID_VAL;    

    QString cardId = DEFAULT_CARD_ID_VAL;
    bool isCardConnected;

    QString login;
    QString password;
    QString surname;
    QString name;
    QString fatherName;
    QDate dateOfBirthd;
    QString address;
    QString phoneNumber;
    int privilegies;

    bool isLogined;

public:
    const static int privilegiesCount = 4;
    const static QString DATE_OF_BIRTHD_FORMAT;
    enum Privilegies{ Admin=0, Recorder=1, Doctor=2, Patient=3 };

    User(User *user);
    User(QString cardId);
    User(QString login, QString password);
    User(QString login, QString password, QString surname, QString name, QString fatherName,
         QDate dateOfBirthd, QString address, QString phoneNumber, int privilegies = 0);

    void AddPrivilegy(Privilegies privilegy);
    void RemovePrivilegy(Privilegies privilegy);
    bool IsPrivilegyExist(Privilegies pr);

    void ConnectCard(QString id, bool isCheckUnique = false);
    bool IsCardConnected();

    QString GetCardId();
    QString& GetLogin();
    QString& GetPassword();
    QString& GetSurname();
    QString& GetName();
    QString& GetFatherName();
    QDate& GetDateOfBirthd();
    QString& GetAddress();
    QString& GetPhoneNumber();
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

    static void ConnectDatabase(HospitalDatabaseHelper *database);

    bool SaveToDB();
    bool LoadFromDB();
};

#endif // USER_H
