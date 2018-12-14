#pragma once

#ifndef PATIENTRECORD_H
#define PATIENTRECORD_H

#include "user.h"

class User;
class Doctor;

class PatientRecord
{
    User* user;
    Doctor* doctor;
    QDateTime* visitDateTime;
    QTime* visitDuration;
    QString* visitData;
    bool isVisited;

public:
    static const QString DATE_TIME_FORMAT;

    PatientRecord(User* user, Doctor* doctor, QDateTime* visitDateTime, QTime* visitDuration, QString* visitData, bool isVisited);

    User* GetUser();
    Doctor* GetDoctor();
    QDateTime* GetVisitDateTime();
    QTime* GetVisitDuration();
    QString* GetVisitInfo();
    bool IsVisited();

    void SetVisitInfo(QString* data);
    void SetVisited();

    bool SaveToDB();
    static QList<PatientRecord> LoadFromDB(User* user);
    static QList<PatientRecord> LoadFromDB(Doctor* doctor);
};

#endif // PATIENTRECORD_H
