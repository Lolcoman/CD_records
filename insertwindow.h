#ifndef INSERTWINDOW_H
#define INSERTWINDOW_H

#include <QDialog>
#include "record.h"

namespace Ui {
class InsertWindow;
}

class InsertWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InsertWindow(QWidget *parent = nullptr);
    ~InsertWindow();
    Record record() const {return pRecord;}
    //DatabaseData sqlDatabase;
private slots:
    //void insertButtonClicked();
    void bookletButtonClicked();
    //void clearButtonClicked();
    void buttonBoxAccepted();
    void buttonBoxRejected();

private:
    Ui::InsertWindow *ui;
    Record pRecord;
};

#endif // INSERTWINDOW_H
