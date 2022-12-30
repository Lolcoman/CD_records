#include "databasehelper.h"

DatabaseHelper::DatabaseHelper()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("C:/Users/Michal/Desktop/cd_DB.db");
}

bool DatabaseHelper::Connect()
{
    if(database.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void DatabaseHelper::Dissconect()
{
    database.close();
}
