#ifndef WIDGETPATIENTS_H
#define WIDGETPATIENTS_H

#include "registrationwindow.h"
#include "serialcommunicationwithcard.h"
#include "user.h"
#include "userinfo.h"

#include <QWidget>

namespace Ui {
class WidgetPatients;
}

class WidgetPatients : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPatients(SerialCommunicationWithCard* serial, User* nowUser, UserInfo* infoWidg, QWidget *parent = nullptr);
    explicit WidgetPatients(User* nowUser, UserInfo* infoWidg, QWidget *parent = nullptr);
    ~WidgetPatients();

    void CloseRegistrationWindow();
    void LoadUsers();
    User* GetChoosedItem();

private:
    bool isEditingUser = false;
    Ui::WidgetPatients *ui;

    SerialCommunicationWithCard* serial;

    RegistrationWindow* regWin = nullptr;

    User* user;
    UserInfo* userInfoWidg;

    QList<User> users;

    bool isOnlyPatients = false;

    int RowToListIndex(int indx);

private slots:
    void OnSaved();
    void OnClosed();

public slots:
    void ItemChoosed(QModelIndex,QModelIndex);
    void RemoveClick();
    void AddClick();
    void EditClick();
};

#endif // WIDGETPATIENTS_H
