#include "mainwindow.h"
#include "patientrecordswindow.h"
#include "ui_mainwindow.h"
#include "userinfo.h"
#include "widgetpatients.h"
#include "widgetregister.h"
#include "widgetschedule.h"
#include "widgetspecialty.h"

#include <QMessageBox>

MainWindow::MainWindow(SerialCommunicationWithCard* serial, User* user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainUser = user;
    this->serial = serial;

    connect(ui->listWidgets, &QTabWidget::currentChanged, this, &MainWindow::TabChanged);

    userInfoWidg = new UserInfo(user, this);
    ui->widgetUserInfo->layout()->addWidget(userInfoWidg);

    if(user->IsPrivilegyExist(User::Privilegies::Doctor))
    {
        schedWidg = new WidgetSchedule(this, serial);
        ui->listWidgets->addTab(schedWidg, "Розклад");
        connect(schedWidg, &WidgetSchedule::OnPatientSelect, userInfoWidg, &UserInfo::EditingState);
        connect(userInfoWidg, &UserInfo::ShowEditRecordWindow, this, &MainWindow::ShowEditRecordsWindow);
    }

    if(user->IsPrivilegyExist(User::Privilegies::Admin))
    {
        patientWidg = new WidgetPatients(serial, user, userInfoWidg, this);
        ui->listWidgets->addTab(patientWidg, "Користувачі");
    }

    if(user->IsPrivilegyExist(User::Privilegies::Recorder))
    {
        if(!user->IsPrivilegyExist(User::Privilegies::Admin))
        {
            patientWidg = new WidgetPatients(serial, user, userInfoWidg, this);
            ui->listWidgets->addTab(patientWidg, "Пацієнти");
        }
        registWidg = new WidgetRegister(user, userInfoWidg, this);
        ui->listWidgets->addTab(registWidg, "Журнал");
    }

    if(user->IsPrivilegyExist(User::Privilegies::Admin))
        ui->listWidgets->addTab(new WidgetSpecialty(mainUser->GetDatabase(), this), "Спеціальності");

    QTimer* reloadTimer = new QTimer(this);
    reloadTimer->setInterval(30000);
    QObject::connect(reloadTimer, SIGNAL(timeout()), this, SLOT(OnTimer()));
    reloadTimer->start();
}

MainWindow::~MainWindow()
{    
    delete ui;
}

void MainWindow::TabChanged()
{    
    userInfoWidg->ShowUserInfo(mainUser, true);
    if(schedWidg != nullptr)
    {
        if(ui->listWidgets->tabText(ui->listWidgets->currentIndex()) == "Розклад")
        {
            schedWidg->SetInfoForShow(mainUser->GetDoctor(), new QDate(QDate::currentDate()));
            schedWidg->SetShowState(true);
        }else
            schedWidg->SetShowState(false);
    }

    if(registWidg != nullptr && ui->listWidgets->tabText(ui->listWidgets->currentIndex()) == "Журнал")
        registWidg->HardReload();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    serial->Disconnect();
    if(patientWidg != nullptr)
        patientWidg->CloseRegistrationWindow();
    if(recordsEditWin != nullptr)
        recordsEditWin->close();
    QWidget::closeEvent(event);
}

void MainWindow::OnTimer()
{
    if(schedWidg != nullptr && ui->listWidgets->tabText(ui->listWidgets->currentIndex()) == "Розклад")
        schedWidg->SetInfoForShow(mainUser->GetDoctor(), new QDate(QDate::currentDate()));
}

void MainWindow::ShowEditRecordsWindow()
{
    if(schedWidg != nullptr && schedWidg->GetSelectedUser()!=nullptr)
    {
        if(!isRecordsEditWinShow)
        {
            isRecordsEditWinShow = true;
            recordsEditWin = new PatientRecordsWindow(schedWidg->GetSelectedUser());
            connect(recordsEditWin, &PatientRecordsWindow::onClose, this, &MainWindow::OnClosedEditRecordsWindow);
            recordsEditWin->show();
        }else
        {
            QMessageBox msg;
            msg.setWindowTitle("Попередження");
            msg.setText("Історія іншого пацієнта уже відкрита!");
            msg.exec();
        }
    }
}

void MainWindow::OnClosedEditRecordsWindow()
{
    isRecordsEditWinShow = false;
    if(recordsEditWin != nullptr)
        disconnect(recordsEditWin, &PatientRecordsWindow::onClose, this, &MainWindow::OnClosedEditRecordsWindow);
}
