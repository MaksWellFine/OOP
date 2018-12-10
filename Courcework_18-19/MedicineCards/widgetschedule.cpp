#include "widgetschedule.h"
#include "ui_widgetschedule.h"

WidgetSchedule::WidgetSchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSchedule)
{
    ui->setupUi(this);
}

WidgetSchedule::~WidgetSchedule()
{
    delete ui;
}
