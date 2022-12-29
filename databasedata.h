#ifndef DATABASEDATA_H
#define DATABASEDATA_H

#include <QObject>
#include <QSqlDatabase>

class DatabaseData : public QObject
{
    Q_OBJECT
public:
    //veřejné metody
    explicit DatabaseData(QObject *parent = nullptr);
    bool initDatabase(const QString &database);
    bool configDatabase(); //const
    QString getError() const {return DatabaseError;}
private:
    QSqlDatabase sqlDatabase;
    QString DatabaseError;
};

#endif // DATABASEDATA_H
