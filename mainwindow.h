#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DatabaseData;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void actionSearchTriggered();
    void actionInsertTriggered();
    void actionCreateTriggered();
    void actionLoadTriggered();
private:
    Ui::MainWindow *ui;
    DatabaseData *sqlDatabase;
};
#endif // MAINWINDOW_H
