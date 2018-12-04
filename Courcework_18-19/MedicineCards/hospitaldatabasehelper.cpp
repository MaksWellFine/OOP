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
const QString HospitalDatabaseHelper::ARG_DOCTORS_USERS_ID                = "user_id";
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
const QString HospitalDatabaseHelper::ARG_DOCTORS_WORKTIME_WORK_DATE      = "work_date";
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
                ARG_DOCTORS_USERS_ID + " INTEGER NOT NULL", ARG_DOCTORS_SPECIALITY_ID + " INTEGER NOT NULL"});

    CreateTable(TABLE_DOCTORS_WORKTIME_NAME, QList<QString>{ARG_DOCTORS_WORKTIME_DOCTOR_ID + " INTEGER NOT NULL",
                ARG_DOCTORS_WORKTIME_START_WORK_AT + " TIME NOT NULL", ARG_DOCTORS_WORKTIME_END_WORK_AT + " TIME NOT NULL",
                ARG_DOCTORS_WORKTIME_WORK_DATE + " DATE", ARG_DOCTORS_WORKTIME_CABINET + " VARCHAR(10)"});

    CreateTable(TABLE_SPECIALITIES_NAME, QList<QString>{ARG_SPECIALITIES_ID + " INTEGER PRIMARY KEY",
                ARG_SPECIALITIES_SPECIALITY + " VARCHAR(30)"});

    CreateTable(TABLE_RECORDS_NAME, QList<QString>{ARG_RECORDS_ID + " INTEGER PRIMARY KEY", ARG_RECORDS_USER_ID + " INTEGER NOT NULL",
                ARG_RECORDS_DOCTOR_ID + " INTEGER NOT NULL", ARG_RECORDS_VISIT_DATE + " DATETIME NOT NULL",
                ARG_RECORDS_VISIT_DURATION + " TIME NOT NULL", ARG_RECORDS_VISIT_DATA + " TEXT NOT NULL",
                ARG_RECORDS_IS_VERIFIED + " BOOL NOT NULL"});
}

void HospitalDatabaseHelper::SaveUser(User* user)
{
    /*DatabaseResponse *response = Insert(TABLE_USERS_NAME, QList<QString>{ARG_USERS_CARD_ID, ARG_USERS_LOGIN, ARG_USERS_PASSWORD, ARG_USERS_SURNAME, ARG_USERS_NAME,
            ARG_USERS_FATHER_NAME, ARG_USERS_DATE_OF_BIRTHD, ARG_USERS_ADDRESS, ARG_USERS_PHONE_NUMBER, ARG_USERS_PRIVILEGIES},
            QList<QList<QString>>{{user->GetCardId(), user->GetLogin(), user->GetPassword(), user->GetSurname(), user->GetName(), user->GetFatherName(),
            user->GetDateOfBirthd().toString("dd.MM.yyyy"), user->GetAddress(), user->GetPhoneNumber(), QString::number(user->GetPrivilegies())}});
    if(response->IsError())
    {
        QMessageBox box;
        box.setText(response->GetError());
        box.exec();
        GetError();*/
        Update(TABLE_USERS_NAME, QList<QString>{ARG_USERS_CARD_ID, ARG_USERS_LOGIN, ARG_USERS_PASSWORD, ARG_USERS_SURNAME, ARG_USERS_NAME,
                    ARG_USERS_FATHER_NAME, ARG_USERS_DATE_OF_BIRTHD, ARG_USERS_ADDRESS, ARG_USERS_PHONE_NUMBER, ARG_USERS_PRIVILEGIES},
                    QList<QString>{user->GetCardId(), user->GetLogin(), user->GetPassword(), user->GetSurname(), user->GetName(), user->GetFatherName(),
                                   user->GetDateOfBirthd().toString("dd.MM.yyyy"), user->GetAddress(), user->GetPhoneNumber(), QString::number(user->GetPrivilegies())},
                    ARG_USERS_LOGIN+"="+"'"+user->GetLogin()+"'");
    //}
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
                    databaseQuery.value(record.indexOf(ARG_USERS_FATHER_NAME)).toString(), QDate::fromString(databaseQuery.value(record.indexOf(ARG_USERS_DATE_OF_BIRTHD)).toString(), "dd.MM.yyyy"),
                    databaseQuery.value(record.indexOf(ARG_USERS_ADDRESS)).toString(), databaseQuery.value(record.indexOf(ARG_USERS_PHONE_NUMBER)).toString(),
                    databaseQuery.value(record.indexOf(ARG_USERS_PRIVILEGIES)).toInt());
        user.ConnectCard(databaseQuery.value(record.indexOf(ARG_USERS_CARD_ID)).toString());
        users.append(user);
    }

    return users;
}

