#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasehelper.h"
#include "databasedata.h"
#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QFileDialog>
#include <QBuffer>
#include <QSqlError>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "searchwindow.h"
#include "insertwindow.h"
#include <QSqlTableModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sqlDatabase = new DatabaseData(this);
    dataModel = nullptr;
    setWindowTitle("Databáze CD nahrávek");
    //Action tlačítka a další dialogy
    connect(ui->actionSearch, &QAction::triggered, this, &MainWindow::actionSearchTriggered);
    connect(ui->actionInsert, &QAction::triggered, this, &MainWindow::actionInsertTriggered);
    connect(ui->actionCreateDatabase, &QAction::triggered, this, &MainWindow::actionCreateTriggered);
    connect(ui->actionLoadDatabase, &QAction::triggered, this, &MainWindow::actionLoadTriggered);

    //Test připojení databáze
    DatabaseHelper con;

    if(con.Connect())
    {
        qDebug() << "Connected"<<Qt::endl;
        ui->statusLabel->setText("Databáze je načtena");
    }
    else
    {
        ui->statusLabel->setText("Databáze není načtena");
    }
    con.Dissconect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionSearchTriggered()
{
    SearchWindow search;
    search.setModal(true);
    search.exec();
}


void MainWindow::actionInsertTriggered()
{
    InsertWindow insert;
    insert.setModal(true);
    insert.exec();
}

void MainWindow::actionCreateTriggered()
{
    close();
}

void MainWindow::actionLoadTriggered()
{
    //
    auto newDatabase =  QFileDialog::getSaveFileName(this,"Nová databáze",QDir::rootPath(),"Databáze (*.db)");
    if(newDatabase.isEmpty()){
        return;
    }
    if(!sqlDatabase->initDatabase(newDatabase)){
        QMessageBox::critical(this,"Chyba",sqlDatabase->getError());
        return;
    }
    if(!sqlDatabase->configDatabase()){
        QMessageBox::critical(this,"Chyba",sqlDatabase->getError());
    }
    delete dataModel;
    dataModel = new QSqlTableModel(this);
    dataModel->setTable("Model");
}
