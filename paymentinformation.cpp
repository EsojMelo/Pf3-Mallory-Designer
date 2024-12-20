#include "paymentinformation.h"
#include "ui_paymentinformation.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QRegularExpression>

PaymentInformation::PaymentInformation(QWidget *parent)
    : QDialog(parent) // Construtor da classe, inicializa o QDialog com o caminho especificado
    , ui(new Ui::PaymentInformation) // Criação do objeto da interface gráfica
{
    ui->setupUi(this); // Configuração inicial da interface
}

PaymentInformation::~PaymentInformation()
{
    delete ui; // Libera a memória alocada para a interface
}

void PaymentInformation::setEstampa(const QString &estampa)
{
    ui->label_Estampa->setText(estampa); // Define o texto da estampa na interface
}

void PaymentInformation::on_pushButton_confirmpayment_clicked()
{
    QString estampa = ui->label_Estampa->text(); // Obtém o texto da estampa
    int quantidade = getQuantity(); // Obtém a quantidade de itens
    QString numeroCartao = ui->lineEdit_3->text();
    QString validade = ui->lineEdit_4->text();
    QString codigo = ui->lineEdit_5->text();
    QString nome = ui->lineEdit->text();
    QString endereco = ui->lineEdit_2->text();

    QSqlQuery query; // Objeto para executar consultas SQL
    QSqlQuery query_exit; // Objeto para gerenciar saídas no banco de dados
    query.prepare("UPDATE entradas SET quantidade = quantidade - :quantidade WHERE id = :id AND quantidade >= :quantidade");
    query.bindValue(":quantidade", quantidade); // Vincula o valor da quantidade estampa e ID do item
    query.bindValue(":estampa", estampa);
    query.bindValue(":id", itemId);


    // Verificar se todos os campos obrigatórios estão preenchidos
    if (nome.isEmpty() || endereco.isEmpty() || numeroCartao.isEmpty() || validade.isEmpty() || codigo.isEmpty()) {
        QMessageBox::warning(this, "Erro de Validação", "Todos os campos devem ser preenchidos.");
        return;
    }

    // Validar o número do cartão: apenas números
    static const QRegularExpression regexNumeros("\\d+");
    if (!regexNumeros.match(numeroCartao).hasMatch()) {
        QMessageBox::warning(this, "Erro de Validação", "O número do cartão deve conter apenas números.");
        return;
    }

    // Validar o formato da validade: MM/AAAA
    static const QRegularExpression regexValidade("^(0[1-9]|1[0-2])/\\d{4}$");
    if (!regexValidade.match(validade).hasMatch()) {
        QMessageBox::warning(this, "Erro de Validação", "A validade deve estar no formato MM/AAAA.");
        return;
    }

    // Validar o código de segurança: exatamente 3 dígitos
    static const QRegularExpression regexCodigo("^\\d{3}$");
    if (!regexCodigo.match(codigo).hasMatch()) {
        QMessageBox::warning(this, "Erro de Validação", "O código de segurança deve conter exatamente 3 dígitos.");
        return;
    }

    if (!query.exec()) { // Executa a consulta e verifica possíveis erros
        QMessageBox::critical(this, "Erro", "Erro ao atualizar o estoque: " + query.lastError().text());
        return; // Encerra a função
    }

    if (query.numRowsAffected() == 0) { // Verifica se a consulta atualizou alguma linha
        QMessageBox::warning(this, "Aviso", "Quantidade insuficiente em estoque ou estampa não encontrada!");
    } else {
        QMessageBox::information(this, "Sucesso", "Pagamento confirmado e estoque atualizado!");
        // Prepara a consulta para registrar a saída de itens
        query.prepare("INSERT INTO saidas (tamanho, estampa, quantidade) VALUES (:itemSize, :estampa, :quantidade)");
        query.bindValue(":itemSize", itemSize);
        query.bindValue(":quantidade", quantidade);
        query.bindValue(":estampa", estampa);
        if (!query.exec()) { // Executa a consulta e verifica possíveis erros
            QMessageBox::critical(this, "Erro", "Erro adicionar a saida: " + query.lastError().text());
            return; // Encerra a função
        }
    }

    close(); // Fecha a janela após concluir a operação
}

void PaymentInformation::setQuantity(int quantity) {
    ui->Label_quantity->setText(QString::number(quantity)); // Define o texto da quantidade na interface
}

int PaymentInformation::getQuantity() const {
    return ui->Label_quantity->text().toInt(); // Retorna o valor da quantidade como inteiro
}

void PaymentInformation::on_pushButton_2_clicked()
{
    close();
}

