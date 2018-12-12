#ifndef WIDGETSPECIALTY_H
#define WIDGETSPECIALTY_H

#include "hospitaldatabasehelper.h"

#include <QWidget>

namespace Ui {
class WidgetSpecialty;
}

class WidgetSpecialty : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSpecialty(HospitalDatabaseHelper *helper, QWidget *parent = nullptr);
    ~WidgetSpecialty();

private:
    HospitalDatabaseHelper* helper;

    Ui::WidgetSpecialty *ui;

    void AddRow(QString specialty);

private slots:
    void RemoveClick();
    void AddClick();
};

#endif // WIDGETSPECIALTY_H
