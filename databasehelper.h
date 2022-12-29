#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H
#include <QSqlDatabase>

class DatabaseHelper
{
private:
public:
    QSqlDatabase database;
    DatabaseHelper();
    bool Connect();
    void Dissconect();
};

#endif // DATABASEHELPER_H
