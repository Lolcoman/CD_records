#include "databasedata.h"
#include <QSqlError>
#include <QSqlQuery>

#define CREATE_TABLE \
    "CREATE TABLE IF NOT EXISTS cd_table"\
    "(Author TEXT"\
    ",Album TEXT"\
    ",AlbumYear INT"\
    ",MusicGenre TEXT"\
    ",Playlist TEXT"\
    ",Booklet BLOB)"
DatabaseData::DatabaseData(QObject *parent)
    : QObject{parent}
{
}

//Inicializace databáze
bool DatabaseData::initDatabase(const QString &database)
{
    sqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    sqlDatabase.setDatabaseName(database);
    bool success = sqlDatabase.open();
    if(!success){
        DatabaseError = sqlDatabase.lastError().text();
    }
    return success;
}
//vytvoření databáze, const
bool DatabaseData::configDatabase()
{
    QSqlQuery query;
    bool success = query.exec(CREATE_TABLE);
    if(!success){
        DatabaseError = query.lastError().text();
    }
    return success;
}
