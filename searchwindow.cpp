#include "searchwindow.h"
#include "ui_searchwindow.h"
#include <QRegularExpressionValidator>
#include <QPushButton>
#include <QMessageBox>

SearchWindow::SearchWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    setWindowTitle("Vyhledávání CD nahrávky");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Vyhledat");
    ui->buttonBox->button(QDialogButtonBox::Retry)->setText("Znovu");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Zrušit");
    //ButtoBox dialog tlačíka
    connect(ui->buttonBox->button(QDialogButtonBox::Ok),SIGNAL(clicked(bool)), this, SLOT(buttonBoxAccepted()));
    connect(ui->buttonBox->button(QDialogButtonBox::Retry),SIGNAL(clicked(bool)), this, SLOT(buttonBoxRetry()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel),SIGNAL(clicked(bool)), this, SLOT(buttonBoxRejected()));
    //Regex validátor roků
    QRegularExpression rx("[1-2][0-9][0-9][0-9]");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->yearLineEdit->setValidator(validator);
}

SearchWindow::~SearchWindow()
{
    delete ui;
}


void SearchWindow::buttonBoxAccepted()
{
    QString author = ui->autorLineEdit->text();
    QString year = ui->yearLineEdit->text();
    QString genre = ui->genreLineEdit->text();

    pRecord = Record(author,year,genre);
    accept();
}
void SearchWindow::buttonBoxRetry()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Znovu", "Opravdu chcete všechna pole vymazat?",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        ui->autorLineEdit->clear();
        ui->yearLineEdit->clear();
        ui->genreLineEdit->clear();
    } else {
        return;
    }
    //reject();
}
void SearchWindow::buttonBoxRejected()
{
    reject();
}
