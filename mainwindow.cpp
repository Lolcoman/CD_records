#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasehelper.h"
#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QFileDialog>
#include <QBuffer>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QPushButton
    connect(ui->bookletButton,SIGNAL(clicked(bool)),ui->bookletLabel,SLOT(text()));
    //connect(ui->insertButton,SIGNAL(clicked(bool)),update)
        connect(ui->insertButton, &QPushButton::clicked, this, &MainWindow::insertButtonClicked);
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
    }
    else
    {
        qDebug() << "Error inserting image into table:\n" << query.lastError();
    }


    database.Dissconect();
}


void MainWindow::on_bookletButton_clicked()
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

