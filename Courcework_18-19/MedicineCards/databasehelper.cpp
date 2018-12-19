
#include "databasehelper.h"
#include <QtSql>

DatabaseHelper::DatabaseHelper(QString databaseName)
{
    this->databaseName = databaseName;
}

DatabaseHelper::~DatabaseHelper()
{
    database.close();
}

void DatabaseHelper::InitializeDatabase()
{    
    database = QSqlDatabase::addDatabase("QSQLITE", "qsqlite_1");
    database.setDatabaseName(databaseName + ".sqlite");
    if (!database.open()) {
        SetError(database.lastError().text());
    }
}

bool DatabaseHelper::IsErrorExists(){ return isError;}
QString DatabaseHelper::GetError(){isError = false; return databaseError;}
void DatabaseHelper::SetError(QString str){isError = true; databaseError = str;}

QSqlDatabase& DatabaseHelper::GetDatabase()
{
    return database;
}

DatabaseResponse* DatabaseHelper::CreateDatabaseResponse(QString error)
{
    SetError(error);
    return new DatabaseResponse(error);
}

DatabaseResponse* DatabaseHelper::CreateDatabaseResponse(QSqlRecord record)
{
    isError = false;
    return new DatabaseResponse(record);
}

DatabaseResponse* DatabaseHelper::CreateTable(QString table, QList<QString> arguments)
{
    int count = arguments.length();
    if(!database.isOpen()) return CreateDatabaseResponse("Problems with database!");
    if(count < 1) return CreateDatabaseResponse("Arguments count must be more than 0!");

    QString query = "CREATE TABLE IF NOT EXISTS %1(%2);";

    QString argumentsStr = "";
    for(int i = 0; i < count; i++){
        argumentsStr.append(arguments[i]);
        if(i+1 < count) argumentsStr.append(',');
    }

    query = query.arg(table)
            .arg(argumentsStr);
    databaseQuery = database.exec(query);
    bool isSuccess = (databaseQuery.lastError().text() == " ");//databaseQuery.exec(query);

    if(!isSuccess)        
        return CreateDatabaseResponse("Error in table creation: " + databaseQuery.lastError().text() + ", query: " + query);
    else
        return CreateDatabaseResponse(databaseQuery.record());
}

DatabaseResponse* DatabaseHelper::Insert(QString table, QList<QString> arguments, QList<QList<QString>> records)
{         
    int argumentsCount = arguments.length();
    int recordsCount = records.length();
    if(!database.isOpen()) return CreateDatabaseResponse("Problems with database!");
    if(argumentsCount < 1) return CreateDatabaseResponse("Arguments count must be more than 0!");
    if(recordsCount < 1) return CreateDatabaseResponse("Records count must be more than 0!");

    QString query = "INSERT INTO %1(%2) VALUES%3;";

    QString argumentsStr = "";
    for(int i = 0; i < argumentsCount; i++){
        argumentsStr.append(arguments[i]);
        if(i+1 < argumentsCount) argumentsStr.append(',');
    }

    QString recordsStr = "";
    for(int i = 0; i < recordsCount; i++){
        recordsStr.append("(");
        for(int q = 0; q < argumentsCount; q++){
            recordsStr.append("'" + records[i][q] + "'");
            if(q+1 < argumentsCount) recordsStr.append(',');
        }
        recordsStr.append(")");
        if(i+1 < recordsCount) recordsStr.append(',');
    }

    query = query.arg(table)
            .arg(argumentsStr)
            .arg(recordsStr);
    databaseQuery = database.exec(query);
    bool isSuccess = (databaseQuery.lastError().text() == " ");

    if(!isSuccess)
        return CreateDatabaseResponse("Error when inserting records: " + databaseQuery.lastError().text() + ", query: " + query);
    else
        return CreateDatabaseResponse(databaseQuery.record());
}

DatabaseResponse* DatabaseHelper::Update(QString table, QList<QString> arguments, QList<QString> values, QString condition)
{
    int argumentsCount = arguments.length();
    int valuesCount = values.length();
    if(!database.isOpen()) return CreateDatabaseResponse("Problems with database!");
    if(argumentsCount < 1) return CreateDatabaseResponse("Arguments count must be more than 0!");
    if(valuesCount < 1) return CreateDatabaseResponse("Records count must be more than 0!");

    QString query = "UPDATE %1 SET %2 %3;";

    QString argumentsStr = "";
    for(int i = 0; i < argumentsCount; i++){
        if(i < valuesCount){
            argumentsStr.append(arguments[i]+"="+"'"+values[i]+"'");
            if(i+1 < argumentsCount) argumentsStr.append(',');
        }
    }

    QString conditionsStr = "WHERE ";
    if(condition.length() < 1) conditionsStr = "";
    else conditionsStr.append(condition);

    query = query.arg(table)
            .arg(argumentsStr)
            .arg(conditionsStr);
    databaseQuery = database.exec(query);
    bool isSuccess = (databaseQuery.lastError().text() == " ");

    if(!isSuccess)
        return CreateDatabaseResponse("Error when updating records: " + databaseQuery.lastError().text() + ", query: " + query);
    else
        return CreateDatabaseResponse(databaseQuery.record());
}

DatabaseResponse* DatabaseHelper::Select(QString table, QList<QString> arguments, QString condition)
{
    int argumentsCount = arguments.length();    
    if(!database.isOpen()) return CreateDatabaseResponse("Problems with database!");

    QString query = "SELECT %2 FROM %1 %3;";

    QString argumentsStr = "*";
    if(argumentsCount > 0) argumentsStr = "";
    for(int i = 0; i < argumentsCount; i++){
        argumentsStr.append(arguments[i]);
        if(i+1 < argumentsCount) argumentsStr.append(',');
    }

    QString conditionsStr = "WHERE ";
    if(condition.length() < 1) conditionsStr = "";
    else conditionsStr.append(condition);

    query = query.arg(table)
            .arg(argumentsStr)
            .arg(conditionsStr);
    databaseQuery = database.exec(query);
    bool isSuccess = (databaseQuery.lastError().text() == " ");

    if(!isSuccess)
        return CreateDatabaseResponse("Error when selecting records: " + databaseQuery.lastError().text() + ", query: " + query);
    else
        return CreateDatabaseResponse(databaseQuery.record());
}

DatabaseResponse* DatabaseHelper::Delete(QString table, QString condition)
{
    if(!database.isOpen()) return CreateDatabaseResponse("Problems with database!");

    QString query = "DELETE FROM %1 %2;";

    QString conditionsStr = "WHERE ";
    if(condition.length() < 1) conditionsStr = "";
    else conditionsStr.append(condition);

    query = query.arg(table)
            .arg(conditionsStr);
    databaseQuery = database.exec(query);
    bool isSuccess = (databaseQuery.lastError().text() == " ");

    if(!isSuccess)
        return CreateDatabaseResponse("Error when deleting records: " + databaseQuery.lastError().text() + ", query: " + query);
    else
        return CreateDatabaseResponse(databaseQuery.record());
}
