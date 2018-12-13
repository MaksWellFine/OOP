#include "patientrecordswindow.h"
#include "ui_patientrecordswindow.h"

PatientRecordsWindow::PatientRecordsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PatientRecordsWindow)
{
    ui->setupUi(this);
}

PatientRecordsWindow::~PatientRecordsWindow()
{
    delete ui;
}
