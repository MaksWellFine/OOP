#include "widgetspecialty.h"
#include "ui_widgetspecialty.h"
#include "hospitaldatabasehelper.h"

#include <QInputDialog>
#include <QMessageBox>

WidgetSpecialty::WidgetSpecialty(HospitalDatabaseHelper *helper, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSpecialty)
{
    ui->setupUi(this);    

    connect(ui->btnRemove, SIGNAL(released()), this, SLOT(RemoveClick()));
    connect(ui->btnAdd, SIGNAL(released()), this, SLOT(AddClick()));

    ui->tableRegister->verticalHeader()->setStretchLastSection(false);

    this->helper = helper;
    QList<QString> specs = helper->GetSpecialities("");
    for(int i = 0; i < specs.length(); i++)
        AddRow(specs.at(i));

    ui->tableRegister->sortItems(0);
}

WidgetSpecialty::~WidgetSpecialty()
{
    delete ui;
}

void WidgetSpecialty::AddRow(QString specialty)
{
    ui->tableRegister->insertRow(ui->tableRegister->rowCount());
    ui->tableRegister->setItem(ui->tableRegister->rowCount()-1, 0, new QTableWidgetItem(specialty));
}

void WidgetSpecialty::RemoveClick()
{
    QList<QTableWidgetItem*> items = ui->tableRegister->selectedItems();
    if(items.length() > 0)
    {
        QString specName = items.at(0)->text();

        if(helper->GetDoctors(HospitalDatabaseHelper::ARG_DOCTORS_SPECIALITY_ID+"='"+QString::number(helper->GetSpecialityId(specName))+"'").length()!=0)
        {
            QMessageBox msg;
            msg.setWindowTitle("Помилка");
            msg.setText("Цю спеціальність видалити не можна! Існує лікар з даної спеціальності.");
            msg.exec();
            return;
        }

        helper->DeleteSpeciality(specName);
        if(!helper->IsErrorExists())
        {
            ui->tableRegister->removeRow(items.at(0)->row());
            ui->tableRegister->sortItems(0);
        }
    }
}

void WidgetSpecialty::AddClick()
{
    bool isOk;
    QString newSpec = QInputDialog::getText(this, tr("Назва нової спеціальності"),
                                         tr("Спеціальність:"), QLineEdit::Normal,
                                         "", &isOk);
    if(isOk && !newSpec.isEmpty())
    {
        helper->SaveSpeciality(newSpec);
        if(!helper->IsErrorExists())
        {
            AddRow(newSpec);
            ui->tableRegister->sortItems(0);

            int rowId = -1;
            for(int i = 0; i < ui->tableRegister->rowCount(); i++)
                if(ui->tableRegister->item(i, 0)->text().compare(newSpec) == 0)
                {
                    rowId = i;
                    break;
                }
            if(rowId >= 0)
                ui->tableRegister->selectRow(rowId);
        }else
        {
            QMessageBox msg;
            msg.setWindowTitle("Помилка");
            msg.setText(helper->GetError());
            msg.exec();
        }
    }
}
