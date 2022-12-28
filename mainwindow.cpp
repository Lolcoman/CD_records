#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasehelper.h"
#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QFileDialog>
#include <QBuffer>
#include <QSqlError>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "searchwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Databáze CD nahrávek");
    //Normální tlačíka
    connect(ui->insertButton, &QPushButton::clicked, this, &MainWindow::insertButtonClicked);
    connect(ui->bookletButton, &QPushButton::clicked, this, &MainWindow::bookletButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearButtonClicked);
    //Action tlačítka
    connect(ui->actionVyhledat, &QAction::triggered, this, &MainWindow::actionVyhledatTriggered);
    //Regex validátor pro roky
    QRegularExpression rx("[1-2][0-9][0-9][0-9]");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->yearLineEdit->setValidator(validator);

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


void MainWindow::insertButtonClicked()
{
    QString author = ui->autorLineEdit->text();
    QString album = ui->albumLineEdit->text();
    QString year = ui->yearLineEdit->text();
    QString genre = ui->genreLineEdit->text();
    QString playlist = ui->playlistLineEdit->text();
    //QString booklet = ui->bookletLabel->text();
    QStringList items;
    items << author;
    items << album;
    items << year;
    items << genre;
    items << playlist;
    items.removeAll(QString(""));
    if(items.length() < 5)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Chyba","Vyplňte všecha pole !");
        return;
    }
    for(int i=0 ; i < items.length() ; i++){
        qDebug() << items.at(i) << Qt::endl;
    }
    //Převod z labelu na obrázek a uložení do DB
    //ZDE MUSÍ BÝT JEŠTĚ OŠTĚŘENÍ ZDA UŽIVATEL VŮBEC NAHRÁL OBRÁZEK!
    QPixmap inPixmap = ui->bookletLabel->pixmap();
    QByteArray arr;
    QBuffer inBuffer(&arr);
    inBuffer.open( QIODevice::WriteOnly );
    inPixmap.save( &inBuffer, "BMP" );

    DatabaseHelper database;

    if(database.Connect())
    {
        qDebug() << "Connected" << Qt::endl;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO cd_table (Author,Album,AlbumYear,MusicGenre,Playlist,Booklet) VALUES ('"+author+"','"+album+"','"+year+"','"+genre+"','"+playlist+"',:arr)");
    query.bindValue( ":arr", arr );
     if(query.exec())
    {
        qDebug() << "Query success" << Qt::endl;
        QMessageBox messageBox;
        messageBox.information(0,"Záznam","Záznam byl vložen.");
    }
    else
    {
        qDebug() << "Error inserting image into table:\n" << query.lastError();
    }


    database.Dissconect();
}


void MainWindow::bookletButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Vyberte obrázek"),"",tr("Obrázky (*.png *.jpg *.jpeg, *bmp)"));

    //Pokud nebylo nic vybráno
    if(QString::compare(filename, QString()) != 0)
    {
        QImage image;
        QByteArray arr;
        bool valid = image.load(filename);
        //Pokud je soubor poškozený
        if(valid)
        {
            //image = image.scaledToWidth(ui->bookletLabel->width(),Qt::SmoothTransformation);
            ui->bookletLabel->setPixmap(QPixmap::fromImage(image));

            //ui->bookletLabel->setPixmap(QPixmap::fromImage(image).scaled(w,h,Qt::KeepAspectRatio));
            QBuffer buffer(&arr);
            buffer.open(QIODevice::WriteOnly);
            image.save(&buffer, "BMP");
        }
        else
        {

        }
    }
}


void MainWindow::clearButtonClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Znovu", "Opravdu chcete všechna pole vymazat?",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        ui->autorLineEdit->clear();
        ui->albumLineEdit->clear();
        ui->yearLineEdit->clear();
        ui->genreLineEdit->clear();
        ui->playlistLineEdit->clear();
        ui->bookletLabel->setText("Náhled");
      } else {
        return;
      }
}


void MainWindow::actionVyhledatTriggered()
{
    SearchWindow search;
    search.setModal(true);
    search.exec();
}

