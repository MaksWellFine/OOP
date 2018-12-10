#ifndef WIDGETSHADOW_H
#define WIDGETSHADOW_H

#include <QWidget>

namespace Ui {
class WidgetShadow;
}

class WidgetSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSchedule(QWidget *parent = nullptr);
    ~WidgetSchedule();

private:
    Ui::WidgetSchedule *ui;
};

#endif // WIDGETSHADOW_H
