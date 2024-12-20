#ifndef CREATEACCOUNTWINDOW_H
#define CREATEACCOUNTWINDOW_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class createaccountwindow;
}

class createaccountwindow : public QDialog
{
    Q_OBJECT

public:
    explicit createaccountwindow(QWidget *parent = nullptr);
    ~createaccountwindow();

private slots:

    void on_pushButton_CreatAccount_clicked();

private:
    Ui::createaccountwindow *ui;
};

#endif // CREATEACCOUNTWINDOW_H
