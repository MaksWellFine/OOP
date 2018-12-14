#include "loginwindow.h"
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
        User user(cardId);
        if(user.IsLogined())
        {
            QMessageBox mBox;
            mBox.setText("Успішний вхід за допомогою картки!");
            mBox.exec();
            nowOperatingWin->Close();
        }else{
            QMessageBox mBox;
            mBox.setText("Не вдалось увійти за допомогою картки!");
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

void LoginWindow::Close()
{
    serial->RemoveCardAddListener(onCardConnected);
    close();
}
