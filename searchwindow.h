#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include "record.h"
#include <QDialog>

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();
    Record record() const {return pRecord;}
private slots:
    void buttonBoxAccepted();
    void buttonBoxRejected();
    void buttonBoxRetry();
private:
    Ui::SearchWindow *ui;
    Record pRecord;
};

#endif // SEARCHWINDOW_H
