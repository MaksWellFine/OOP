#include "widgetpatients.h"
#include "ui_widgetpatients.h"
#include "registrationwindow.h"

#include <QMessageBox>

WidgetPatients::WidgetPatients(SerialCommunicationWithCard* serial, User* nowUser, UserInfo* infoWidg, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetPatients)
{
    ui->setupUi(this);

    this->serial = serial;

    user = nowUser;
    userInfoWidg = infoWidg;

    connect(ui->btnAdd, SIGNAL(released()), this, SLOT(AddClick()));
    connect(ui->btnRemove, SIGNAL(released()), this, SLOT(RemoveClick()));
    connect(ui->btnEdit, SIGNAL(released()), this, SLOT(EditClick()));

    QItemSelectionModel *sm = ui->tableWidgetUsers->selectionModel();
        connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                this, SLOT(ItemChoosed(QModelIndex,QModelIndex)));

    ui->tableWidgetUsers->verticalHeader()->setStretchLastSection(false);

    if(serial == nullptr)
        isOnlyPatients = true;
    LoadUsers();    
}

WidgetPatients::WidgetPatients(User* nowUser, UserInfo* infoWidg, QWidget *parent):
    WidgetPatients(nullptr, nowUser, infoWidg, parent)
{
    ui->btnAdd->setMinimumHeight(0);
    ui->btnAdd->setMaximumHeight(0);
    ui->btnEdit->setMinimumHeight(0);
    ui->btnEdit->setMaximumHeight(0);
    ui->btnRemove->setMinimumHeight(0);
    ui->btnRemove->setMaximumHeight(0);
}

WidgetPatients::~WidgetPatients()
{
    delete ui;
}

void WidgetPatients::LoadUsers()
{
    ui->tableWidgetUsers->sortItems(2);
    //int rowsCount = ui->tableWidgetUsers->rowCount();
    //for(int i = 0 ; i < rowsCount; i++)
    //    ui->tableWidgetUsers->removeRow(i);
    users.clear();
    ui->tableWidgetUsers->setRowCount(0);

    if(user->IsPrivilegyExist(User::Privilegies::Admin) && !isOnlyPatients)
        users.append(user->GetDatabase()->GetUsers(""));
    else if(user->IsPrivilegyExist(User::Privilegies::Recorder) || isOnlyPatients)
        users.append(user->GetDatabase()->GetUsers(HospitalDatabaseHelper::ARG_USERS_PRIVILEGIES+">=8"));

    for(int i = 0; i < users.length(); i++)
    {
        ui->tableWidgetUsers->insertRow(ui->tableWidgetUsers->rowCount());
        ui->tableWidgetUsers->setItem(ui->tableWidgetUsers->rowCount()-1, 0, new QTableWidgetItem(users[i].ToShortStr()));
        ui->tableWidgetUsers->setItem(ui->tableWidgetUsers->rowCount()-1, 1, new QTableWidgetItem(users[i].GetPhoneNumber()));
        ui->tableWidgetUsers->setItem(ui->tableWidgetUsers->rowCount()-1, 2, new QTableWidgetItem(users[i].GetLogin()));
    }
    //ui->tableWidgetUsers->update();
    ui->tableWidgetUsers->sortItems(0);
}

int WidgetPatients::RowToListIndex(int indx)
{
    if(indx < ui->tableWidgetUsers->rowCount())
        for(int i = 0; i < users.length(); i++)
            if(ui->tableWidgetUsers->item(indx, 2)->text() == users[i].GetLogin())
                return i;
    return 0;
}

void WidgetPatients::RemoveClick()
{
    QList<QTableWidgetItem*> items = ui->tableWidgetUsers->selectedItems();
    if(items.length() > 0)
    {
        if(isEditingUser)
        {
            QMessageBox msg;
            msg.setWindowTitle("Попередження");
            msg.setText("Інший користувач ще редагується або додається!");
            msg.exec();
            return;
        }
        int selectedRow = RowToListIndex(items.at(0)->row());
        if(users[selectedRow].IsPrivilegyExist(User::Privilegies::Admin))
        {
            QMessageBox msg;
            msg.setWindowTitle("Помилка видалення");
            msg.setText("Видаляти адміністратора заборонено!");
            msg.exec();
            return;
        }

        user->GetDatabase()->DeleteUser(&users[selectedRow]);
        if(!user->GetDatabase()->IsErrorExists())
        {
            users.removeAt(selectedRow);
            ui->tableWidgetUsers->removeRow(selectedRow);
        }
    }
}

void WidgetPatients::AddClick()
{
    if(!isEditingUser)
    {
        isEditingUser = true;
        regWin = new RegistrationWindow(serial, nullptr, user);
        connect(regWin, SIGNAL(onSaved()), this, SLOT(OnSaved()));
        connect(regWin, &RegistrationWindow::onClose, this, &WidgetPatients::OnClosed);        
        regWin->show();
    }else
    {
        QMessageBox msg;
        msg.setWindowTitle("Попередження");
        msg.setText("Інший користувач уже редагується або додається!");
        msg.exec();
    }
}

void WidgetPatients::EditClick()
{
    QList<QTableWidgetItem*> items = ui->tableWidgetUsers->selectedItems();
    if(items.length() > 0)
    {
        if(!isEditingUser)
        {
            isEditingUser = true;
            regWin = new RegistrationWindow(serial, nullptr, user, &users[RowToListIndex(items.at(0)->row())]);
            connect(regWin, SIGNAL(onSaved()), this, SLOT(OnSaved()));
            connect(regWin, &RegistrationWindow::onClose, this, &WidgetPatients::OnClosed);
            regWin->show();
        }else
        {
            QMessageBox msg;
            msg.setWindowTitle("Попередження");
            msg.setText("Інший користувач уже редагується або додається!");
            msg.exec();
        }
    }
}

void WidgetPatients::OnSaved()
{
    LoadUsers();
    user->LoadFromDB();
    disconnect(sender(), SIGNAL(onSaved()), this, SLOT(OnSaved()));
}

void WidgetPatients::OnClosed()
{
    isEditingUser = false;
}

void WidgetPatients::ItemChoosed(QModelIndex indx,QModelIndex indx1)
{
    if(ui->tableWidgetUsers->rowCount() <= 0) return;
    int rIndx = RowToListIndex(indx.row());
    if(rIndx < users.length())
        userInfoWidg->ShowUserInfo(&users[rIndx]);
}

void WidgetPatients::CloseRegistrationWindow()
{
    if(regWin!=nullptr)
        regWin->close();
}

User* WidgetPatients::GetChoosedItem()
{
    QList<QTableWidgetItem*> items = ui->tableWidgetUsers->selectedItems();
    if(items.length() > 0)
        return new User(users.at(RowToListIndex(items[0]->row())));
    else
        return nullptr;
}
