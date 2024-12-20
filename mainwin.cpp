/***************************************************************************
 *   mainwin.cpp                              Version 20230621.000147      *
 *                                                                         *
 *   Brief description                                                     *
 *   Copyright (C) 2023         by Ruben Carlo Benante                     *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License.               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *   To contact the author, please write to:                               *
 *   Ruben Carlo Benante                                                   *
 *   Email: rcb@beco.cc                                                    *
 *   Webpage: http://www.beco.cc                                           *
 *   Phone: +55 (81) 3184-7555                                             *
 ***************************************************************************/

/* ---------------------------------------------------------------------- */
/* includes */
/* #include <iostream> */ /* (Input/output library) Several standard stream objects */
/* using namespace std; */
/* #include <cstdio> */ /* (Input/output library) C-style input-output functions */
/* #include <fstream> */ /* (Input/output library) std::basic_fstream, std::basic_ifstream, std::basic_ofstream class templates and several typedefs */
/* #include <iomanip> */ /* (Input/output library) Helper functions to control the format of input and output */
/* #include <ios> */ /* (Input/output library) std::ios_base class, std::basic_ios class template and several typedefs */
/* #include <iosfwd> */ /* (Input/output library) Forward declarations of all classes in the input/output library */
/* #include <istream> */ /* (Input/output library) std::basic_istream class template and several typedefs */
/* #include <ostream> */ /* (Input/output library) std::basic_ostream, std::basic_iostream class templates and several typedefs */
/* #include <spanstream> */ /* (C++23, Input/output library) std::basic_spanstream, std::basic_ispanstream, std::basic_ospanstream class templates and typedefs */
/* #include <sstream> */ /* (Input/output library) std::basic_stringstream, std::basic_istringstream, std::basic_ostringstream class templates and several typedefs */
/* #include <streambuf> */ /* (Input/output library) std::basic_streambuf class template */
/* #include <strstream> */ /* (deprecated in C++98, Input/output library) std::strstream, std::istrstream, std::ostrstream */
/* #include <syncstream> */ /* (C++20, Input/output library) std::basic_osyncstream, std::basic_syncbuf, and typedefs */

/* #include "libuser.hpp" */ /* your personal user library together with libuser.cpp */

#include "mainwin.hpp" /* To be created for this template if needed */
#include <QtSql>


/* ---------------------------------------------------------------------- */
/* methods */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setupDatabase();
    loadDataFromDatabase();

    connect(ui->homeButton, &QPushButton::clicked, this, &MainWindow::navigateToHome);
    connect(ui->estoqueButton, &QPushButton::clicked, this, &MainWindow::navigateToEstoque);

    connect(ui->addEntradaButton, &QPushButton::clicked, this, &MainWindow::handleAddEntrada);
    connect(ui->addSaidaButton, &QPushButton::clicked, this, &MainWindow::handleAddSaida);
    connect(ui->removeEntradaButton, &QPushButton::clicked, this, &MainWindow::handleRemoveEntrada);
    connect(ui->removeSaidaButton, &QPushButton::clicked, this, &MainWindow::handleRemoveSaida);
}


MainWindow::~MainWindow() {
    delete ui;
}

// Métodos para navegação
void MainWindow::navigateToHome() {
    ui->stackedWidget->setCurrentIndex(0); // Página 1
}

void MainWindow::navigateToEstoque() {
    ui->stackedWidget->setCurrentIndex(1); // Página 2
}

// Métodos para manipulação do estoque
void MainWindow::handleAddEntrada() {
    addItemToTreeWidget(ui->treeWidget, "Adicionar Entrada");
}

void MainWindow::handleAddSaida() {
    addItemToTreeWidget(ui->treeWidget_2, "Adicionar Saída");
}

void MainWindow::handleRemoveEntrada() {
    removeSelectedItemFromTreeWidget(ui->treeWidget);
}

void MainWindow::handleRemoveSaida() {
    removeSelectedItemFromTreeWidget(ui->treeWidget_2);
}

void MainWindow::setupDatabase() {
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

void MainWindow::loadDataFromDatabase() {
    QSqlQuery query;

    // Carregar Entradas
    query.exec("SELECT id, tamanho, estampa, quantidade FROM entradas");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString size = query.value(1).toString();
        QString pattern = query.value(2).toString();
        int quantity = query.value(3).toInt();

        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
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

        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_2);
        item->setText(0, QString::number(id));
        item->setText(1, size);
        item->setText(2, pattern);
        item->setText(3, QString::number(quantity));
    }
}

void MainWindow::addItemToTreeWidget(QTreeWidget *treeWidget, const QString &title) {
    QString table = (treeWidget == ui->treeWidget) ? "entradas" : "saidas";
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
    if (quantity <= 0) return;

    QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget);
    item->setText(1, size);
    item->setText(2, pattern);
    item->setText(3, QString::number(quantity));
    treeWidget->addTopLevelItem(item);

    addItemToDatabase(table, size, pattern, quantity);
}

void MainWindow::addItemToDatabase(const QString &table, const QString &size, const QString &pattern, int quantity) {
    QSqlQuery query;
    query.prepare(QString("INSERT INTO %1 (tamanho, estampa, quantidade) VALUES (:size, :pattern, :quantity)").arg(table));
    query.bindValue(":size", size);
    query.bindValue(":pattern", pattern);
    query.bindValue(":quantity", quantity);
    if (!query.exec()) {
        QMessageBox::critical(this, "Erro", "Erro ao inserir no banco de dados: " + query.lastError().text());
    }
}

void MainWindow::removeSelectedItemFromTreeWidget(QTreeWidget *treeWidget) {
    QTreeWidgetItem *item = treeWidget->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Erro", "Selecione um item para remover.");
        return;
    }

    QString table = (treeWidget == ui->treeWidget) ? "entradas" : "saidas";
    QString size = item->text(0);
    QString pattern = item->text(1);
    int quantity = item->text(2).toInt();

    removeItemFromDatabase(table, size, pattern, quantity);
    delete item;
}

void MainWindow::removeItemFromDatabase(const QString &table, const QString &size, const QString &pattern, int quantity) {
    QSqlQuery query;
    query.prepare(QString("DELETE FROM %1 WHERE tamanho = :size AND estampa = :pattern AND quantidade = :quantity").arg(table));
    query.bindValue(":size", size);
    query.bindValue(":pattern", pattern);
    query.bindValue(":quantity", quantity);
    if (!query.exec()) {
        QMessageBox::critical(this, "Erro", "Erro ao remover do banco de dados: " + query.lastError().text());
    }
}


/* add more methods here */

/* ---------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : CPP config - Vim modeline */
/* Template by Dr. Beco <rcb at beco dot cc> Version 20220718.172615      */


