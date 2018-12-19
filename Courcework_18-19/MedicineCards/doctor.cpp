#include "doctor.h"

const QString Doctor::DATE_FORMAT = "dd.MM.yyyy";
const QString Doctor::TIME_FORMAT = "HH:mm";

Doctor::Doctor(Doctor* doctor)
{
    user = doctor->GetUser();
    speciality = doctor->GetSpeciality();
    workTimes = doctor->GetWorkTimes();
}

Doctor::Doctor(User *user, QString speciality,  QList<WorkTime> workTimes)
{
    this->user = user;
    if(user==nullptr) return;
    /*if(user->GetDatabase()->GetSpecialities("").contains(speciality))
    {
        this->speciality = speciality;
    }else
    {
        user->GetDatabase()->SaveSpeciality(speciality);
        this->speciality = speciality;
    }*/
    this->speciality = speciality;
    this->workTimes = workTimes;
}

Doctor* Doctor::CreateDoctor(User *user, QString speciality, QList<WorkTime> workTimes)
{
    if(user != nullptr && user->IsPrivilegyExist(User::Privilegies::Doctor))
    {
        Doctor* doctor = new Doctor(user, speciality, workTimes);
        return doctor;
    }
    else
        return nullptr;
}

WorkTime::WorkTime(QString cabinet, QPair<QTime, QTime> workTime, Day workDay)
{
    this->cabinet = cabinet;
    this->workTime = workTime;
    this->workDay = workDay;
}

bool WorkTime::IsEquals(WorkTime workT)
{
    return (workT.cabinet.compare(cabinet) == 0 &&
            workT.workTime.first.msecsSinceStartOfDay() == workTime.first.msecsSinceStartOfDay() &&
            workT.workTime.second.msecsSinceStartOfDay() == workTime.second.msecsSinceStartOfDay() &&
            workT.workDay == workDay);
}

User* Doctor::GetUser()
{
    if(user != nullptr)
        return user;
    else
        return nullptr;
}

QString Doctor::GetSpeciality(){ return speciality; }

void Doctor::SetSpeciality(QString spec){ speciality = spec; }

QList<WorkTime> Doctor::GetWorkTimes()
{
    return workTimes;
}

bool Doctor::SaveToDB()
{
    if(user == nullptr || user->GetDatabase()==nullptr) return false;
    HospitalDatabaseHelper *helper = user->GetDatabase();

    helper->GetError();
    helper->SaveDoctor(this);
    return !helper->IsErrorExists();
}

Doctor* Doctor::LoadFromDB(User* user)
{
    if(user == nullptr || user->GetDatabase()==nullptr) return nullptr;
    HospitalDatabaseHelper *helper = user->GetDatabase();

    QList<Doctor> list = helper->GetDoctors(user);
    if(helper->IsErrorExists() || list.length() != 1) return nullptr;

    return new Doctor(list[0]);
}
