#include "mainwindow.h"
#include "infowindow.h"
#include "ui_mainwindow.h"
#include "databasedata.h"
#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QFileDialog>
#include <QBuffer>
#include <QSqlError>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "insertwindow.h"
#include <QSqlTableModel>
#include <QStandardItemModel>
#include "imagedelegate.h"
#include "updatewindow.h"
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sqlDatabase = new DatabaseData(this);
    proxyModel = new QSortFilterProxyModel(this);
    dataModel = nullptr;
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addActions({ui->actionInsert,ui->actionDelete,ui->actionUpdate});

    ui->statusbar->addPermanentWidget(ui->statusLabel,3);
    setWindowTitle("Databáze CD nahrávek");
    //Action tlačítka a další dialogy
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)), SLOT(searchComboBox(int)));
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &::MainWindow::searchLineEdit);
    connect(ui->actionInsert, &QAction::triggered, this, &MainWindow::actionInsertTriggered);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::actionDeleteTriggered);
    connect(ui->actionUpdate, &QAction::triggered, this, &MainWindow::actionUpdateTriggered);
    connect(ui->actionCreateDatabase, &QAction::triggered, this, &MainWindow::actionCreateTriggered);
    connect(ui->actionLoadDatabase, &QAction::triggered, this, &MainWindow::actionLoadTriggered);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::actionCloseTriggered);
    connect(ui->actionInfo, &QAction::triggered, this, &MainWindow::actionInfoTriggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::actionInsertTriggered()
{
    InsertWindow rec(this);
    if(!sqlDatabase->checkConnection()){
        QMessageBox::critical(this,"Chyba","Nejprve vytvořte nebo nahrejte databázi!");
        return;
    }
    if(rec.exec() == QDialog::Rejected){
        return;
    }
    //Podmínka zda došlo k vložení záznamu do databáze
    if(!sqlDatabase->insertRecord(rec.record())){
        QMessageBox::critical(this,"Chyba",sqlDatabase->getError());
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
    dataModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    dataModel->setHeaderData(1, Qt::Horizontal, tr("Autor"));
    dataModel->setHeaderData(2, Qt::Horizontal, tr("Album"));
    dataModel->setHeaderData(3, Qt::Horizontal, tr("Rok vydání alba"));
    dataModel->setHeaderData(4, Qt::Horizontal, tr("Žánr"));
    dataModel->setHeaderData(5, Qt::Horizontal, tr("Playlist"));
    dataModel->setHeaderData(6, Qt::Horizontal, tr("Obal CD"));

    QByteArray img = dataModel->index(0,6).data().toByteArray();
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( img );
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    ui->tableView->setItemDelegateForColumn(6,pImageDelegate);

    proxyModel->setSourceModel(dataModel);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->comboBox->addItems(QStringList()<<"Autor"<<"Rok vydání alba"<<"Žánr");
    ui->lineEdit->setReadOnly(false);
    ui->tableView->setModel(proxyModel);
}

void MainWindow::actionCloseTriggered()
{
    close();
}

void MainWindow::searchLineEdit(const QString &arg1)
{
    proxyModel->setFilterFixedString(arg1);
}

void MainWindow::searchComboBox(int index)
{
    switch (index) {
    case 0:
        index = 1;
        break;
    case 1:
        index = 3;
        break;
    case 2:
        index = 4;
    default:
        break;
    }
    proxyModel->setFilterKeyColumn(index);
}

void MainWindow::actionInfoTriggered()
{
    InfoWindow infoWindow;
    infoWindow.setModal(true);
    infoWindow.exec();
}


void MainWindow::actionDeleteTriggered()
{
    if(!sqlDatabase->checkConnection()){
        QMessageBox::critical(this,"Chyba","Nejprve vytvořte nebo nahrejte databázi!");
        return;
    }
    const int id = ui->tableView->currentIndex().row();
    QVariant selectedId = dataModel->data(dataModel->index(id,0));
    //qDebug("ID:%i ", selectedId.toInt());
    if(selectedId.toInt()== 0){
        QMessageBox::critical(this,"Chyba","Nebyl vybrán žádný záznám!");
        return;
    }
    //Podmínka zda došlo k vložení záznamu do databáze
    if(!sqlDatabase->deleteRecord(selectedId.toInt())){
        QMessageBox::critical(this,"Chyba",sqlDatabase->getError());
        return;
    }
    if(dataModel){
        dataModel->select();
        proxyModel->setSourceModel(dataModel);;
        ui->tableView->setModel(proxyModel);
    }
}

void MainWindow::actionUpdateTriggered()
{
    updatewindow rec(this);
    if(!sqlDatabase->checkConnection()){
        QMessageBox::critical(this,"Chyba","Nejprve vytvořte nebo nahrejte databázi!");
        return;
    }
    if(rec.exec() == QDialog::Rejected){
        return;
    }
    const int id = ui->tableView->currentIndex().row();
    QVariant selectedId = dataModel->data(dataModel->index(id,0));
    //Podmínka zda došlo k vložení záznamu do databáze
    if(!sqlDatabase->updateRecord(rec.record(),selectedId.toInt())){
        QMessageBox::critical(this,"Chyba",sqlDatabase->getError());
        return;
    }
    if(dataModel){
        dataModel->select();
    }
}

