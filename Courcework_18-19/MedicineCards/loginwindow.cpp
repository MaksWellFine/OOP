#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "user.h"

#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);        

    connect(ui->buttonLogin, SIGNAL(released()), this, SLOT(LoginClick()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::LoginClick()
{
    QMessageBox mBox;    
    User user(ui->lineEditLogin->text(), ui->lineEditPassword->text());
    if(user.IsPrivilegyExist(User::Privilegies::Admin) || user.IsPrivilegyExist(User::Privilegies::Doctor) ||
            user.IsPrivilegyExist(User::Privilegies::Recorder))
    {
        if(user.IsLogined())
        {
            close();
        }else
        {
            mBox.setText("Помилка входу! Перевірте логін та пароль.");
            mBox.exec();
        }
    }else
    {
        mBox.setText("Помилка входу! Пацієнт не може входити в систему.");
        mBox.exec();
    }
}
