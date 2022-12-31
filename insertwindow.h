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
private slots:;
    void bookletButtonClicked();
    void buttonBoxAccepted();
    void buttonBoxRejected();
    void buttonBoxRetry();
private:
    Ui::InsertWindow *ui;
    Record pRecord;
};

#endif // INSERTWINDOW_H
