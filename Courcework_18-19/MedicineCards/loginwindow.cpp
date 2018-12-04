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
    if(user.IsLogined())
    {
        close();
    }else
    {
        mBox.setText("Помилка входу! Перевірте логін та пароль.");
        mBox.exec();
    }
}