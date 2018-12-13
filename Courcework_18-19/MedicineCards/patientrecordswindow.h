#ifndef PATIENTRECORDSWINDOW_H
#define PATIENTRECORDSWINDOW_H

#include <QMainWindow>

namespace Ui {
class PatientRecordsWindow;
}

class PatientRecordsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PatientRecordsWindow(QWidget *parent = nullptr);
    ~PatientRecordsWindow();

private:
    Ui::PatientRecordsWindow *ui;
};

#endif // PATIENTRECORDSWINDOW_H
