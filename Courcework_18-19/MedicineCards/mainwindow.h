#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "patientrecordswindow.h"
#include "serialcommunicationwithcard.h"
#include "user.h"
#include "userinfo.h"
#include "widgetpatients.h"
#include "widgetregister.h"
#include "widgetschedule.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(SerialCommunicationWithCard* serial, User* user, QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void closeEvent(QCloseEvent *event) override;

    Ui::MainWindow *ui;

    SerialCommunicationWithCard* serial;
    User* mainUser;

    UserInfo *userInfoWidg = nullptr;

    PatientRecordsWindow *recordsEditWin = nullptr;
    bool isRecordsEditWinShow = false;

    WidgetSchedule* schedWidg = nullptr;
    WidgetPatients* patientWidg = nullptr;
    WidgetRegister* registWidg = nullptr;

private slots:
    void TabChanged();
    void OnTimer();
    void ShowEditRecordsWindow();
    void OnClosedEditRecordsWindow();
};

#endif // MAINWINDOW_H
