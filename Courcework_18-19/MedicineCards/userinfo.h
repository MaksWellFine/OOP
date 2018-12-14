#ifndef USERINFO_H
#define USERINFO_H

#include <QWidget>

namespace Ui {
class userInfo;
}

class userInfo : public QWidget
{
    Q_OBJECT

public:
    explicit userInfo(QWidget *parent = nullptr);
    ~userInfo();

private:
    Ui::userInfo *ui;
};

#endif // USERINFO_H
