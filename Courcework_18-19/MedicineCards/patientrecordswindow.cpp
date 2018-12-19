#include "patientrecordswindow.h"
#include "ui_patientrecordswindow.h"

#include <QMessageBox>

PatientRecordsWindow::PatientRecordsWindow(User* patient, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PatientRecordsWindow)
{
    ui->setupUi(this);

    ui->tableWidgetPatientRecords->verticalHeader()->setStretchLastSection(false);

    this->patient = patient;

    ui->comboBoxSpeiality->addItems(QStringList::fromSet(patient->GetDatabase()->GetSpecialities("").toSet()));
    ui->labelPatient->setText(patient->ToShortStr());

    QTimer* timer = new QTimer(this);
    timer->setInterval(200);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
    timer->start();

    connect(ui->btnSave, &QPushButton::released, this, &PatientRecordsWindow::SaveRecord);
}

PatientRecordsWindow::~PatientRecordsWindow()
{
    delete ui;
}

void PatientRecordsWindow::LoadRecords()
{
    ui->tableWidgetPatientRecords->setRowCount(0);

    QList<PatientRecord> allRecords = patient->GetDatabase()->GetPatientRecords(patient);
    for(int i = allRecords.length()-1; i >= 0; i--)
    {
        if(allRecords[i].GetDoctor()->GetSpeciality()==specialty && allRecords[i].IsVisited())
        {
            records.append(*new PatientRecord(allRecords[i]));

            ui->tableWidgetPatientRecords->insertRow(ui->tableWidgetPatientRecords->rowCount());
            ui->tableWidgetPatientRecords->setItem(ui->tableWidgetPatientRecords->rowCount()-1, 0,
                new QTableWidgetItem(allRecords[i].GetVisitDateTime()->toString(PatientRecord::DATE_TIME_FORMAT)));
            ui->tableWidgetPatientRecords->setItem(ui->tableWidgetPatientRecords->rowCount()-1, 1,
                new QTableWidgetItem(allRecords[i].GetDoctor()->GetUser()->ToShortStr()));
            ui->tableWidgetPatientRecords->setItem(ui->tableWidgetPatientRecords->rowCount()-1, 2,
                new QTableWidgetItem(*allRecords[i].GetVisitInfo()));
        }
    }
}

void PatientRecordsWindow::LoadRecordInfo()
{
    if(currentRecord != nullptr)
    {
        ui->labelName->setText(currentRecord->GetDoctor()->GetUser()->ToShortStr());
        ui->labelSpeciality->setText(specialty);
        ui->labelDataTime->setText(currentRecord->GetVisitDateTime()->toString(PatientRecord::DATE_TIME_FORMAT));

        ui->textEdit->setText(*currentRecord->GetVisitInfo());
        ui->textEdit->setEnabled(true);
        ui->btnSave->setEnabled(true);
    }else if(ui->btnSave->isEnabled())
    {
        ui->labelName->setText("Невідомо");
        ui->labelSpeciality->setText("");
        ui->labelDataTime->setText("Дата/час");

        ui->textEdit->setText("");
        ui->textEdit->setEnabled(false);
        ui->btnSave->setEnabled(false);
    }
}

void PatientRecordsWindow::OnTimer()
{
    if(specialty != ui->comboBoxSpeiality->currentText())
    {
        specialty = ui->comboBoxSpeiality->currentText();
        LoadRecords();
    }
    if(ui->tableWidgetPatientRecords->selectedItems().length() > 0)
    {
        int row = ui->tableWidgetPatientRecords->selectedItems()[0]->row();
        if(selectedIndex != row)
        {
            selectedIndex = row;
            if(selectedIndex < records.length())
                currentRecord = &records[selectedIndex];
            else
                return;
            LoadRecordInfo();
        }
    }else
    {
        selectedIndex = -1;
        currentRecord = nullptr;
        LoadRecordInfo();
    }
}

void PatientRecordsWindow::SaveRecord()
{
    if(currentRecord != nullptr)
    {
        currentRecord->SetVisitInfo(new QString(ui->textEdit->toPlainText()));
        if(!currentRecord->SaveToDB())
        {
            QMessageBox msg;
            msg.setWindowTitle("Помилка збереження");
            msg.setText("Не можливо зберегти дані, спробуйте ще раз!");
            msg.exec();
        }
        LoadRecords();
        LoadRecordInfo();
    }else
    {
        QMessageBox msg;
        msg.setWindowTitle("Помилка збереження");
        msg.setText("Не вибрано жодного запису для збереження!");
        msg.exec();
    }
}


void PatientRecordsWindow::closeEvent(QCloseEvent *event)
{
    emit onClose();
    QWidget::closeEvent(event);
}
