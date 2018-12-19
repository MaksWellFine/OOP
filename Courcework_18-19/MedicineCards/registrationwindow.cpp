#include "mainwindow.h"
#include "registrationwindow.h"
#include "ui_registrationwindow.h"

#include <QGraphicsPixmapItem>
#include <QMessageBox>

RegistrationWindow* RegistrationWindow::nowOperatingWin = nullptr;

RegistrationWindow::RegistrationWindow(SerialCommunicationWithCard* serial, QWidget *parent, User *creator, User *user) :
    QMainWindow(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);    

    ui->labUserImage->setPixmap(QPixmap::fromImage(*(new QImage(":/images/user.jpg"))).scaled(
                                    ui->labUserImage->width(), ui->labUserImage->height(), Qt::KeepAspectRatio));

    connect(ui->butMon, SIGNAL(released()), this, SLOT(ChooseDayClick()));
    connect(ui->butTue, SIGNAL(released()), this, SLOT(ChooseDayClick()));
    connect(ui->butWed, SIGNAL(released()), this, SLOT(ChooseDayClick()));
    connect(ui->butThu, SIGNAL(released()), this, SLOT(ChooseDayClick()));
    connect(ui->butFri, SIGNAL(released()), this, SLOT(ChooseDayClick()));
    connect(ui->butSat, SIGNAL(released()), this, SLOT(ChooseDayClick()));
    connect(ui->butSun, SIGNAL(released()), this, SLOT(ChooseDayClick()));
    daysStateBtns = {ui->butMon,ui->butTue,ui->butWed,ui->butThu,ui->butFri,ui->butSat,ui->butSun};

    connect(ui->checkBoxDoctor, SIGNAL(released()), this, SLOT(ChoosedDoctor()));

    connect(ui->butCancel, SIGNAL(released()), this, SLOT(CancelClick()));
    connect(ui->butSave, SIGNAL(released()), this, SLOT(SaveClick()));   

    this->serial = serial;

    nowOperatingWin = this;
    onCardConnected = [](QString cardId)-> void{
        nowOperatingWin->ui->editCardId->setText(cardId);
        nowOperatingWin->isCardConnected = true;
    };
    serial->AddCardAddListener(onCardConnected);


    if(creator==nullptr)
    {
        isAdmin = true;
        isCreateFirstUser = true;
        setWindowTitle("Реєстрація адміністратора");
        ui->checkBoxRecorder->setEnabled(true);
        ui->checkBoxPatient->setEnabled(true);
        ui->checkBoxDoctor->setEnabled(true);
    }else
    {        
        ui->comboBox->addItems(QStringList::fromStdList(
                                   creator->GetDatabase()->GetSpecialities("").toStdList()));
        if(creator->IsPrivilegyExist(User::Privilegies::Admin))
        {
            ui->checkBoxDoctor->setEnabled(true);
            ui->checkBoxRecorder->setEnabled(true);
            ui->checkBoxPatient->setEnabled(true);
        }else if(creator->IsPrivilegyExist(User::Privilegies::Recorder))
        {
            ui->checkBoxPatient->setEnabled(true);
            ui->checkBoxPatient->setChecked(true);
        }

        if(user!=nullptr)
        {            
            if(creator->IsPrivilegyExist(User::Privilegies::Admin) ||
                    (creator->IsPrivilegyExist(User::Privilegies::Recorder) && !user->IsPrivilegyExist(User::Privilegies::Admin)
                        && !user->IsPrivilegyExist(User::Privilegies::Doctor) && !user->IsPrivilegyExist(User::Privilegies::Recorder)) ||
                    creator->GetLogin() == user->GetLogin())
            {
                setWindowTitle("Редагування користувача");                
                LoadFromUser(user);
                userToSave = user;
            }else
            {
                QMessageBox msg;
                msg.setWindowTitle("Помилка редагування!");
                msg.setText("У вас не достатньо прав доступу для редагування даного користувача!");
                msg.exec();
                QTimer::singleShot(0, this, SLOT(close()));
            }
        }
    }
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::ChooseDayClick()
{
    QAbstractButton* but = static_cast<QAbstractButton *>(sender());    
    int index = but->maximumHeight()/1000-1;
    daysState[index] = !daysState[index];
    RefreshDaysStates();
}

void RegistrationWindow::RefreshDaysStates()
{
    for(int i = 0; i < 7; i++)
    {
        QPalette pal = daysStateBtns[i]->palette();
        if(daysState[i])
            pal.setColor(QPalette::Button, QColor(Qt::lightGray));
        else
            pal.setColor(QPalette::Button, QColor(Qt::transparent));
        daysStateBtns[i]->setPalette(pal);
        daysStateBtns[i]->update();
    }
}

void RegistrationWindow::ChoosedDoctor()
{
    ui->widgetDoctor->setEnabled(ui->checkBoxDoctor->isChecked());
}

void RegistrationWindow::LoadFromUser(User *user)
{
    ui->editLogin->setText(user->GetLogin());
    ui->editLogin->setReadOnly(true);
    ui->editPassword->setText(user->GetPassword());
    ui->editSurname->setText(user->GetSurname());
    ui->editName->setText(user->GetName());
    ui->editFatherName->setText(user->GetFatherName());
    ui->editAddress->setText(user->GetAddress());
    ui->editDateOfBirthd->setDate(user->GetDateOfBirthd());
    ui->editPhoneNumber->setText(user->GetPhoneNumber());
    if(user->IsCardConnected())
    {
        isCardConnected = true;
        ui->editCardId->setText(user->GetCardId());
    }
    if(user->IsPrivilegyExist(User::Privilegies::Admin))
    {
        isAdmin = true;
    }

    if(user->IsPrivilegyExist(User::Privilegies::Doctor))
    {
        ui->checkBoxDoctor->setChecked(true);
        ui->checkBoxDoctor->setEnabled(false);
        ui->widgetDoctor->setEnabled(true);
        if(user->GetDoctor()!=nullptr)
        {
            ui->comboBox->setCurrentText(user->GetDoctor()->GetSpeciality());
            QList<WorkTime> workTimes = user->GetDoctor()->GetWorkTimes();
            if(workTimes.length() > 0)
            {
                ui->editCabinet->setText(workTimes[0].cabinet);
                ui->editTimeStartWork->setTime(workTimes[0].workTime.first);
                ui->editTimeEndWork->setTime(workTimes[0].workTime.second);
            }
            for(int i = 0; i < workTimes.length(); i++)
                daysState[workTimes[i].workDay] = true;
            RefreshDaysStates();
        }
    }
    if(user->IsPrivilegyExist(User::Privilegies::Recorder))
    {
        ui->checkBoxRecorder->setChecked(true);
        ui->checkBoxRecorder->setEnabled(false);
    }
    if(user->IsPrivilegyExist(User::Privilegies::Patient))
    {
        ui->checkBoxPatient->setChecked(true);
        ui->checkBoxPatient->setEnabled(false);
    }
}

void RegistrationWindow::LoadToUser(User **user)
{
    if(*user==nullptr)
    {
        *user = new User(ui->editLogin->text(), ui->editPassword->text(), ui->editSurname->text(), ui->editName->text(),
                        ui->editFatherName->text(), ui->editDateOfBirthd->date(),
                        ui->editAddress->text(), ui->editPhoneNumber->text());        
    }else
    {
        (*user)->SetPassword(ui->editPassword->text());
        (*user)->SetSurname(ui->editSurname->text());
        (*user)->SetName(ui->editName->text());
        (*user)->SetFatherName(ui->editFatherName->text());
        (*user)->SetAddress(ui->editAddress->text());
        (*user)->SetPhoneNumber(ui->editPhoneNumber->text());
        (*user)->SetDateOfBirthd(ui->editDateOfBirthd->date());
    }
    if(isCardConnected)
    {
        if(oldCardId == "") oldCardId = (*user)->GetCardId();
        (*user)->ConnectCard(ui->editCardId->text(), true);
    }
    if(ui->checkBoxRecorder->isChecked())
        (*user)->AddPrivilegyRecorder();
    else
        (*user)->RemovePrivilegy(User::Privilegies::Recorder);
    if(ui->checkBoxDoctor->isChecked())
    {
        QString cabinet = ui->editCabinet->text();
        QPair<QTime, QTime> time(ui->editTimeStartWork->time(), ui->editTimeEndWork->time());
        QList<WorkTime> workTimes;
        for(int i = 0; i < 7; i++)
            if(daysState[i]) workTimes.append(WorkTime(cabinet, time, (WorkTime::Day)i));
        (*user)->AddPrivilegyDoctor(ui->comboBox->currentText(), workTimes);
    }
    else
        (*user)->RemovePrivilegy(User::Privilegies::Doctor);
    if(ui->checkBoxPatient->isChecked())
        (*user)->AddPrivilegyPatient();
    else
        (*user)->RemovePrivilegy(User::Privilegies::Patient);

    if(isAdmin) (*user)->AddPrivilegyAdmin();

    //user->Login();
}

void RegistrationWindow::SaveClick()
{
    QMessageBox msg;
    msg.setWindowTitle("Результат збереження");

    if(!IsUserInfoCorrect())    
        return;    

    LoadToUser(&userToSave);   

    if(isCardConnected != userToSave->IsCardConnected())
    {
        if(oldCardId != User::DEFAULT_CARD_ID_VAL)
        {
            userToSave->ConnectCard(oldCardId);
            ui->editCardId->setText(oldCardId);
        }else
            ui->editCardId->setText("Прикладіть картку");

        msg.setText("Дана картка уже викорстовується!");
        msg.exec();
        return;
    }
    if(ui->checkBoxDoctor->isChecked() && userToSave->GetDoctor()==nullptr)
    {
        msg.setText("Помилка при додаванні привілегії лікаря!");
        msg.exec();
        return;
    }
    if(userToSave->SaveToDB())
    {
        if(!isCreateFirstUser || userToSave->Login())
        {
            if(ui->checkBoxDoctor->isChecked() && userToSave->GetDoctor()==nullptr)
            {
                msg.setText("Кориcтувача збережено, проте не вдалось додати налаштування лікаря!");
                msg.exec();
            }else
            {
                msg.setText("Кориcтувача успішно збережено!");
                msg.exec();
                if(isCreateFirstUser) StartMainWindow();
                emit onSaved();
                CancelClick();
            }
        }else
        {
            msg.setText("Кориcтувача успішно збережено, проте не вдалось увійти в систему, спробуйте ще раз!");
            msg.exec();
        }
    }else
    {
        msg.setText("Помилка збереження! Можливо користувач з таким логіном або карткою уже існує!");
        msg.exec();
    }
}

void RegistrationWindow::CancelClick()
{
    serial->RemoveCardAddListener(onCardConnected);
    close();
}

void RegistrationWindow::StartMainWindow()
{
    MainWindow *wind = new MainWindow(serial, userToSave);
    wind->show();
}

bool RegistrationWindow::IsUserInfoCorrect()
{
    bool isError = false;

    if(!ui->checkBoxPatient->isChecked() && !ui->checkBoxRecorder->isChecked() && !ui->checkBoxDoctor->isChecked()
            && !isAdmin)
    {
        QMessageBox msg;
        msg.setWindowTitle("Результат збереження");
        msg.setText("Виберіть хоча б одну привілегію користувача(пацієнт, реєстратор, лікар)!");
        msg.exec();
        isError = true;
    }

    if(ui->editLogin->text().length() < 8)
    {
        SetEditTextErrorState(ui->editLogin);
        isError = true;
    }else
        SetEditTextErrorState(ui->editLogin, false);

    if(ui->editPassword->text().length() < 8)
    {
        SetEditTextErrorState(ui->editPassword);
        isError = true;
    }else
        SetEditTextErrorState(ui->editPassword, false);

    if(ui->editSurname->text().isEmpty())
    {
        SetEditTextErrorState(ui->editSurname);
        isError = true;
    }else
        SetEditTextErrorState(ui->editSurname, false);

    if(ui->editName->text().isEmpty())
    {
        SetEditTextErrorState(ui->editName);
        isError = true;
    }else
        SetEditTextErrorState(ui->editName, false);

    if(ui->editFatherName->text().isEmpty())
    {
        SetEditTextErrorState(ui->editFatherName);
        isError = true;
    }else
        SetEditTextErrorState(ui->editFatherName, false);

    if(ui->editPhoneNumber->text().isEmpty())
    {
        SetEditTextErrorState(ui->editPhoneNumber);
        isError = true;
    }else
        SetEditTextErrorState(ui->editPhoneNumber, false);

    if(ui->checkBoxPatient->isChecked() && !isCardConnected)
    {
        SetEditTextErrorState(ui->editCardId);
        isError = true;
    }else
        SetEditTextErrorState(ui->editCardId, false);

    if(ui->checkBoxDoctor->isChecked())
    {
        if(ui->comboBox->currentText().isEmpty())
        {
            QMessageBox msg;
            msg.setWindowTitle("Результат збереження");
            msg.setText("Виберіть спеціальність лікаря!");
            msg.exec();
            isError = true;
        }

        if(ui->editTimeStartWork->text().isEmpty())
        {
            SetEditTextErrorState(ui->editTimeStartWork);
            isError = true;
        }else
            SetEditTextErrorState(ui->editTimeStartWork, false);

        if(ui->editTimeEndWork->text().isEmpty())
        {
            SetEditTextErrorState(ui->editTimeEndWork);
            isError = true;
        }else
            SetEditTextErrorState(ui->editTimeEndWork, false);

        if(ui->editCabinet->text().isEmpty())
        {
            SetEditTextErrorState(ui->editCabinet);
            isError = true;
        }else
            SetEditTextErrorState(ui->editCabinet, false);

        bool isDayChoosed = false;
        for(int i = 0; i < 7; i++) if(daysState[i]) isDayChoosed = true;
        if(!isDayChoosed && !isError)
        {
            QMessageBox msg;
            msg.setWindowTitle("Результат збереження");
            msg.setText("Виберіть день/дні роботи лікаря!");
            msg.exec();
            isError = true;
        }
    }


    return !isError;
}

void RegistrationWindow::SetEditTextErrorState(QWidget* widget, bool isError)
{
    QPalette pal = widget->palette();
    if(isError)
        pal.setColor(QPalette::Base, QColor(Qt::red));
    else
        pal.setColor(QPalette::Base, QColor(Qt::transparent));
    widget->setPalette(pal);
    widget->update();
}

void RegistrationWindow::closeEvent(QCloseEvent *event)
{
    emit onClose();
    QWidget::closeEvent(event);
}
