#ifndef WIDGETSHADOW_H
#define WIDGETSHADOW_H

#include "doctor.h"

#include <QWidget>

namespace Ui {
class WidgetSchedule;
}

class WidgetSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSchedule(QWidget *parent = nullptr);
    ~WidgetSchedule();

    void SetInfoForShow(Doctor* doctor, QDate* date);

private:
    static const QString START_WORK_DAY;
    static const QString END_WORK_DAY;
    static const QString RECORDS_INTERVAL;

    Ui::WidgetSchedule *ui;

    Doctor* doctorToShow;
    QDate* dateToShow;
    void RefreshSchedule();
    int GetRowWithTime(QTime time);
};

#endif // WIDGETSHADOW_H
