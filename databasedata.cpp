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
//Konfigurace nové databáze
bool DatabaseData::configDatabase()
{
    QSqlQuery query;
    bool success = query.exec(CREATE_TABLE);
    if(!success){
        DatabaseError = query.lastError().text();
    }
    return success;
}
//Vložení nahrávky do databáze, třída se stará o práci s db, Query je zde
bool DatabaseData::insertRecord(const Record &record)
{
    QSqlQuery qry;
    qry.prepare("INSERT INTO cd_table (Author,Album,AlbumYear,MusicGenre,Playlist,Booklet) VALUES (?,?,?,?,?,?)");
    qry.addBindValue(record.Author());
    qry.addBindValue(record.Album());
    qry.addBindValue(record.AlbumYear());
    qry.addBindValue(record.MusicGenre());
    qry.addBindValue(record.Playlist());
    qry.addBindValue(record.Booklet());
    bool success = qry.exec();
    if(!success){
        DatabaseError = qry.lastError().text();
    }
    return success;
}
//Oveření zda byla databáze načtena
bool DatabaseData::checkConnection()
{
    bool success = sqlDatabase.open();
    if(success){
        return true;
    }
    else{
        return false;
    }
}
