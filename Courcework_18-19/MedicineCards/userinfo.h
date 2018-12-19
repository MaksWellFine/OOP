#ifndef USERINFO_H
#define USERINFO_H

#include "user.h"

#include <QWidget>

namespace Ui {
class UserInfo;
}

class UserInfo : public QWidget
{
    Q_OBJECT

public:
    explicit UserInfo(User* user, QWidget *parent = nullptr);
    ~UserInfo();

    void ShowUserInfo(User* user, bool isMainUser = false);

private:
    QString privilegiesNames[User::privilegiesCount] = {"Адміністратор", "Реєстратор", "Лікар", "Пацієнт"};

    Ui::UserInfo *ui;

private slots:
    void OnEditClick();

public slots:
    void EditingState(bool state = false);

signals:
    void ShowEditRecordWindow();
};

#endif // USERINFO_H
