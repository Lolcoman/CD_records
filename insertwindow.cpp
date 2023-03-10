#include "insertwindow.h"
#include "ui_insertwindow.h"
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QFileDialog>
#include <QBuffer>
#include <QSqlError>

InsertWindow::InsertWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertWindow)
{
    ui->setupUi(this);
    setWindowTitle("Přidání CD nahrávky");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Přidat");
    ui->buttonBox->button(QDialogButtonBox::Retry)->setText("Znovu");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Zrušit");
    //Normální tlačíka
    connect(ui->bookletButton, &QPushButton::clicked, this, &InsertWindow::bookletButtonClicked);
    //ButtoBox dialog tlačíka
    connect(ui->buttonBox->button(QDialogButtonBox::Ok),SIGNAL(clicked(bool)), this, SLOT(buttonBoxAccepted()));
    connect(ui->buttonBox->button(QDialogButtonBox::Retry),SIGNAL(clicked(bool)), this, SLOT(buttonBoxRetry()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel),SIGNAL(clicked(bool)), this, SLOT(buttonBoxRejected()));
    //Regex validátor roků
    QRegularExpression rx("[1-2][0-9][0-9][0-9]");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->yearLineEdit->setValidator(validator);
}

InsertWindow::~InsertWindow()
{
    delete ui;
}

//Tlačítko pro vybrání obrázku a zobrazení náhledu
void InsertWindow::bookletButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Vyberte obrázek"),"",tr("Obrázky (*.png *.jpg *.jpeg *.bmp)"));
    if(filename.isEmpty()){
        return;
    }else{
        QImage image;
        bool valid = image.load(filename);
        if(valid){
            ui->bookletLabel->setPixmap(QPixmap::fromImage(image));
        }
    }

}
//Tlačítko pro přidání záznamu
void InsertWindow::buttonBoxAccepted()
{
    QString author = ui->autorLineEdit->text();
    QString album = ui->albumLineEdit->text();
    QString year = ui->yearLineEdit->text();
    QString genre = ui->genreLineEdit->text();
    QString playlist = ui->playlistLineEdit->text();
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
    //Převod z labelu na obrázek a uložení do DB
    QPixmap inPixmap = ui->bookletLabel->pixmap();
    QPixmap afterScaled = inPixmap.scaled(QSize(80, 80),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QByteArray arr;
    QBuffer inBuffer(&arr);
    inBuffer.open( QIODevice::WriteOnly );
    afterScaled.save( &inBuffer,"BMP");

    pRecord = Record(author,album,year,genre,playlist,arr);
    accept();
}


void InsertWindow::buttonBoxRetry()
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
    //reject();
}
void InsertWindow::buttonBoxRejected()
{
    reject();
}
