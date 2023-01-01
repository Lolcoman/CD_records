#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>

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
    void actionInsertTriggered();
    void actionCreateTriggered();
    void actionLoadTriggered();
    void actionCloseTriggered();
    void actionInfoTriggered();
    void searchLineEdit(const QString &arg1);
    void searchComboBox(int index);
private:
    void createDatabase(Database database);
    Ui::MainWindow *ui;
    DatabaseData *sqlDatabase;
    QSqlTableModel *dataModel;
    ImageDelegate *pImageDelegate;
    QSortFilterProxyModel *proxyModel;
};
#endif // MAINWINDOW_H
