#ifndef UPDATEWINDOW_H
#define UPDATEWINDOW_H

#include "record.h"
#include <QDialog>

namespace Ui {
class updatewindow;
}

class updatewindow : public QDialog
{
    Q_OBJECT

public:
    explicit updatewindow(QWidget *parent = nullptr);
    ~updatewindow();
    Record record() const {return pRecord;}
private slots:;
    void bookletButtonClicked();
    void buttonBoxAccepted();
    void buttonBoxRejected();
    void buttonBoxRetry();
private:
    Ui::updatewindow *ui;
    Record pRecord;
};

#endif // UPDATEWINDOW_H
