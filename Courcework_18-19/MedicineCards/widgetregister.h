#ifndef WIDGETREGISTER_H
#define WIDGETREGISTER_H

#include <QWidget>

namespace Ui {
class widgetRegister;
}

class widgetRegister : public QWidget
{
    Q_OBJECT

public:
    explicit widgetRegister(QWidget *parent = nullptr);
    ~widgetRegister();

private:
    Ui::widgetRegister *ui;
};

#endif // WIDGETREGISTER_H
