#ifndef WIDGETREGISTER_H
#define WIDGETREGISTER_H

#include "user.h"
#include "userinfo.h"
#include "widgetpatients.h"
#include "widgetschedule.h"

#include <QWidget>

namespace Ui {
class WidgetRegister;
}

class WidgetRegister : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetRegister(User* nowUser, UserInfo* infoWidg, QWidget *parent = nullptr);
    ~WidgetRegister();    

    void HardReload();

private:
    Ui::WidgetRegister *ui;        

    HospitalDatabaseHelper *helper;
    QTimer* reloadTimer;

    WidgetSchedule* schedWidg;
    WidgetPatients* patientWidg;

    QList<Doctor> doctors;

    QString choosedSpec = " ";
    QString choosedDoctorStr = " ";
    Doctor* choosedDoctor = nullptr;
    QDate* choosedDate = nullptr;

    bool needReload = false;

    void Error(QString text);

private slots:
    void ReloadAllData();
    void AddRecord();
    void RemoveRecord();
};

#endif // WIDGETREGISTER_H
