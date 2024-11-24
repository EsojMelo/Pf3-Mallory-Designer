#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <mainwin.hpp>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_Username->text();
    QString password = ui->lineEdit_Password->text();

    if (username == "test" && password == "test")
    {
        QMessageBox::information(this, "Login", "Username and login is Correct");
        hide();
        mainWindow = new MainWindow(this);
        mainWindow->show();
    }
    else
    {
        QMessageBox::warning(this, "Login", "Username or Password is incorrect");
    }
}


void LoginWindow::on_pushButton_2_clicked()
{

}

