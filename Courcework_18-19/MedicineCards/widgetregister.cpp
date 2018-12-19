#include "widgetregister.h"
#include "ui_widgetregister.h"
#include "widgetpatients.h"
#include "widgetschedule.h"

#include <QMessageBox>

WidgetRegister::WidgetRegister(User* nowUser, UserInfo* infoWidg, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetRegister)
{
    ui->setupUi(this);    

    helper = nowUser->GetDatabase();

    QLayout *lay1 = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    patientWidg = new WidgetPatients(nowUser, infoWidg, this);
    lay1->addWidget(patientWidg);
    ui->widgPatients->setLayout(lay1);

    QLayout *lay2 = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    schedWidg = new WidgetSchedule(this);
    lay2->addWidget(schedWidg);
    ui->widgSchedule->setLayout(lay2);

    reloadTimer = new QTimer(this);
    reloadTimer->setInterval(200);
    QObject::connect(reloadTimer, SIGNAL(timeout()), this, SLOT(ReloadAllData()));
    reloadTimer->start();

    ui->dateEdit->setDate(QDate::currentDate());

    connect(ui->btnAdd, &QPushButton::pressed, this, &WidgetRegister::AddRecord);
    connect(ui->btnRemove, &QPushButton::pressed, this, &WidgetRegister::RemoveRecord);
}

WidgetRegister::~WidgetRegister()
{ 
    delete ui;
}

void WidgetRegister::ReloadAllData()
{
    if(choosedSpec == ui->comboBoxSpecialties->currentText() && choosedDoctorStr == ui->comboBoxDoctors->currentText() &&
            *choosedDate == ui->dateEdit->date() && !needReload)
        return;

    needReload = false;

    QList<QString> specs = helper->GetSpecialities("");
    choosedSpec = ui->comboBoxSpecialties->currentText();
    ui->comboBoxSpecialties->clear();
    ui->comboBoxSpecialties->addItems(QStringList::fromSet(specs.toSet()));
    ui->comboBoxSpecialties->setCurrentText(choosedSpec);

    doctors = helper->GetDoctors(HospitalDatabaseHelper::ARG_DOCTORS_SPECIALITY_ID+"='"+
                                 QString::number(helper->GetSpecialityId(ui->comboBoxSpecialties->currentText()))+"'");
    choosedDoctorStr = ui->comboBoxDoctors->currentText();
    choosedDoctor = nullptr;
    ui->comboBoxDoctors->clear();
    for(int i = 0; i < doctors.length(); i++)
    {
        ui->comboBoxDoctors->addItem(doctors[i].GetUser()->ToShortStr());
        if(choosedDoctorStr == doctors[i].GetUser()->ToShortStr())
            choosedDoctor = &doctors[i];
    }
    ui->comboBoxDoctors->setCurrentText(choosedDoctorStr);

    choosedDate = new QDate(ui->dateEdit->date());

    schedWidg->SetInfoForShow(choosedDoctor, choosedDate);

    patientWidg->LoadUsers();
}

void WidgetRegister::HardReload()
{
    needReload = true;
}

void WidgetRegister::Error(QString text)
{
    QMessageBox msg;
    msg.setWindowTitle("Помилка при додаванні запису");
    msg.setText(text);
    msg.exec();
}

void WidgetRegister::AddRecord()
{
    if(choosedDoctor == nullptr)
    {
        Error("Виберіть лікаря!");
        return;
    }

    if(choosedDate == nullptr)
    {
        Error("Виберіть дату!");
        return;
    }

    QTime* time = schedWidg->GetSelectedTime();
    if(time == nullptr)
    {
        Error("Виберіть час!");
        return;
    }else if(QDateTime(*choosedDate, *time).addSecs(QTime(0,0,0).secsTo(QTime::fromString(
            WidgetSchedule::RECORDS_INTERVAL, Doctor::TIME_FORMAT))) < QDateTime::currentDateTime())
    {
        Error("Не можливо записувати пацієнтів у минуле =]");
        return;
    }

    WidgetSchedule::VisitStates state = schedWidg->GetVisitStateForItem(schedWidg->GetSelectedPersonItem());
    if(state == WidgetSchedule::VisitStates::NotWork)
    {
        Error("Лікар не працює в цей час!");
        return;
    }else if(state == WidgetSchedule::VisitStates::Accepted || state == WidgetSchedule::VisitStates::NotAccepted ||
             state == WidgetSchedule::VisitStates::Registered)
    {
        Error("На цей час записаний інший пацієнт!");
        return;
    }

    User* user = patientWidg->GetChoosedItem();
    if(user == nullptr)
    {
        Error("Виберіть пацієнта!");
        return;
    }

    helper->SavePatientRecord(new PatientRecord(user, choosedDoctor, new QDateTime(QDateTime(*choosedDate, *time)),
                                                new QTime(QTime::fromString(WidgetSchedule::RECORDS_INTERVAL)), new QString(), false));

    HardReload();
}

void WidgetRegister::RemoveRecord()
{
    if(choosedDoctor == nullptr)
    {
        Error("Виберіть лікаря!");
        return;
    }

    if(choosedDate == nullptr)
    {
        Error("Виберіть дату!");
        return;
    }

    QTime* time = schedWidg->GetSelectedTime();
    if(time == nullptr)
    {
        Error("Виберіть час!");
        return;
    }else if(QDateTime(*choosedDate, *time).addSecs(QTime(0,0,0).secsTo(QTime::fromString(
            WidgetSchedule::RECORDS_INTERVAL, Doctor::TIME_FORMAT))) < QDateTime::currentDateTime())
    {
        Error("Не можливо видаляти прийом пацієнтів у минулому!");
        return;
    }

    WidgetSchedule::VisitStates state = schedWidg->GetVisitStateForItem(schedWidg->GetSelectedPersonItem());
    if(state == WidgetSchedule::VisitStates::NotWork)
    {
        Error("Лікар не працює в цей час!");
        return;
    }else if(state != WidgetSchedule::VisitStates::Registered)
    {
        Error("На цей час не можливо видалити запис на прийом!");
        return;
    }

    QList<PatientRecord> records = helper->GetPatientRecords(choosedDoctor);
    PatientRecord* rec = nullptr;
    for(int i = 0; i < records.length(); i++)
    {
        if(*records[i].GetVisitDateTime() == QDateTime(*choosedDate, *time))
        {
            rec = &records[i];
            break;
        }
    }
    if(rec == nullptr)
    {
        Error("Не можливо видалити цей запис на прийом до лікаря!");
        return;
    }
    helper->DeletePatientRecord(rec);
    HardReload();
}
