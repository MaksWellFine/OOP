#include "doctor.h"
#include "user.h"

#include <QMessageBox>
#include <databasehelper.h>

HospitalDatabaseHelper* User::helper = nullptr;
const QString User::DEFAULT_CARD_ID_VAL = "null";
const QString User::DATE_OF_BIRTHD_FORMAT = "dd.MM.yyyy";

void User::ConnectDatabase(HospitalDatabaseHelper *database)
{
    helper = database;
}

HospitalDatabaseHelper* User::GetDatabase()
{
    return helper;
}

User::User(User *user)
{
    login = user->GetLogin();
    password = user->GetPassword();
    surname = user->GetSurname();
    name = user->GetName();
    fatherName = user->GetFatherName();
    address = user->GetAddress();
    SetPhoneNumber(user->GetPhoneNumber());
    dateOfBirthd = user->GetDateOfBirthd();
    ConnectCard(user->GetCardId());
    privilegies = user->GetPrivilegies();
    isLogined = user->IsLogined();
    if(user->IsPrivilegyExist(Privilegies::Doctor))
        AddPrivilegyDoctor();
}

User::User(QString cardId)
{
    ConnectCard(cardId);
    Login();
}

User::User(QString login, QString password)
{
    this->login = login;
    this->password = password;
    Login();
}

User::User(QString login, QString password, QString surname, QString name, QString fatherName,
           QDate dateOfBirthd, QString address, QString phoneNumber, int privilegies)
{    
    this->login = login;
    this->password = password;
    this->surname = surname;
    this->name = name;
    this->fatherName = fatherName;
    this->dateOfBirthd = dateOfBirthd;
    this->address = address;
    SetPhoneNumber(phoneNumber);
    this->privilegies = privilegies;
    if(IsPrivilegyExist(Privilegies::Doctor))
        AddPrivilegyDoctor();
}

void User::ConnectCard(QString id, bool isCheckUnique)
{
    bool isUnique = true;
    if(isCheckUnique)
    {
        if(helper != nullptr)
            isUnique = (helper->GetUsers(HospitalDatabaseHelper::ARG_USERS_CARD_ID+"="+"'"+id+"' AND "
                                         +HospitalDatabaseHelper::ARG_USERS_LOGIN+"!='"+login+"'").length() == 0);
        else
            isUnique = false;
    }
    if(id != DEFAULT_CARD_ID_VAL && isUnique)
    {
        cardId = id;
        isCardConnected = true;
    }else
    {
        cardId = DEFAULT_CARD_ID_VAL;
        isCardConnected = false;
    }
}

QString User::GetCardId()
{
    if(isCardConnected)
        return cardId;
    else
        return DEFAULT_CARD_ID_VAL;
}

bool User::IsCardConnected()
{
    return isCardConnected;
}

void User::SetPhoneNumber(QString numberStr)
{
    QString newStr = "";
    for(int i = 0; i < numberStr.length(); i++)
        if(numberStr[i] >= 48 && numberStr[i] <= 57)
            newStr.append(numberStr[i]);
    phoneNumber = "+" + newStr;
}

void User::AddPrivilegy(Privilegies privilegy)
{
    privilegies |= 1 << privilegy;
}

void User::AddPrivilegyAdmin()
{
    AddPrivilegy(Privilegies::Admin);
}

void User::AddPrivilegyRecorder()
{
    AddPrivilegy(Privilegies::Recorder);
}

void User::AddPrivilegyDoctor(QString speciality, QList<WorkTime> workTimes)
{
    AddPrivilegy(Privilegies::Doctor);
    bool result = true;
    QList<class Doctor> doctors = helper->GetDoctors(this);
    if(doctors.length()!=0)
    {
        QString spec = doctors[0].GetSpeciality();
        QList<WorkTime> workTs = doctors[0].GetWorkTimes();
        if(speciality != "")
            spec = speciality;
        if(workTimes.length()!=0)
            workTs = workTimes;
        doctor = new class Doctor(doctors[0].GetUser(), spec, workTs);
    }
    else
    {
        if(speciality != "" && workTimes.length()!=0)
        {
            doctor = Doctor::CreateDoctor(this, speciality, workTimes);
            if(doctor==nullptr) result = false;            
        }else result = false;
    }
    if(!result)
    {
        RemovePrivilegy(Privilegies::Doctor);
    }
}

void User::AddPrivilegyPatient()
{
    AddPrivilegy(Privilegies::Patient);
}

void User::RemovePrivilegy(Privilegies privilegy)
{
    if(privilegy == Privilegies::Doctor && doctor!=nullptr)
        helper->DeleteDoctor(doctor);
    privilegies &= ~(1 << privilegy);
}

bool User::IsPrivilegyExist(Privilegies pr)
{
    return (privilegies >> pr) & 1;
}

QString User::GetLogin() { return login;}
QString User::GetPassword(){ return password;}
QString User::GetSurname(){ return  surname;}
QString User::GetName(){return name;}
QString User::GetFatherName(){ return fatherName;}
QDate User::GetDateOfBirthd(){ return dateOfBirthd;}
QString User::GetAddress(){ return address;}
QString User::GetPhoneNumber(){ return phoneNumber;}
int User::GetPrivilegies(){return privilegies;}

void User::SetPassword(QString str){ password = str;}
void User::SetSurname(QString str){ surname = str;}
void User::SetName(QString str){name = str;}
void User::SetFatherName(QString str){ fatherName = str; }
void User::SetDateOfBirthd(QDate date){ dateOfBirthd = date; }
void User::SetAddress(QString str){ address = str; }


bool User::IsLogined()
{
    return isLogined;
}

bool User::Login()
{
    isLogined = LoadFromDB();
    return isLogined;
}

Doctor* User::GetDoctor()
{
    if(IsPrivilegyExist(Privilegies::Doctor))
        return doctor;
    else
        return nullptr;
}

bool User::SaveToDB()
{
    if(helper == nullptr) return false;

    helper->SaveUser(this);
    bool isSuccess = !helper->IsErrorExists();
    if(doctor != nullptr && !doctor->SaveToDB())
    {
        RemovePrivilegy(Privilegies::Doctor);
        //helper->GetError();
    }

    return isSuccess;
}

bool User::LoadFromDB()
{
    if(helper == nullptr) return false;

    QString additionCheck = " OR " + HospitalDatabaseHelper::ARG_USERS_CARD_ID+"='"+cardId+"'";
    if(!isCardConnected) additionCheck = "";
    QList<User> list = helper->GetUsers("("+HospitalDatabaseHelper::ARG_USERS_LOGIN+"='"+login+"' AND "+
                                   HospitalDatabaseHelper::ARG_USERS_PASSWORD+"='"+password+"')"+
                                   additionCheck);
    if(helper->IsErrorExists() || list.length() != 1) return false;

    User *user = &list[0];
    ConnectCard(user->GetCardId());
    login = user->GetLogin();
    password = user->GetPassword();
    name = user->GetName();
    surname = user->GetSurname();
    fatherName = user->GetFatherName();
    address = user->GetAddress();
    dateOfBirthd = user->GetDateOfBirthd();
    SetPhoneNumber(user->GetPhoneNumber());
    privilegies = user->GetPrivilegies();
    //delete user;
    if(IsPrivilegyExist(Privilegies::Doctor))
        AddPrivilegyDoctor();

    return !helper->IsErrorExists();
}

QString User::ToShortStr()
{
    return surname + " " + name.at(0) + ". " + fatherName.at(0) + ".";
}
