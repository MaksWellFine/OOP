#include "databaseresponse.h"

DatabaseResponse::DatabaseResponse()
{
}

DatabaseResponse::DatabaseResponse(QString errorMsg)
{
    isError = true;
    error = errorMsg;    
}

DatabaseResponse::DatabaseResponse(QSqlRecord record)
{
    this->record = record;
}

bool DatabaseResponse::IsError()
{
    return isError;
}

QString DatabaseResponse::GetError()
{
    if(isError)
        return error;
    else
        return QString();
}

QSqlRecord& DatabaseResponse::GetRecord()
{
    return record;
}
