#include "cadastrarfuncionario.h"
#include "ui_cadastrarfuncionario.h"
#include "DatabaseManager.h"

CadastrarFuncionario::CadastrarFuncionario(QWidget *parent) // Construtor da classe CadastrarFuncionario
    : QDialog(parent)
    , ui(new Ui::CadastrarFuncionario) // Inicializa a interface gráfica
{
    ui->setupUi(this); // Configura a interface gráfica
}

CadastrarFuncionario::~CadastrarFuncionario()
{
    delete ui; // Libera a memória alocada para a interface gráfica
}

void CadastrarFuncionario::on_pushButton_RegisterEmployee_clicked()
{
    TypeUser typeUser; // Declara uma variável do tipo TypeUser
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text()   ;
    QString email = ui->lineEdit_email->text();

    bool verify_account = DatabaseManager::AlreadyHasAccount(email); // Verifica se já existe uma conta com o email fornecido

    if (verify_account == true){
        QMessageBox::warning(this, "Cadastro", "Email já cadastrado no sistema!");
    }
    else {
        DatabaseManager::createUser(email, username, password, typeUser.employee); // Cria um novo usuário no banco de dados
        QMessageBox::information(this, "Cadastro", "Funcionário cadastrado com sucesso");
        close(); // Fecha a janela de cadastro
    }
}
