#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include "user.h"

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr, User *creator = nullptr, User *user= nullptr);
    ~RegistrationWindow();

private:
    Ui::RegistrationWindow *ui;

    bool isAdmin = false;
    bool isCardConnected = false;
    bool daysState[7]{false,false,false,false,false,false,false};
    QList<QPushButton*> daysStateBtns;
    User *userToSave = nullptr;

    void RefreshDaysStates();

    void LoadFromUser(User *user);
    void LoadToUser(User **user);

    bool IsUserInfoCorrect();
    void SetEditTextErrorState(QWidget* widget, bool isError = true);

private slots:
    void ChooseDayClick();
    void ChoosedDoctor();
    void SaveClick();
    void CancelClick();

};

#endif // REGISTRATIONWINDOW_H
