#include "userinfo.h"
#include "ui_userinfo.h"

UserInfo::UserInfo(User* user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfo)
{
    ui->setupUi(this);

    ShowUserInfo(user);

    connect(ui->btnOpenPatientsHistory, &QPushButton::released, this, &UserInfo::OnEditClick);
}

UserInfo::~UserInfo()
{
    delete ui;
}

void UserInfo::ShowUserInfo(User* user, bool isMainUser)
{
    if(user->IsPrivilegyExist(User::Privilegies::Doctor) && isMainUser)
        ui->btnOpenPatientsHistory->show();
    else
        ui->btnOpenPatientsHistory->hide();
    EditingState();

    ui->labelSurname->setText(user->GetSurname());
    ui->labelName->setText(user->GetName());
    ui->labelFatherName->setText(user->GetFatherName());
    ui->labelAdress->setText("Адреса: " + user->GetAddress());
    ui->labelPhoneNmber->setText("Номер телефону: " + user->GetPhoneNumber());

    QString privilegiesStr = "";
    for(int i = 0; i < User::privilegiesCount; i++)
        if(user->IsPrivilegyExist((User::Privilegies)i))
        {
            if(!privilegiesStr.isEmpty())
                privilegiesStr.append(", ");
            privilegiesStr.append(privilegiesNames[i]);
            if((User::Privilegies)i == User::Privilegies::Doctor)
                privilegiesStr.append("("+user->GetDoctor()->GetSpeciality()+")");
        }
    ui->labelPrivilege->setText(privilegiesStr);
}

void UserInfo::EditingState(bool state)
{
    ui->btnOpenPatientsHistory->setEnabled(state);
}

void UserInfo::OnEditClick()
{
    emit ShowEditRecordWindow();
}
