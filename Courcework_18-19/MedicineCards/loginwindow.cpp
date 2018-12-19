#include "loginwindow.h"
#include "mainwindow.h"
#include "ui_loginwindow.h"
#include "user.h"

#include <QMessageBox>

LoginWindow *LoginWindow::nowOperatingWin;

LoginWindow::LoginWindow(SerialCommunicationWithCard* serial, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);        

    connect(ui->buttonLogin, SIGNAL(released()), this, SLOT(LoginClick()));

    this->serial = serial;

    nowOperatingWin = this;
    onCardConnected = [](QString cardId)-> void{
        User *user = new User(cardId);
        if(user->IsPrivilegyExist(User::Privilegies::Admin) || user->IsPrivilegyExist(User::Privilegies::Doctor) ||
                user->IsPrivilegyExist(User::Privilegies::Recorder))
        {
            if(user->IsLogined())
            {
                nowOperatingWin->CloseAndStart(user);
                QMessageBox mBox;
                mBox.setText("Успішний вхід за допомогою картки!");
                mBox.exec();
            }else{
                QMessageBox mBox;
                mBox.setText("Не вдалось увійти за допомогою картки!");
                mBox.exec();
            }
        }else
        {
            QMessageBox mBox;
            mBox.setText("Помилка входу! Пацієнт не може входити в систему.");
            mBox.exec();
        }
    };
    serial->AddCardAddListener(onCardConnected);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::LoginClick()
{
    QMessageBox mBox;    
    User *user = new User(ui->lineEditLogin->text(), ui->lineEditPassword->text());
    if(user->IsPrivilegyExist(User::Privilegies::Admin) || user->IsPrivilegyExist(User::Privilegies::Doctor) ||
            user->IsPrivilegyExist(User::Privilegies::Recorder))
    {
        if(user->IsLogined())
        {            
            CloseAndStart(user);
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

void LoginWindow::CloseAndStart(User* user)
{
    MainWindow *wind = new MainWindow(serial, user);
    wind->show();
    serial->RemoveCardAddListener(onCardConnected);
    close();
}
