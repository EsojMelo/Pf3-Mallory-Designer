#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "DatabaseManager.h"
#include <QInputDialog>
#include <QMessageBox>
#include "debugwindow.h"
#include "createaccountwindow.h"
#include "clientwindow.h"
#include "mainwin.hpp"
#include "gerwindow.h"

// Construtor da classe LoginWindow
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow) {
    ui->setupUi(this); // Configura a interface grafica

    // Inicializar banco de dados
    if (!DatabaseManager::instance().initialize()) {
        QMessageBox::critical(this, "Erro", "Não foi possível inicializar o banco de dados.");
        close();
        return;
    }

    // Verificar se o administrador está cadastrado
    if (!DatabaseManager::instance().isAdminRegistered()) {
        QMessageBox::information(this, "Configuração Inicial", "Vamos configurar o administrador.");
        QString email = QInputDialog::getText(this, "Cadastro do Admin", "Email:");
        QString username = QInputDialog::getText(this, "Cadastro do Admin", "Username:");
        QString password = QInputDialog::getText(this, "Cadastro do Admin", "Password:");

        if (!DatabaseManager::instance().createUser(email, username, password, "admin")) {
            QMessageBox::critical(this, "Erro", "Erro ao criar administrador.");
            close();
        } else {
            QMessageBox::information(this, "Sucesso", "Administrador cadastrado com sucesso!");
        }
    }
}

// Função chamada ao clicar no botao de login
void LoginWindow::on_pushButton_Login_clicked() {
    QString username = ui->lineEdit_Username->text();
    QString password = ui->lineEdit_Password->text();

    QSqlQuery query;
    query.prepare("SELECT usertype FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

        if (query.exec() && query.next()) {
            QString userType = query.value(0).toString();

            QMessageBox::information(this, "Login", "Bem-vindo, " + userType + "!");

            QMainWindow *nextWindow = nullptr;

            if (userType == "admin") {
                nextWindow = new GerWindow(); // Criar a janela do administrador
            } else if (userType == "Funcionario") {
                nextWindow = new MainWindow(); // Criar a janela do funcionário
            } else if (userType == "Cliente") {
                nextWindow = new ClientWindow(); // Criar a janela do cliente
            } else {
                QMessageBox::warning(this, "Erro", "Tipo de usuário desconhecido.");
                return;
            }

            nextWindow->show(); // Mostrar a próxima janela
            this->close();      // Fechar a janela de login

        } else {
            QMessageBox::warning(this, "Erro", "Usuário ou senha incorretos.");
        }
    }




LoginWindow::~LoginWindow() {
    delete ui; // Libera a memoria da interface
}

// logica para criação de uma nova janela de criar conta
void LoginWindow::on_pushButton_CreateAccount_clicked()
{
    createaccountwindow creatAccWin; // Cria uma nova janela de criar conta
    creatAccWin.setModal(true);
    creatAccWin.exec(); // Executa a janela
}

// Logica usada ao clicar no botao de debug
void LoginWindow::on_pushButton_Debug_clicked()
{
    DebugWindow debugWin; // Cria uma nova janela de debug
    debugWin.setModal(true);
    debugWin.exec(); // Executa a janela
}

