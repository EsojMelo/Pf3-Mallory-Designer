#include "purchasedialog.h"
#include "ui_purchasedialog.h"
#include "paymentinformation.h"
#include "DatabaseManager.h"
#include <QMessageBox>

PurchaseDialog::PurchaseDialog(QWidget *parent)
    : QDialog(parent) // Construtor da classe, inicializa o QDialog com o pai especificado
    , ui(new Ui::PurchaseDialog)
{
    ui->setupUi(this); // Configuração inicial da interface
}

PurchaseDialog::~PurchaseDialog()
{
    delete ui; // Libera a memória alocada para a interface
}

void PurchaseDialog::setEstampa(const QString &estampa)
{
    ui->label_tshirt->setText("Estampa: " + estampa); // Define o texto da estampa na interface
    itemParttern = estampa; // Armazena a estampa no membro da classe
}

void PurchaseDialog::setTamanho(const QString &tamanho)
{
    ui->label_tshirt->setText(ui->label_tshirt->text() + "\nTamanho: " + tamanho); // Adiciona o tamanho ao texto da interface
    itemSize = tamanho; // Armazena o tamanho no membro da classe
}

int PurchaseDialog::getQuantity() const
{
    return ui->spinBox_quanity->value(); // Retorna o valor selecionado no spinBox da quantidade
}

void PurchaseDialog::on_pushButton_Cancel_clicked()
{
    close(); // Fecha a janela atual ao cancelar a compra
}


void PurchaseDialog::on_pushButton_Confirm_clicked()
{
    DatabaseManager DbManager = DatabaseManager::instance();
    if (DbManager.HasEnoughQuantity(getQuantity(), itemId) == true){
        PaymentInformation paymentScreen; // Criação da janela de informações de pagamento
        paymentScreen.setEstampa(itemParttern);
        paymentScreen.setQuantity(getQuantity()); // Define a quantidade na tela de pagamento
        paymentScreen.getSize(itemSize);
        paymentScreen.setId(itemId); // Define o ID do item na tela de pagamento
        paymentScreen.setModal(true);
        paymentScreen.exec(); // Exibe a janela de pagamento e aguarda sua conclusão
        close();
    }
    else
    {
        QMessageBox::warning(this, "Aviso", "Quantidade insuficiente em estoque ou estampa não encontrada!");
    }
}
