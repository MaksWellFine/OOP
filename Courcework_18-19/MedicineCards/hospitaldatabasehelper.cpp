#include "hospitaldatabasehelper.h"

#include <QMessageBox>

const QString HospitalDatabaseHelper::DB_NAME                             = "hospital";

const QString HospitalDatabaseHelper::TABLE_USERS_NAME                    = "users";
const QString HospitalDatabaseHelper::ARG_USERS_ID                        = "id";
const QString HospitalDatabaseHelper::ARG_USERS_CARD_ID                   = "card_id";
const QString HospitalDatabaseHelper::ARG_USERS_LOGIN                     = "login";
const QString HospitalDatabaseHelper::ARG_USERS_PASSWORD                  = "password";
const QString HospitalDatabaseHelper::ARG_USERS_SURNAME                   = "surname";
const QString HospitalDatabaseHelper::ARG_USERS_NAME                      = "name";
const QString HospitalDatabaseHelper::ARG_USERS_FATHER_NAME               = "father_name";
const QString HospitalDatabaseHelper::ARG_USERS_DATE_OF_BIRTHD            = "date_of_birthd";
const QString HospitalDatabaseHelper::ARG_USERS_ADDRESS                   = "address";
const QString HospitalDatabaseHelper::ARG_USERS_PHONE_NUMBER              = "phone_number";
const QString HospitalDatabaseHelper::ARG_USERS_PRIVILEGIES               = "privilegies";

const QString HospitalDatabaseHelper::TABLE_DOCTORS_NAME                  = "doctors";
const QString HospitalDatabaseHelper::ARG_DOCTORS_ID                      = "id";
const QString HospitalDatabaseHelper::ARG_DOCTORS_USER_ID                = "user_id";
const QString HospitalDatabaseHelper::ARG_DOCTORS_SPECIALITY_ID           = "speciality_id";

const QString HospitalDatabaseHelper::TABLE_SPECIALITIES_NAME             = "specialities";
const QString HospitalDatabaseHelper::ARG_SPECIALITIES_ID                 = "id";
const QString HospitalDatabaseHelper::ARG_SPECIALITIES_SPECIALITY         = "speciality";

const QString HospitalDatabaseHelper::TABLE_RECORDS_NAME                  = "records";
const QString HospitalDatabaseHelper::ARG_RECORDS_ID                      = "id";
const QString HospitalDatabaseHelper::ARG_RECORDS_USER_ID                 = "user_id";
const QString HospitalDatabaseHelper::ARG_RECORDS_DOCTOR_ID               = "doctor_id";
const QString HospitalDatabaseHelper::ARG_RECORDS_VISIT_DATE              = "visit_date";
const QString HospitalDatabaseHelper::ARG_RECORDS_VISIT_DURATION          = "visit_duration";
const QString HospitalDatabaseHelper::ARG_RECORDS_VISIT_DATA              = "visit_data";
const QString HospitalDatabaseHelper::ARG_RECORDS_IS_VERIFIED             = "is_verified";

const QString HospitalDatabaseHelper::TABLE_DOCTORS_WORKTIME_NAME         = "doctors_worktime";
const QString HospitalDatabaseHelper::ARG_DOCTORS_WORKTIME_DOCTOR_ID      = "doctor_id";
const QString HospitalDatabaseHelper::ARG_DOCTORS_WORKTIME_START_WORK_AT  = "start_work_at";
const QString HospitalDatabaseHelper::ARG_DOCTORS_WORKTIME_END_WORK_AT    = "end_work_at";
const QString HospitalDatabaseHelper::ARG_DOCTORS_WORKTIME_WORK_DAY      = "work_day";
const QString HospitalDatabaseHelper::ARG_DOCTORS_WORKTIME_CABINET        = "cabinet";

HospitalDatabaseHelper::HospitalDatabaseHelper():DatabaseHelper(DB_NAME)
{

}

void HospitalDatabaseHelper::InitializeDatabase()
{       
    DatabaseHelper::InitializeDatabase();

    CreateTable(TABLE_USERS_NAME, QList<QString>{ARG_USERS_ID + " INTEGER PRIMARY KEY", ARG_USERS_CARD_ID + " VARCHAR(20)",
                ARG_USERS_LOGIN + " VARCHAR(20) NOT NULL UNIQUE", ARG_USERS_PASSWORD + " VARCHAR(20) NOT NULL",
                ARG_USERS_SURNAME + " VARCHAR(30)", ARG_USERS_NAME + " VARCHAR(30)", ARG_USERS_FATHER_NAME + " VARCHAR(30)",
                ARG_USERS_DATE_OF_BIRTHD + " DATE", ARG_USERS_ADDRESS + " VARCHAR(40)", ARG_USERS_PHONE_NUMBER + " VARCHAR(13)", ARG_USERS_PRIVILEGIES + " INTEGER NOT NULL"});

    CreateTable(TABLE_DOCTORS_NAME, QList<QString>{ARG_DOCTORS_ID + " INTEGER PRIMARY KEY",
                ARG_DOCTORS_USER_ID + " INTEGER NOT NULL UNIQUE", ARG_DOCTORS_SPECIALITY_ID + " INTEGER NOT NULL"});

    CreateTable(TABLE_DOCTORS_WORKTIME_NAME, QList<QString>{ARG_DOCTORS_WORKTIME_DOCTOR_ID + " INTEGER NOT NULL",
                ARG_DOCTORS_WORKTIME_START_WORK_AT + " TIME NOT NULL", ARG_DOCTORS_WORKTIME_END_WORK_AT + " TIME NOT NULL",
                ARG_DOCTORS_WORKTIME_WORK_DAY + " INT NOT NULL", ARG_DOCTORS_WORKTIME_CABINET + " VARCHAR(10) NOT NULL"});

    CreateTable(TABLE_SPECIALITIES_NAME, QList<QString>{ARG_SPECIALITIES_ID + " INTEGER PRIMARY KEY",
                ARG_SPECIALITIES_SPECIALITY + " VARCHAR(30) NOT NULL UNIQUE"});

    CreateTable(TABLE_RECORDS_NAME, QList<QString>{ARG_RECORDS_ID + " INTEGER PRIMARY KEY", ARG_RECORDS_USER_ID + " INTEGER NOT NULL",
                ARG_RECORDS_DOCTOR_ID + " INTEGER NOT NULL", ARG_RECORDS_VISIT_DATE + " DATETIME NOT NULL",
                ARG_RECORDS_VISIT_DURATION + " TIME NOT NULL", ARG_RECORDS_VISIT_DATA + " TEXT NOT NULL",
                ARG_RECORDS_IS_VERIFIED + " BOOL NOT NULL"});
}

void HospitalDatabaseHelper::SaveUser(User* user)
{
    Update(TABLE_USERS_NAME, QList<QString>{ARG_USERS_CARD_ID, ARG_USERS_LOGIN, ARG_USERS_PASSWORD, ARG_USERS_SURNAME, ARG_USERS_NAME,
        ARG_USERS_FATHER_NAME, ARG_USERS_DATE_OF_BIRTHD, ARG_USERS_ADDRESS, ARG_USERS_PHONE_NUMBER, ARG_USERS_PRIVILEGIES},
        QList<QString>{user->GetCardId(), user->GetLogin(), user->GetPassword(), user->GetSurname(), user->GetName(), user->GetFatherName(),
                       user->GetDateOfBirthd().toString(User::DATE_OF_BIRTHD_FORMAT), user->GetAddress(), user->GetPhoneNumber(), QString::number(user->GetPrivilegies())},
        ARG_USERS_LOGIN+"="+"'"+user->GetLogin()+"'");
    if(databaseQuery.numRowsAffected() == 0)
    {
        Insert(TABLE_USERS_NAME, QList<QString>{ARG_USERS_CARD_ID, ARG_USERS_LOGIN, ARG_USERS_PASSWORD, ARG_USERS_SURNAME, ARG_USERS_NAME,
            ARG_USERS_FATHER_NAME, ARG_USERS_DATE_OF_BIRTHD, ARG_USERS_ADDRESS, ARG_USERS_PHONE_NUMBER, ARG_USERS_PRIVILEGIES},
            QList<QList<QString>>{{user->GetCardId(), user->GetLogin(), user->GetPassword(), user->GetSurname(), user->GetName(), user->GetFatherName(),
            user->GetDateOfBirthd().toString(User::DATE_OF_BIRTHD_FORMAT), user->GetAddress(), user->GetPhoneNumber(), QString::number(user->GetPrivilegies())}});
    }
}

QList<User> HospitalDatabaseHelper::GetUsers(QString condition)
{    
    DatabaseResponse *response = Select(TABLE_USERS_NAME, QList<QString>{ARG_USERS_CARD_ID, ARG_USERS_LOGIN, ARG_USERS_PASSWORD, ARG_USERS_SURNAME, ARG_USERS_NAME,
            ARG_USERS_FATHER_NAME, ARG_USERS_DATE_OF_BIRTHD, ARG_USERS_ADDRESS, ARG_USERS_PHONE_NUMBER, ARG_USERS_PRIVILEGIES},
            condition);

    QList<User> users;
    if(response->IsError()) return users;

    QSqlRecord record = response->GetRecord();
    while(databaseQuery.next())
    {
        User user(databaseQuery.value(record.indexOf(ARG_USERS_LOGIN)).toString(), databaseQuery.value(record.indexOf(ARG_USERS_PASSWORD)).toString(),
                    databaseQuery.value(record.indexOf(ARG_USERS_SURNAME)).toString(), databaseQuery.value(record.indexOf(ARG_USERS_NAME)).toString(),
                    databaseQuery.value(record.indexOf(ARG_USERS_FATHER_NAME)).toString(), QDate::fromString(databaseQuery.value(record.indexOf(ARG_USERS_DATE_OF_BIRTHD)).toString(), User::DATE_OF_BIRTHD_FORMAT),
                    databaseQuery.value(record.indexOf(ARG_USERS_ADDRESS)).toString(), databaseQuery.value(record.indexOf(ARG_USERS_PHONE_NUMBER)).toString(),
                    databaseQuery.value(record.indexOf(ARG_USERS_PRIVILEGIES)).toInt());
        user.ConnectCard(databaseQuery.value(record.indexOf(ARG_USERS_CARD_ID)).toString());
        users.append(user);
    }   

    return users;
}


void HospitalDatabaseHelper::DeleteUser(User* user)
{
    for(int i = 0; i < user->privilegiesCount; i++)
        user->RemovePrivilegy(((User::Privilegies)i));
    Delete(TABLE_USERS_NAME, ARG_USERS_LOGIN+"='"+user->GetLogin()+"'");
}

void HospitalDatabaseHelper::SaveSpeciality(QString spec)
{
    if(GetSpecialities(ARG_SPECIALITIES_SPECIALITY+"='"+spec+"'").length()==0)
        Insert(TABLE_SPECIALITIES_NAME, QList<QString>{ARG_SPECIALITIES_SPECIALITY},
                                        QList<QList<QString>>{{spec}});    
}

QList<QString> HospitalDatabaseHelper::GetSpecialities(QString condition)
{
    DatabaseResponse *response = Select(TABLE_SPECIALITIES_NAME, QList<QString>{ARG_SPECIALITIES_SPECIALITY}, condition);

    QList<QString> specs;
    if(response->IsError()) return specs;

    QSqlRecord record = response->GetRecord();
    while(databaseQuery.next())
        specs.append(databaseQuery.value(record.indexOf(ARG_SPECIALITIES_SPECIALITY)).toString());

    return specs;
}

void HospitalDatabaseHelper::DeleteSpeciality(QString spec)
{
    Delete(TABLE_SPECIALITIES_NAME, ARG_SPECIALITIES_SPECIALITY+"='"+spec+"'");
}

void HospitalDatabaseHelper::SaveDoctor(Doctor* doctor)
{
    //Search user ID and speciality ID
    int userId, specId;

    DatabaseResponse *response = Select(TABLE_USERS_NAME, QList<QString>{ARG_USERS_ID, ARG_USERS_LOGIN},
                                        ARG_USERS_LOGIN+"='"+doctor->GetUser()->GetLogin()+"'");
    if(response->IsError())   
        return;    
    if(!databaseQuery.first())
    {
        CreateDatabaseResponse("Користувач з логіном '" + doctor->GetUser()->GetLogin() + "' не існує. Не можливо зберегти лікаря.");
        return;
    }else userId = databaseQuery.value(response->GetRecord().indexOf(ARG_USERS_ID)).toInt();


    response = Select(TABLE_SPECIALITIES_NAME, QList<QString>{ARG_SPECIALITIES_ID},
                      ARG_SPECIALITIES_SPECIALITY+"='"+doctor->GetSpeciality()+"'");    
    if(!databaseQuery.first())
    {
        CreateDatabaseResponse("Професії '" + doctor->GetSpeciality() + "' не існує. Не можливо зберегти лікаря.");
        return;
    }else specId = databaseQuery.value(response->GetRecord().indexOf(ARG_SPECIALITIES_ID)).toInt();

    //Create or upadate doctor
    response = Update(TABLE_DOCTORS_NAME, QList<QString>{ARG_DOCTORS_SPECIALITY_ID},
                QList<QString>{QString::number(specId)},
                ARG_DOCTORS_USER_ID+"="+"'"+QString::number(userId)+"'");
    if(databaseQuery.numRowsAffected() == 0)
    {
        response = Insert(TABLE_DOCTORS_NAME, QList<QString>{ARG_DOCTORS_USER_ID, ARG_DOCTORS_SPECIALITY_ID},
                    QList<QList<QString>>{{QString::number(userId), QString::number(specId)}});
    }

    if(response->IsError()) return;    

    RefreshWorkTimes(userId, doctor->GetWorkTimes());
}

QList<Doctor> HospitalDatabaseHelper::GetDoctors(QString condition, User* user)
{
    DatabaseResponse *response = Select(TABLE_DOCTORS_NAME, QList<QString>{ARG_DOCTORS_ID, ARG_DOCTORS_USER_ID, ARG_DOCTORS_SPECIALITY_ID}, condition);
    QSqlRecord record = response->GetRecord();
    QList<Doctor> doctors;
    while(databaseQuery.next())
    {
        int userId = databaseQuery.value(record.indexOf(ARG_DOCTORS_USER_ID)).toInt();
        int specId = databaseQuery.value(record.indexOf(ARG_DOCTORS_SPECIALITY_ID)).toInt();
        int doctorId = databaseQuery.value(record.indexOf(ARG_DOCTORS_ID)).toInt();        
        if(user==nullptr)
        {
            QList<User> users = GetUsers(ARG_USERS_ID+"='"+QString::number(userId)+"'");
            if(users.length() > 0)
                user = new User(users[0]);
            else
                continue;
        }

        QString specName;
        QList<QString> specNames = GetSpecialities(ARG_SPECIALITIES_ID+"='"+QString::number(specId)+"'");
        if(specNames.length() > 0)
            specName = specNames[0];
        else
            continue;


        QList<WorkTime> workTimes = GetWorkTimes(doctorId);

        doctors.append(*Doctor::CreateDoctor(user, specName, workTimes));
    }
    return doctors;
}

QList<Doctor> HospitalDatabaseHelper::GetDoctors(User *user)
{
    DatabaseResponse *response = Select(TABLE_USERS_NAME, QList<QString>{ARG_USERS_ID, ARG_USERS_LOGIN},
                                        ARG_USERS_LOGIN+"='"+user->GetLogin()+"'");
    if(!databaseQuery.first())
    {
        CreateDatabaseResponse("Користувач з логіном '" + user->GetLogin() + "' не існує. Не можливо загрузити лікаря.");
        return QList<Doctor>{};
    }else    
        return GetDoctors(ARG_DOCTORS_USER_ID+"='"+databaseQuery.value(response->GetRecord().indexOf(ARG_USERS_ID)).toString()+"'", user);
}

void HospitalDatabaseHelper::DeleteDoctor(Doctor* doctor)
{
    int userId;
    DatabaseResponse *response = Select(TABLE_USERS_NAME, QList<QString>{ARG_USERS_ID, ARG_USERS_LOGIN},
                                        ARG_USERS_LOGIN+"='"+doctor->GetUser()->GetLogin()+"'");
    if(!databaseQuery.first())
    {
        CreateDatabaseResponse("Користувач з логіном '" + doctor->GetUser()->GetLogin() + "' не існує. Не можливо загрузити лікаря.");
        return;
    }else
        userId = databaseQuery.value(response->GetRecord().indexOf(ARG_USERS_ID)).toInt();
    response = Delete(TABLE_DOCTORS_NAME, ARG_DOCTORS_USER_ID+"='"+QString::number(userId)+"'");

    if(response->IsError())
    {
        CreateDatabaseResponse("Не можливо видалити лікаря");
        return;
    }else
    {
        RefreshWorkTimes(userId, QList<WorkTime>{});
    }
}

void HospitalDatabaseHelper::RefreshWorkTimes(int userId, QList<WorkTime> workTimesNew)
{
    //Search now operating doctor ID
    int doctorId;
    DatabaseResponse* response = Select(TABLE_DOCTORS_NAME, QList<QString>{ARG_DOCTORS_ID},
                                        ARG_DOCTORS_USER_ID+"='"+QString::number(userId)+"'");
    if(!databaseQuery.first())
    {
        CreateDatabaseResponse("Лікаря з id '" + QString::number(userId) + "' не існує. Не можливо зберегти лікаря.");
        return;
    }else doctorId = databaseQuery.value(response->GetRecord().indexOf(ARG_DOCTORS_ID)).toInt();

    //Search available worktimes for doctor
    QList<WorkTime> workTimesOld = GetWorkTimes(doctorId);

    //Add new worktimes and remove old
    QList<int> indexesToAdd; //From new list
    QList<int> indexesToRemove; //From old list
    for(int i = 0; i < workTimesOld.length(); i++)
    {
        bool isContain = false;
        for(int q = 0; q < workTimesNew.length(); q++)
        {
            if(workTimesNew[q].IsEquals(workTimesOld[i]))
            {
                isContain = true;
                break;
            }
        }
        if(!isContain) indexesToRemove.append(i);
    }
    for(int i = 0; i < workTimesNew.length(); i++)
    {
        bool isContain = false;
        for(int q = 0; q < workTimesOld.length(); q++)
            if(workTimesOld[q].IsEquals(workTimesNew[i]))
            {
                if(isContain)
                {
                    if(!indexesToRemove.contains(q))
                    {
                        indexesToRemove.append(q);
                        indexesToAdd.append(i);
                        break;
                    }
                }else
                    isContain = true;
            }
        if(!isContain) indexesToAdd.append(i);
    }

    for(int i = 0; i < indexesToRemove.length(); i++)
    {
        WorkTime oldWorkTime = workTimesOld[indexesToRemove[i]];
        response = Delete(TABLE_DOCTORS_WORKTIME_NAME, ARG_DOCTORS_WORKTIME_DOCTOR_ID+"='"+QString::number(doctorId)+"' AND "+
               ARG_DOCTORS_WORKTIME_CABINET+"='"+oldWorkTime.cabinet+"' AND "+
               ARG_DOCTORS_WORKTIME_WORK_DAY+"='"+QString::number(oldWorkTime.workDay)+"' AND "+
               ARG_DOCTORS_WORKTIME_START_WORK_AT+"='"+oldWorkTime.workTime.first.toString(Doctor::TIME_FORMAT)+"' AND "+
               ARG_DOCTORS_WORKTIME_END_WORK_AT+"='"+oldWorkTime.workTime.second.toString(Doctor::TIME_FORMAT)+"'");
    }
    if(response->IsError())
    {
        CreateDatabaseResponse("Неможливо видалити деякі записи про робочий час лікаря!");
    }
    for(int i = 0; i < indexesToAdd.length(); i++)
    {
        WorkTime newWorkTime = workTimesNew[indexesToAdd[i]];
        response = Insert(TABLE_DOCTORS_WORKTIME_NAME, QList<QString>{ARG_DOCTORS_WORKTIME_DOCTOR_ID, ARG_DOCTORS_WORKTIME_CABINET,
               ARG_DOCTORS_WORKTIME_WORK_DAY, ARG_DOCTORS_WORKTIME_START_WORK_AT, ARG_DOCTORS_WORKTIME_END_WORK_AT},
               QList<QList<QString>>{{QString::number(doctorId), newWorkTime.cabinet, QString::number(newWorkTime.workDay),
                   newWorkTime.workTime.first.toString(Doctor::TIME_FORMAT), newWorkTime.workTime.second.toString(Doctor::TIME_FORMAT)}});
    }
    if(response->IsError())
    {
        CreateDatabaseResponse("Неможливо додати деякі записи про робочий час лікаря!");
    }
}

QList<WorkTime> HospitalDatabaseHelper::GetWorkTimes(int doctorId)
{
    DatabaseResponse* response = Select(TABLE_DOCTORS_WORKTIME_NAME, QList<QString>{ARG_DOCTORS_WORKTIME_DOCTOR_ID, ARG_DOCTORS_WORKTIME_CABINET,
        ARG_DOCTORS_WORKTIME_WORK_DAY, ARG_DOCTORS_WORKTIME_START_WORK_AT, ARG_DOCTORS_WORKTIME_END_WORK_AT},
                                        ARG_DOCTORS_WORKTIME_DOCTOR_ID+"='"+QString::number(doctorId)+"'");
    QList<WorkTime> workTimes;

    //return;
    if(response->IsError()) return workTimes;

    QSqlRecord record = response->GetRecord();
    while(databaseQuery.next())
    {
        QString cabinet = databaseQuery.value(record.indexOf(ARG_DOCTORS_WORKTIME_CABINET)).toString();
        QPair<QTime, QTime> time(
                QTime::fromString(databaseQuery.value(record.indexOf(ARG_DOCTORS_WORKTIME_START_WORK_AT)).toString(), Doctor::TIME_FORMAT),
                QTime::fromString(databaseQuery.value(record.indexOf(ARG_DOCTORS_WORKTIME_END_WORK_AT)).toString(), Doctor::TIME_FORMAT));
        int day = databaseQuery.value(record.indexOf(ARG_DOCTORS_WORKTIME_WORK_DAY)).toInt();
        workTimes.append(WorkTime(cabinet, time, (WorkTime::Day)day));
    }
    return workTimes;
}
