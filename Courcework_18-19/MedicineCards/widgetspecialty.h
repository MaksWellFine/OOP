#ifndef WIDGETSPECIALTY_H
#define WIDGETSPECIALTY_H

#include <QWidget>

namespace Ui {
class widgetSpecialty;
}

class widgetSpecialty : public QWidget
{
    Q_OBJECT

public:
    explicit widgetSpecialty(QWidget *parent = nullptr);
    ~widgetSpecialty();

private:
    Ui::widgetSpecialty *ui;
};

#endif // WIDGETSPECIALTY_H
