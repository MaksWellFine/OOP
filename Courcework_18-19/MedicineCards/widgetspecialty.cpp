#include "widgetspecialty.h"
#include "ui_widgetspecialty.h"

widgetSpecialty::widgetSpecialty(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetSpecialty)
{
    ui->setupUi(this);
}

widgetSpecialty::~widgetSpecialty()
{
    delete ui;
}
