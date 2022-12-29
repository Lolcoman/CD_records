#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "databasehelper.h"
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

    DatabaseHelper con;
    QSqlQueryModel * modal= new QSqlQueryModel();

    con.Connect();
    //QSqlQuery* qry = new QSqlQuery(con.database);
    QSqlQuery qry(con.database);

    qry.prepare("SELECT * FROM cd_table");
    if(qry.exec())
    {
        qDebug() << (qry.result());
        //ui->tableView->setRowCount(qry.size());
        int Row_Number = 0;
        while(qry.next())
        {
            //ImageName = qry->value("Booklet").toString();
            ImageDataFromDatabase = QByteArray::fromBase64(qry.value("Booklet").toByteArray());
            Image.loadFromData(ImageDataFromDatabase,"BMP");

            QTableWidgetItem *Image_item = new QTableWidgetItem();
            //ui->tableWidget->setItem(Row_Number,0,Image_item);

            Row_Number = Row_Number+1;
        }
    }
    con.Dissconect();
    //ui->tableWidget->resizeRowsToContents();
    //modal->setQuery(*qry);
    //ui->tableWidget->setModel(modal);

    qDebug() << (modal->rowCount());
}

