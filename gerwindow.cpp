#include "gerwindow.h"
#include "ui_gerwindow.h"
#include "cadastrarfuncionario.h"
#include "funcionarios.h"
#include "DatabaseManager.h"

GerWindow::GerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GerWindow)
{
    ui->setupUi(this);

    setupDatabase();
    loadDataFromDatabase();

    // Conectar botões do estoque
    connect(ui->addEntradaButton_2, &QPushButton::clicked, this, &GerWindow::handleAddEntrada);
    connect(ui->removeEntradaButton_2, &QPushButton::clicked, this, &GerWindow::handleRemoveEntrada);
    connect(ui->addSaidaButton_2, &QPushButton::clicked, this, &GerWindow::handleAddSaida);
    connect(ui->removeSaidaButton_2, &QPushButton::clicked, this, &GerWindow::handleRemoveSaida);
}

GerWindow::~GerWindow()
{
    delete ui;
}



void GerWindow::on_pushButton_ManageEmployee_clicked()
{
    Funcionarios Employees ;
    Employees.setModal(true);
    Employees.exec();
}


void GerWindow::on_estoqueButton_RegisterEmployee_clicked()
{
    CadastrarFuncionario RegisterEmployee;
    RegisterEmployee.setModal(true);
    RegisterEmployee.exec();
    QSqlQuery query;

}


void GerWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void GerWindow::on_homeButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Métodos para manipulação do estoque
void GerWindow::handleAddEntrada() {
    addItemToTreeWidget(ui->treeWidget_3, "Adicionar Entrada");
}

void GerWindow::handleAddSaida() {
    addItemToTreeWidget(ui->treeWidget_4, "Adicionar Saída");
}

void GerWindow::handleRemoveEntrada() {
    removeSelectedItemFromTreeWidget(ui->treeWidget_3);
}


void GerWindow::handleRemoveSaida() {
    removeSelectedItemFromTreeWidget(ui->treeWidget_4);
}

void GerWindow::setupDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE", "mainDBwin");
    db.setDatabaseName("estoque.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Erro", "Falha ao conectar ao banco de dados: " + db.lastError().text());
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS entradas ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "tamanho TEXT, "
               "estampa TEXT, "
               "quantidade INTEGER)");

    query.exec("CREATE TABLE IF NOT EXISTS saidas ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "tamanho TEXT, "
               "estampa TEXT, "
               "quantidade INTEGER)");
}

void GerWindow::loadDataFromDatabase() {
    QSqlQuery query;

    // Carregar Entradas
    query.exec("SELECT id, tamanho, estampa, quantidade FROM entradas");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString size = query.value(1).toString();
        QString pattern = query.value(2).toString();
        int quantity = query.value(3).toInt();

        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_3);
        item->setText(0, QString::number(id));
        item->setText(1, size);
        item->setText(2, pattern);
        item->setText(3, QString::number(quantity));
    }

    // Carregar Saídas
    query.exec("SELECT id, tamanho, estampa, quantidade FROM saidas");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString size = query.value(1).toString();
        QString pattern = query.value(2).toString();
        int quantity = query.value(3).toInt();

        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_4);
        item->setText(0, QString::number(id));
        item->setText(1, size);
        item->setText(2, pattern);
        item->setText(3, QString::number(quantity));
    }
}

void GerWindow::addItemToTreeWidget(QTreeWidget *treeWidget, const QString &title) {
    QString table = (treeWidget == ui->treeWidget_3) ? "entradas" : "saidas";
    QStringList sizeOptions = {"P", "M", "G"};
    QString size = QInputDialog::getItem(this, title, "Tamanho:", sizeOptions, 0, false);
    if (size.isEmpty()) return;

    QStringList patternOptions = {"Capitao-America", "Batman", "Boba-Fett", "Cell", "Coringa",
                                  "Darth-Vader", "Flash", "Goku", "Homem-Aranha", "Homem-de-ferro",
                                  "Hulk", "Kratos", "Lanterna-Verde", "Naruto", "Pantera-Negra",
                                  "Scorpion", "Sub-Zero", "Superman", "Thor"};
    QString pattern = QInputDialog::getItem(this, title, "Estampa:", patternOptions, 0, false);
    if (pattern.isEmpty()) return;

    int quantity = QInputDialog::getInt(this, title, "Quantidade:", 0, 0, 1000);
    if (quantity <= 0) {
        QMessageBox::warning(this, "Erro", "Quantidade inválida. Deve ser maior que 0.");
        return;
    }

    QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget);
    item->setText(1, size);
    item->setText(2, pattern);
    item->setText(3, QString::number(quantity));
    treeWidget->addTopLevelItem(item);

    addItemToDatabase(table, size, pattern, quantity);
}

void GerWindow::addItemToDatabase(const QString &table, const QString &size, const QString &pattern, int quantity) {
    QSqlQuery query;
    query.prepare(QString("INSERT INTO %1 (tamanho, estampa, quantidade) VALUES (:size, :pattern, :quantity)").arg(table));
    query.bindValue(":size", size);
    query.bindValue(":pattern", pattern);
    query.bindValue(":quantity", quantity);
    if (!query.exec()) {
        QMessageBox::critical(this, "Erro", "Erro ao inserir no banco de dados: " + query.lastError().text());
    }
}

void GerWindow::removeSelectedItemFromTreeWidget(QTreeWidget *treeWidget) {
    QTreeWidgetItem *item = treeWidget->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Erro", "Selecione um item para remover.");
        return;
    }

    QString table = (treeWidget == ui->treeWidget_3) ? "entradas" : "saidas";
    QString size = item->text(0);
    QString pattern = item->text(1);
    int quantity = item->text(2).toInt();

    removeItemFromDatabase(table, size, pattern, quantity);
    delete item;
}

void GerWindow::removeItemFromDatabase(const QString &table, const QString &size, const QString &pattern, int quantity) {
    QSqlQuery query;
    query.prepare(QString("DELETE FROM %1 WHERE tamanho = :size AND estampa = :pattern AND quantidade = :quantity").arg(table));
    query.bindValue(":size", size);
    query.bindValue(":pattern", pattern);
    query.bindValue(":quantity", quantity);
    if (!query.exec()) {
        QMessageBox::critical(this, "Erro", "Erro ao remover do banco de dados: " + query.lastError().text());
    }
}
