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
    explicit RegistrationWindow(QWidget *parent = nullptr, User *creator = nullptr);
    ~RegistrationWindow();

private:
    Ui::RegistrationWindow *ui;

    bool daysState[7]{false,false,false,false,false,false,false};

private slots:
    void ChooseDayClick();

};

#endif // REGISTRATIONWINDOW_H
