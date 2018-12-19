#ifndef PATIENTRECORDSWINDOW_H
#define PATIENTRECORDSWINDOW_H

#include "user.h"

#include <QMainWindow>

namespace Ui {
class PatientRecordsWindow;
}

class PatientRecordsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PatientRecordsWindow(User* patient, QWidget *parent = nullptr);
    ~PatientRecordsWindow();

private:
    Ui::PatientRecordsWindow *ui;
    User* patient = nullptr;

    QList<PatientRecord> records;

    QString specialty = "";
    int selectedIndex = -1;
    PatientRecord* currentRecord = nullptr;

    void closeEvent(QCloseEvent *event) override;

    void LoadRecords();
    void LoadRecordInfo();

private slots:
    void OnTimer();
    void SaveRecord();

signals:
    void onClose();
};

#endif // PATIENTRECORDSWINDOW_H
