#include "widgetregister.h"
#include "ui_widgetregister.h"

widgetRegister::widgetRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetRegister)
{
    ui->setupUi(this);
}

widgetRegister::~widgetRegister()
{
    delete ui;
}
