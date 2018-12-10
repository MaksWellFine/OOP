#pragma once

#ifndef DOCTOR_H
#define DOCTOR_H

#include "user.h"

class HospitalDatabaseHelper;
class User;

struct WorkTime
{
    public:
        enum Day{Monday=0, Tuesday=1, Wednesday=2, Thursday=3, Friday=4, Saturday=5, Sunday=6};
        bool IsEquals(WorkTime workTime);
        WorkTime(QString cabinet, QPair<QTime, QTime> workTime, Day workDay);
        QString cabinet;
        QPair<QTime, QTime> workTime;
        Day workDay;
};

class Doctor
{
    User *user;

    QString speciality;        

public:
    const static QString DATE_FORMAT;
    const static QString TIME_FORMAT;

    static Doctor* CreateDoctor(User *user, QString speciality,  QList<WorkTime> workTimes);
    Doctor(Doctor* doctor);
    Doctor(User *user, QString speciality,  QList<WorkTime> workTimes);

    User* GetUser();

    QString GetSpeciality();
    void SetSpeciality(QString spec);

    QList<WorkTime> GetWorkTimes();

    bool SaveToDB();    
    static Doctor* LoadFromDB(User* user);
private:
    QList<WorkTime> workTimes;

};

#endif // DOCTOR_H
