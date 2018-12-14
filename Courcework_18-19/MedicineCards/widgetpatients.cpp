#include "widgetpatients.h"
#include "ui_widgetpatients.h"

widgetPatients::widgetPatients(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetPatients)
{
    ui->setupUi(this);
}

widgetPatients::~widgetPatients()
{
    delete ui;
}
