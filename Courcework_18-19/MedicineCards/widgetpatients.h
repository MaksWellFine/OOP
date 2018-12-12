#ifndef WIDGETPATIENTS_H
#define WIDGETPATIENTS_H

#include <QWidget>

namespace Ui {
class widgetPatients;
}

class widgetPatients : public QWidget
{
    Q_OBJECT

public:
    explicit widgetPatients(QWidget *parent = nullptr);
    ~widgetPatients();

private:
    Ui::widgetPatients *ui;
};

#endif // WIDGETPATIENTS_H
