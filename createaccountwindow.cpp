#include "createaccountwindow.h"
#include "ui_createaccountwindow.h"
#include "DatabaseManager.h"

createaccountwindow::createaccountwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::createaccountwindow)
{
    ui->setupUi(this);
}

createaccountwindow::~createaccountwindow()
{
    delete ui;
}

void createaccountwindow::on_pushButton_CreatAccount_clicked()
{
    TypeUser typeUser;
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString email = ui->lineEdit_email->text();

    bool verify_account = DatabaseManager::AlreadyHasAccount(email);

    if (verify_account == true){
        QMessageBox::warning(this, "Cadastro", "Email já cadastrado no sistema!");
    }
    else {
        DatabaseManager::createUser(email, username, password, typeUser.customer);
        QMessageBox::information(this, "Cadastro", "Usuário cadastrado com sucesso");
        close();
    }
}

