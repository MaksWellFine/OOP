#include "patientrecord.h"

const QString PatientRecord::DATE_TIME_FORMAT = "dd.MM.yyyy HH:mm";

PatientRecord::PatientRecord(User* user, Doctor* doctor, QDateTime* visitDateTime, QTime* visitDuration, QString* visitData, bool isVisited)
{
    this->user = user;
    this->doctor = doctor;
    this->visitDateTime = visitDateTime;
    this->visitDuration = visitDuration;
    this->visitData = visitData;
    this->isVisited = isVisited;
}

User* PatientRecord::GetUser(){return user;}
Doctor* PatientRecord::GetDoctor(){return doctor;}
QDateTime* PatientRecord::GetVisitDateTime(){return visitDateTime;}
QTime* PatientRecord::GetVisitDuration(){return visitDuration;}
QString* PatientRecord::GetVisitInfo(){return visitData;}
bool PatientRecord::IsVisited(){return isVisited;}

void PatientRecord::SetVisitInfo(QString* data){visitData = data;}
void PatientRecord::SetVisited(){isVisited = true;}

bool PatientRecord::SaveToDB()
{
    user->GetDatabase()->GetError();
    user->GetDatabase()->SavePatientRecord(this);
    if(user->GetDatabase()->IsErrorExists())
        return false;
    else return true;
}

QList<PatientRecord> PatientRecord::LoadFromDB(User* user)
{
    return user->GetDatabase()->GetPatientRecords(user);
}

QList<PatientRecord> PatientRecord::LoadFromDB(Doctor* doctor)
{
    return doctor->GetUser()->GetDatabase()->GetPatientRecords(doctor);
}
