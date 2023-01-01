#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DatabaseData;
class QSqlTableModel;
class ImageDelegate;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Database
    {
        CREATED,
        NOTCREATED
    };
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void actionSearchTriggered();
    void actionInsertTriggered();
    void actionCreateTriggered();
    void actionLoadTriggered();
    void actionCloseTriggered();
private:
    void createDatabase(Database database);
    Ui::MainWindow *ui;
    DatabaseData *sqlDatabase;
    QSqlTableModel *dataModel;
    ImageDelegate *pImageDelegate;
};
#endif // MAINWINDOW_H
