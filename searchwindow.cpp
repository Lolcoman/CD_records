#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "databasedata.h"
#include <qsqldatabase.h>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QTableWidgetItem>

SearchWindow::SearchWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    setWindowTitle("Vyhledávání CD nahrávky");
    //Normální tlačíka
    connect(ui->searchButton, &QPushButton::clicked, this, &SearchWindow::searchButtonClicked);
}

SearchWindow::~SearchWindow()
{
    delete ui;
}


void SearchWindow::searchButtonClicked()
{
    QByteArray ImageDataFromDatabase;
    QPixmap Image;

    DatabaseData con;
    DatabaseData data;
    QSqlQueryModel * modal= new QSqlQueryModel();

    //QSqlQuery* qry = new QSqlQuery(con.database)
    //ui->tableWidget->resizeRowsToContents();
    //modal->setQuery(*qry);
    //ui->tableWidget->setModel(modal);

    qDebug() << (modal->rowCount());
}

