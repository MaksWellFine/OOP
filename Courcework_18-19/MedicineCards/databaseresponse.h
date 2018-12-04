#ifndef DATABASERESPONSE_H
#define DATABASERESPONSE_H

#include <QCoreApplication>
#include <QtSql>

class DatabaseResponse
{
    QString error;
    bool isError = false;

    QSqlRecord record;
public:
    DatabaseResponse();
    DatabaseResponse(QString errorMsg);
    DatabaseResponse(QSqlRecord record);

    bool IsError();
    QString GetError();
    QSqlRecord& GetRecord();
};

#endif // DATABASERESPONSE_H
