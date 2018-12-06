#include "registrationwindow.h"
#include "ui_registrationwindow.h"

#include <QGraphicsPixmapItem>
#include <QMessageBox>

RegistrationWindow::RegistrationWindow(QWidget *parent, User *creator) :
    QMainWindow(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);

    ui->labUserImage->setPixmap(QPixmap::fromImage(*(new QImage(":/images/user.jpg"))).scaled(
                                    ui->labUserImage->width(), ui->labUserImage->height(), Qt::KeepAspectRatio));

    connect(ui->butMon, SIGNAL(released()), this, SLOT(ChooseDayClick()));
    connect(ui->butTue, SIGNAL(released()), this, SLOT(ChooseDayClick()));
    connect(ui->butWed, SIGNAL(released()), this, SLOT(ChooseDayClick()));
    connect(ui->butThu, SIGNAL(released()), this, SLOT(ChooseDayClick()));
    connect(ui->butFri, SIGNAL(released()), this, SLOT(ChooseDayClick()));
    connect(ui->butSat, SIGNAL(released()), this, SLOT(ChooseDayClick()));
    connect(ui->butSun, SIGNAL(released()), this, SLOT(ChooseDayClick()));

}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::ChooseDayClick()
{
    QAbstractButton* but = static_cast<QAbstractButton *>(sender());
    QPalette pal = but->palette();
    int index = but->maximumHeight()/1000-1;
    daysState[index] = !daysState[index];
    if(daysState[index])
        pal.setColor(QPalette::Button, QColor(Qt::lightGray));
    else
        pal.setColor(QPalette::Button, QColor(Qt::transparent));
    but->setPalette(pal);
    but->update();
}
