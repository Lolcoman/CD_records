#ifndef INSERTWINDOW_H
#define INSERTWINDOW_H

#include <QDialog>

namespace Ui {
class InsertWindow;
}

class InsertWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InsertWindow(QWidget *parent = nullptr);
    ~InsertWindow();
private slots:
    void insertButtonClicked();
    void bookletButtonClicked();
    void clearButtonClicked();
private:
    Ui::InsertWindow *ui;
};

#endif // INSERTWINDOW_H
