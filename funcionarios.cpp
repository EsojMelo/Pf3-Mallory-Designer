#include "funcionarios.h"
#include "ui_funcionarios.h"
#include <QSqlTableModel>
#include <QSqlQuery>
#include <DatabaseManager.h>

Funcionarios::Funcionarios(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Funcionarios)
    , model(new QSqlTableModel(this))
{
    ui->setupUi(this);
    TypeUser typeuser;
    model->setTable("users"); // Nome da tabela no banco
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setFilter("usertype = 'Funcionario'");
    model->select(); // Carrega os dados da tabela

    // Define nomes amigáveis para as colunas
    model->setHeaderData(1, Qt::Horizontal, "Email");
    model->setHeaderData(2, Qt::Horizontal, "Nome");
    model->setHeaderData(3, Qt::Horizontal, "Senha");
    model->setHeaderData(4, Qt::Horizontal, "Tipo");

    // Conecta o modelo ao QTableView
    ui->tableView->setModel(model);

    // Ajusta automaticamente o tamanho das colunas
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

Funcionarios::~Funcionarios()
{
    delete ui;
}

