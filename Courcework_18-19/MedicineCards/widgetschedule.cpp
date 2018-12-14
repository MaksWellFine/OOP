#include "widgetschedule.h"
#include "ui_widgetschedule.h"

const QString WidgetSchedule::START_WORK_DAY = "08:00";
const QString WidgetSchedule::END_WORK_DAY = "18:00";
const QString WidgetSchedule::RECORDS_INTERVAL = "00:30";

WidgetSchedule::WidgetSchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSchedule)
{
    ui->setupUi(this);

    ui->tableSchedule->verticalHeader()->setStretchLastSection(false);
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
    int rowsCount = ui->tableSchedule->rowCount();
    for(int i = 0 ; i < rowsCount; i++)
        ui->tableSchedule->removeRow(i);
    if(doctorToShow != nullptr && dateToShow != nullptr)
    {
        QTime timeToCreate = QTime::fromString(START_WORK_DAY, Doctor::TIME_FORMAT);
        while(timeToCreate < QTime::fromString(END_WORK_DAY, Doctor::TIME_FORMAT))
        {
            ui->tableSchedule->insertRow(ui->tableSchedule->rowCount());
            ui->tableSchedule->setItem(ui->tableSchedule->rowCount()-1, 0, new QTableWidgetItem(timeToCreate.toString(Doctor::TIME_FORMAT)));

            timeToCreate = timeToCreate.addSecs(QTime(0,0,0).secsTo(QTime::fromString(RECORDS_INTERVAL, Doctor::TIME_FORMAT)));
        }

        ui->lableTime->setText(dateToShow->toString(Doctor::DATE_FORMAT));
        QList<PatientRecord> records = doctorToShow->GetUser()->GetDatabase()->GetPatientRecords(doctorToShow);
        for(int i = 0; i < records.length(); i++)
        {
            QDateTime* dateTime = records[i].GetVisitDateTime();
            if(dateTime->date().toString(Doctor::DATE_FORMAT)==dateToShow->toString(Doctor::DATE_FORMAT))
            {
                int indx = GetRowWithTime(dateTime->time());
                if(indx!=-1 && records[i].GetVisitDuration()->toString(Doctor::TIME_FORMAT)==RECORDS_INTERVAL)
                {
                    QString userStr = records[i].GetUser()->GetSurname() + " " + records[i].GetUser()->GetName() + " " + records[i].GetUser()->GetFatherName();
                    ui->tableSchedule->setItem(indx, 1, new QTableWidgetItem(userStr));
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
