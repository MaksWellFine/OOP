#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "serialcommunicationwithcard.h"
#include "user.h"

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(SerialCommunicationWithCard* serial, QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void LoginClick();

private:
    static LoginWindow *nowOperatingWin;

    Ui::LoginWindow *ui;

    SerialCommunicationWithCard* serial;

    void CloseAndStart(User* user);

    SerialCommunicationWithCard::OnCardAddFunct* onCardConnected;
};

#endif // LOGINWINDOW_H
