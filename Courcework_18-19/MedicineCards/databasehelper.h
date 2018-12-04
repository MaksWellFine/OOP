#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <databaseresponse.h>

#include <QApplication>
#include <QtSql>

class DatabaseHelper
{        
    QSqlDatabase database;
    QString databaseName;

    QString databaseError;
    bool isError = false;

    void SetError(QString);
    DatabaseResponse* CreateDatabaseResponse(QString error);
    DatabaseResponse* CreateDatabaseResponse(QSqlRecord record);

protected:
    QSqlQuery databaseQuery;

public:
    DatabaseHelper(QString);
    virtual ~DatabaseHelper();
    virtual void InitializeDatabase();
    bool IsErrorExists();
    QString GetError();    

    QSqlDatabase& GetDatabase();

    DatabaseResponse* CreateTable(QString table, QList<QString> arguments);
    DatabaseResponse* Insert(QString table, QList<QString> arguments, QList<QList<QString>> records);
    DatabaseResponse* Update(QString table, QList<QString> arguments, QList<QString> records, QString condition);
    DatabaseResponse* Select(QString table, QList<QString> arguments, QString condition);
};

#endif // DATABASEHELPER_H
