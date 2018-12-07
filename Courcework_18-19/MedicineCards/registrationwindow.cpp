#include "registrationwindow.h"
#include "ui_registrationwindow.h"

#include <QGraphicsPixmapItem>
#include <QMessageBox>

RegistrationWindow::RegistrationWindow(QWidget *parent, User *creator, User *user) :
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

    connect(ui->checkBoxDoctor, SIGNAL(released()), this, SLOT(ChoosedDoctor()));

    connect(ui->butCancel, SIGNAL(released()), this, SLOT(CancelClick()));
    connect(ui->butSave, SIGNAL(released()), this, SLOT(SaveClick()));

    if(creator==nullptr)
    {
        isAdmin = true;
        setWindowTitle("Реєстрація адміністратора");
        ui->checkBoxRecorder->setEnabled(true);
        ui->checkBoxPatient->setEnabled(true);
        ui->checkBoxDoctor->setEnabled(true);
    }else
    {
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
    QPalette pal = but->palette();
    int index = but->maximumHeight()/1000-1;
    daysState[index] = !daysState[index];
    if(daysState[index])
        pal.setColor(QPalette::Button, QColor(Qt::lightGray));
    else
        pal.setColor(QPalette::Button, QColor(Qt::transparent));
    but->setPalette(pal);
    but->update();
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
    if(user->IsCardConnected()) ui->editCardId->setText(user->GetCardId());

    if(user->IsPrivilegyExist(User::Privilegies::Doctor))
    {
        ui->checkBoxDoctor->setChecked(true);
        ui->checkBoxDoctor->setEnabled(false);
        ui->widgetDoctor->setEnabled(true);
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

void RegistrationWindow::LoadToUser(User *user)
{
    if(user==nullptr)
    {
        user = new User(ui->editLogin->text(), ui->editPassword->text(), ui->editSurname->text(), ui->editName->text(),
                        ui->editFatherName->text(), QDate::fromString(ui->editDateOfBirthd->text(), User::DATE_OF_BIRTHD_FORMAT),
                        ui->editAddress->text(), ui->editPhoneNumber->text());
        if(isCardConnected) user->ConnectCard(ui->editCardId->text(), true);

    }else
    {
        user->SetPassword(ui->editPassword->text());
        user->SetSurname(ui->editSurname->text());
        user->SetName(ui->editName->text());
        user->SetFatherName(ui->editFatherName->text());
        user->SetAddress(ui->editAddress->text());
        user->SetPhoneNumber(ui->editPhoneNumber->text());
        user->SetDateOfBirthd(QDate::fromString(ui->editDateOfBirthd->text(), User::DATE_OF_BIRTHD_FORMAT));
    }
    if(ui->checkBoxRecorder->isChecked())
        user->AddPrivilegy(User::Privilegies::Recorder);
    else
        user->RemovePrivilegy(User::Privilegies::Recorder);
    if(ui->checkBoxDoctor->isChecked())
        user->AddPrivilegy(User::Privilegies::Doctor);
    else
        user->RemovePrivilegy(User::Privilegies::Doctor);
    if(ui->checkBoxPatient->isChecked())
        user->AddPrivilegy(User::Privilegies::Patient);
    else
        user->RemovePrivilegy(User::Privilegies::Patient);

    if(isAdmin) user->AddPrivilegy(User::Privilegies::Admin);

    //user->Login();
}

void RegistrationWindow::SaveClick()
{
    QMessageBox msg;
    msg.setWindowTitle("Результат збереження");

    LoadToUser(userToSave);

    if(userToSave->SaveToDB())
    {
        if(userToSave->Login())
        {
            msg.setText("Кориcтувача успішно збережено!");
            msg.exec();
            close();
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
    close();
}
