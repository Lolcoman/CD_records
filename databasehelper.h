#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H
#include <QSqlDatabase>

class DatabaseHelper
{
private:
    QSqlDatabase database;
public:
    DatabaseHelper();
    bool Connect();
    void Dissconect();
};

#endif // DATABASEHELPER_H
