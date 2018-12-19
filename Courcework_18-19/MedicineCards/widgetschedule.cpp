#include "widgetschedule.h"
#include "ui_widgetschedule.h"

#include <QMessageBox>

const QString WidgetSchedule::START_WORK_DAY = "08:00";
const QString WidgetSchedule::END_WORK_DAY = "18:00";
const QString WidgetSchedule::RECORDS_INTERVAL = "00:30";

WidgetSchedule* WidgetSchedule::nowOperatingWidg = nullptr;

WidgetSchedule::WidgetSchedule(QWidget *parent, SerialCommunicationWithCard* serial) :
    QWidget(parent),
    ui(new Ui::WidgetSchedule)
{
    ui->setupUi(this);

    ui->tableSchedule->verticalHeader()->setStretchLastSection(false);

    nowOperatingWidg = this;
    if(serial != nullptr)
    {
        serial->AddCardAddListener([](QString cardId)->void{
            User* user = new User(cardId);
            nowOperatingWidg->OnPatientAccepting(user);
        });

        QTimer* timer = new QTimer(this);
        timer->setInterval(200);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
        timer->start();
    }
}

WidgetSchedule::~WidgetSchedule()
{
    delete ui;
}

void WidgetSchedule::SetInfoForShow(Doctor* doctor, QDate* date)
{
    if(doctor != nullptr && date != nullptr)
    {
        doctorToShow = doctor;
        dateToShow = date;
        RefreshSchedule();
    }
}

void WidgetSchedule::RefreshSchedule()
{    
    ui->tableSchedule->setRowCount(0);

    if(doctorToShow != nullptr && dateToShow != nullptr)
    {
        QList<WorkTime> workTimes = doctorToShow->GetWorkTimes();

        QTime timeToCreate = QTime::fromString(START_WORK_DAY, Doctor::TIME_FORMAT);
        QTime intervalTime = QTime::fromString(RECORDS_INTERVAL, Doctor::TIME_FORMAT);
        while(timeToCreate < QTime::fromString(END_WORK_DAY, Doctor::TIME_FORMAT))
        {
            ui->tableSchedule->insertRow(ui->tableSchedule->rowCount());
            ui->tableSchedule->setItem(ui->tableSchedule->rowCount()-1, 0, new QTableWidgetItem(timeToCreate.toString(Doctor::TIME_FORMAT)));
            ui->tableSchedule->setItem(ui->tableSchedule->rowCount()-1, 1, new QTableWidgetItem(""));

            bool isWork = false;
            for(int i = 0; i < workTimes.length(); i++)
                if(workTimes[i].workDay == dateToShow->dayOfWeek()-1)
                {
                    if(timeToCreate >= workTimes[i].workTime.first &&
                            timeToCreate.addSecs(QTime(0,0,0).secsTo(intervalTime)) <= workTimes[i].workTime.second)
                    {
                        isWork = true;
                        break;
                    }
                }

            if(!isWork)
                SetVisitStateForItem(ui->tableSchedule->item(ui->tableSchedule->rowCount()-1, 1), VisitStates::NotWork);
            else
                SetVisitStateForItem(ui->tableSchedule->item(ui->tableSchedule->rowCount()-1, 1), VisitStates::NotRegistered);

            timeToCreate = timeToCreate.addSecs(QTime(0,0,0).secsTo(intervalTime));
        }

        ui->lableTime->setText(dateToShow->toString(Doctor::DATE_FORMAT));
        QList<PatientRecord> records = doctorToShow->GetUser()->GetDatabase()->GetPatientRecords(doctorToShow);
        for(int i = 0; i < records.length(); i++)
        {
            QDateTime* dateTime = records[i].GetVisitDateTime();
            if(dateTime->date() == *dateToShow)
            {
                int indx = GetRowWithTime(dateTime->time());
                if(indx!=-1 && records[i].GetVisitDuration()->toString(Doctor::TIME_FORMAT)==RECORDS_INTERVAL)
                {
                    QString userStr = records[i].GetUser()->GetSurname() + " " + records[i].GetUser()->GetName() + " " + records[i].GetUser()->GetFatherName();
                    QTableWidgetItem* item = ui->tableSchedule->item(indx, 1);
                    item->setText(userStr);
                    if(records[i].IsVisited())
                        SetVisitStateForItem(item, VisitStates::Accepted);
                    else
                        if(QDateTime::currentDateTime() > records[i].GetVisitDateTime()->addSecs(QTime(0,0,0).secsTo(*records[i].GetVisitDuration())))
                            SetVisitStateForItem(item, VisitStates::NotAccepted);
                        else
                            SetVisitStateForItem(item, VisitStates::Registered);
                }
            }
        }
    }
}

int WidgetSchedule::GetRowWithTime(QTime time)
{
    QString timeStr = time.toString(Doctor::TIME_FORMAT);
    for(int i = 0; i < ui->tableSchedule->rowCount(); i++)
    {
        if(ui->tableSchedule->item(i, 0)->text() == timeStr)
            return i;
    }
    return -1;
}

void WidgetSchedule::SetVisitStateForItem(QTableWidgetItem* item, VisitStates state)
{
    switch (state) {
        case VisitStates::NotWork:
            item->setBackgroundColor(QColor(Qt::GlobalColor::blue));
        break;
        case VisitStates::Registered:
            item->setBackgroundColor(QColor(Qt::GlobalColor::yellow));
        break;
        case VisitStates::NotRegistered:
            item->setBackgroundColor(QColor(Qt::GlobalColor::transparent));
        break;
        case VisitStates::Accepted:
            item->setBackgroundColor(QColor(Qt::GlobalColor::green));
        break;
        case VisitStates::NotAccepted:
            item->setBackgroundColor(QColor(Qt::GlobalColor::red));
        break;
    }
}

WidgetSchedule::VisitStates WidgetSchedule::GetVisitStateForItem(QTableWidgetItem* item)
{
    QColor backColor = item->backgroundColor();
    if(backColor == QColor(Qt::GlobalColor::blue))
        return VisitStates::NotWork;
    else if(backColor == QColor(Qt::GlobalColor::yellow))
        return VisitStates::Registered;
    else if(backColor == QColor(Qt::GlobalColor::green))
        return VisitStates::Accepted;
    else if(backColor == QColor(Qt::GlobalColor::red))
        return VisitStates::NotAccepted;
    else
        return VisitStates::NotRegistered;
}

QTableWidgetItem* WidgetSchedule::GetSelectedPersonItem()
{
    if(ui->tableSchedule->selectedItems().length() > 1)
        return ui->tableSchedule->selectedItems()[1];
    else
        return nullptr;
}

QTime* WidgetSchedule::GetSelectedTime()
{
    if(ui->tableSchedule->selectedItems().length() > 1)
        return new QTime(QTime::fromString(ui->tableSchedule->selectedItems()[0]->text(), Doctor::TIME_FORMAT));
    else
        return nullptr;
}

void WidgetSchedule::OnPatientAccepting(User* patient)
{
    if(!patient->IsPrivilegyExist(User::Privilegies::Patient))
    {
        QMessageBox msg;
        msg.setWindowTitle("Помилка");
        msg.setText("Користувач не є пацієнтом!");
        msg.exec();
    }

    if(doctorToShow == nullptr)
    {
        QMessageBox msg;
        msg.setWindowTitle("Помилка");
        msg.setText("Не відомий лікар!");
        msg.exec();
    }
    QList<PatientRecord> records = patient->GetDatabase()->GetPatientRecords(doctorToShow);
    bool isRecordExist = false;
    bool isBadTime = false;
    for(int i = 0; i < records.length(); i++)
    {
        if(records[i].GetUser()->GetLogin() == patient->GetLogin())
        {
            isRecordExist = true;
            if(QDateTime::currentDateTime() >= *records[i].GetVisitDateTime() &&
                     QDateTime::currentDateTime() <= records[i].GetVisitDateTime()->addSecs(QTime(0,0,0).secsTo(*records[i].GetVisitDuration())))
            {
                isBadTime = false;
                records[i].SetVisited();
                records[i].SaveToDB();
                int row = GetRowWithTime(records[i].GetVisitDateTime()->time());
                if(row != -1)
                    SetVisitStateForItem(ui->tableSchedule->item(row, 1), VisitStates::Accepted);
                break;
            }else
                isBadTime = true;
        }
    }
    if(!isRecordExist)
    {
        QMessageBox msg;
        msg.setWindowTitle("Помилка");
        msg.setText("Пацієнт не записаний до даного лікаря!");
        msg.exec();
    }else if(isBadTime)
    {
        QMessageBox msg;
        msg.setWindowTitle("Помилка");
        msg.setText("Пацієнт прийшов не у свій час!");
        msg.exec();
    }
    RefreshSchedule();
}

void WidgetSchedule::OnTimer()
{
    QTime* time = GetSelectedTime();
    if(time != nullptr)
    {
        if(*oldTimeSelected!=*time)
        {
            *oldTimeSelected = *time;
            int row = GetRowWithTime(*time);
            if(row <= 0) return;
            if(GetVisitStateForItem(ui->tableSchedule->item(row, 1)) == VisitStates::Accepted)
            {
                QList<PatientRecord> records = doctorToShow->GetUser()->GetDatabase()->GetPatientRecords(doctorToShow);
                for(int i = 0; i < records.length(); i++)
                {
                    if(*records[i].GetVisitDateTime() == QDateTime(*dateToShow, *time))
                    {
                        selectedPatient = new User(records[i].GetUser());
                        emit OnPatientSelect(true);
                        return;
                    }
                }
            }
        }else return;
    }else oldTimeSelected = new QTime(0,0,0);
    selectedPatient = nullptr;
    emit OnPatientSelect(false);
}

User* WidgetSchedule::GetSelectedUser()
{
    return selectedPatient;
}
