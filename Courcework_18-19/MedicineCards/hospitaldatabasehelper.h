#pragma once

#ifndef HOSPITALDATABASEHELPER_H
#define HOSPITALDATABASEHELPER_H

#include "databasehelper.h"
#include "doctor.h"
#include "user.h"

#include <QCoreApplication>

class User;
class Doctor;
struct WorkTime;
class HospitalDatabaseHelper: public DatabaseHelper
{
    void RefreshWorkTimes(int userId, QList<WorkTime> workTimesNew);
    QList<WorkTime> GetWorkTimes(int doctorId);
public:
    const static QString DB_NAME;

    const static QString TABLE_USERS_NAME;
    const static QString ARG_USERS_ID;
    const static QString ARG_USERS_CARD_ID;
    const static QString ARG_USERS_LOGIN;
    const static QString ARG_USERS_PASSWORD;
    const static QString ARG_USERS_SURNAME;
    const static QString ARG_USERS_NAME;
    const static QString ARG_USERS_FATHER_NAME;
    const static QString ARG_USERS_DATE_OF_BIRTHD;
    const static QString ARG_USERS_ADDRESS;
    const static QString ARG_USERS_PHONE_NUMBER;
    const static QString ARG_USERS_PRIVILEGIES;

    const static QString TABLE_DOCTORS_NAME;
    const static QString ARG_DOCTORS_ID;
    const static QString ARG_DOCTORS_USER_ID;
    const static QString ARG_DOCTORS_SPECIALITY_ID;

    const static QString TABLE_SPECIALITIES_NAME;
    const static QString ARG_SPECIALITIES_ID;
    const static QString ARG_SPECIALITIES_SPECIALITY;

    const static QString TABLE_RECORDS_NAME;
    const static QString ARG_RECORDS_ID;
    const static QString ARG_RECORDS_USER_ID;
    const static QString ARG_RECORDS_DOCTOR_ID;
    const static QString ARG_RECORDS_VISIT_DATE;
    const static QString ARG_RECORDS_VISIT_DURATION;
    const static QString ARG_RECORDS_VISIT_DATA;
    const static QString ARG_RECORDS_IS_VERIFIED;

    const static QString TABLE_DOCTORS_WORKTIME_NAME;
    const static QString ARG_DOCTORS_WORKTIME_DOCTOR_ID;
    const static QString ARG_DOCTORS_WORKTIME_START_WORK_AT;
    const static QString ARG_DOCTORS_WORKTIME_END_WORK_AT;
    const static QString ARG_DOCTORS_WORKTIME_WORK_DAY;
    const static QString ARG_DOCTORS_WORKTIME_CABINET;

    HospitalDatabaseHelper();
    void InitializeDatabase() override;

    void SaveUser(User* user);
    QList<User> GetUsers(QString condition);
    void DeleteUser(User* user);

    void SaveSpeciality(QString spec);
    QList<QString> GetSpecialities(QString condition);
    void DeleteSpeciality(QString spec);

    void SaveDoctor(Doctor* doctor);
    QList<Doctor> GetDoctors(QString condition, User *user=nullptr);
    QList<Doctor> GetDoctors(User *user);
    void DeleteDoctor(Doctor* doctor);
};

#endif // HOSPITALDATABASEHELPER_H
