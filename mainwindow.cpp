#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <QStandardItemModel>
#include "imagedelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sqlDatabase = new DatabaseData(this);
    dataModel = nullptr;

    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addActions({ui->actionInsert,ui->actionSearch});

    ui->statusbar->addPermanentWidget(ui->statusLabel,3);
    setWindowTitle("Databáze CD nahrávek");
    //Action tlačítka a další dialogy
    connect(ui->actionSearch, &QAction::triggered, this, &MainWindow::actionSearchTriggered);
    connect(ui->actionInsert, &QAction::triggered, this, &MainWindow::actionInsertTriggered);
    connect(ui->actionCreateDatabase, &QAction::triggered, this, &MainWindow::actionCreateTriggered);
    connect(ui->actionLoadDatabase, &QAction::triggered, this, &MainWindow::actionLoadTriggered);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::actionCloseTriggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionSearchTriggered()
{
    SearchWindow ser(this);

    SearchWindow search;
//    if(!sqlDatabase->checkConnection()){
//        QMessageBox::critical(this,"Chyba","Vyberte databázi!");
//        return;
//    }
    if(ser.exec() == QDialog::Rejected){
        return;
    }
    if(!sqlDatabase->insertRecord(ser.record())){
        QMessageBox::critical(this,"Chyba",sqlDatabase->getError()+"\nVyberte databázi!");
        return;
    }
    if(dataModel){
        dataModel->select();
    }
}

void MainWindow::actionInsertTriggered()
{
    //InsertWindow insert;
    InsertWindow rec(this);
    //insert.setModal(true);
    //insert.exec();
    if(!sqlDatabase->checkConnection()){
        QMessageBox::critical(this,"Chyba","Vyberte databázi!");
        return;
    }
    if(rec.exec() == QDialog::Rejected){
        return;
    }
    //Podmínka zda došlo k vložení záznamu do databáze
    if(!sqlDatabase->insertRecord(rec.record())){
        QMessageBox::critical(this,"Chyba",sqlDatabase->getError()+"\nVyberte databázi!");
        return;
    }
    if(dataModel){
        dataModel->select();
    }
}

void MainWindow::actionCreateTriggered()
{
    createDatabase(NOTCREATED);
    if(sqlDatabase->checkConnection()){
        ui->statusLabel->setText("Databáze je načtena");
    }
}

void MainWindow::actionLoadTriggered()
{
    createDatabase(CREATED);
    if(sqlDatabase->checkConnection()){
        ui->statusLabel->setText("Databáze je načtena");
    }
}

void MainWindow::createDatabase(Database database)
{
    QString newDatabase;
    //Pokud je již vytvořená
    if(database == CREATED){
        newDatabase =  QFileDialog::getOpenFileName(this,"Vytvořená databáze",QDir::rootPath(),"Databáze (*.db)");
    }else{ //Pokud se teprve vytváří
        newDatabase =  QFileDialog::getSaveFileName(this,"Nová databáze",QDir::rootPath(),"Databáze (*.db)");
    }
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
    pImageDelegate = new ImageDelegate(this);
    dataModel->setTable("cd_table"); //název tabulky
    dataModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    dataModel->select();
    dataModel->setHeaderData(0, Qt::Horizontal, tr("Autor"));
    dataModel->setHeaderData(1, Qt::Horizontal, tr("Album"));
    dataModel->setHeaderData(2, Qt::Horizontal, tr("Rok vydání alba"));
    dataModel->setHeaderData(3, Qt::Horizontal, tr("Žánr"));
    dataModel->setHeaderData(4, Qt::Horizontal, tr("Playlist"));
    dataModel->setHeaderData(5, Qt::Horizontal, tr("Obal CD"));
    //qDebug()<<dataModel->index(0,5).data().toByteArray();

    QByteArray img = dataModel->index(0,5).data().toByteArray();
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( img );
    //dataModel->(0, 0, outPixmap);
    //qDebug()<<img;
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);



    ui->tableView->setModel(dataModel);
    ui->tableView->setItemDelegateForColumn(5,pImageDelegate);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
}

void MainWindow::actionCloseTriggered()
{
    close();
}

