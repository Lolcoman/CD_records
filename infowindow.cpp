#include "infowindow.h"
#include "qpushbutton.h"
#include "ui_infowindow.h"

InfoWindow::InfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
    setWindowTitle("Info o aplikaci");
    ui->buttonBox->button(QDialogButtonBox::Close)->setText("Zavřít");
}

InfoWindow::~InfoWindow()
{
    delete ui;
}
