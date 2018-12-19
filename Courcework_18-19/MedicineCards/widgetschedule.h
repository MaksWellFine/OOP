#ifndef WIDGETSHADOW_H
#define WIDGETSHADOW_H

#include "doctor.h"
#include "serialcommunicationwithcard.h"

#include <QTableWidget>
#include <QWidget>

namespace Ui {
class WidgetSchedule;
}

class WidgetSchedule : public QWidget
{
    Q_OBJECT

public:
    static const QString RECORDS_INTERVAL;

    enum VisitStates { NotWork, Registered, NotRegistered, Accepted, NotAccepted};

    explicit WidgetSchedule(QWidget *parent = nullptr, SerialCommunicationWithCard* serial = nullptr);
    ~WidgetSchedule();

    void SetInfoForShow(Doctor* doctor, QDate* date);    

private:    

    static const QString START_WORK_DAY;
    static const QString END_WORK_DAY;    

    Ui::WidgetSchedule *ui;
    static WidgetSchedule* nowOperatingWidg;

    User* selectedPatient = nullptr;
    QTime* oldTimeSelected = new QTime(0,0,0);

    Doctor* doctorToShow = nullptr;
    QDate* dateToShow = nullptr;
    void RefreshSchedule();
    int GetRowWithTime(QTime time);

    void SetVisitStateForItem(QTableWidgetItem* item, VisitStates state);

    void OnPatientAccepting(User* patient);

public:
    VisitStates GetVisitStateForItem(QTableWidgetItem* item);
    QTime* GetSelectedTime();
    QTableWidgetItem* GetSelectedPersonItem();
    User* GetSelectedUser();

private slots:
    void OnTimer();

signals:
    void OnPatientSelect(bool state);
};

#endif // WIDGETSHADOW_H
