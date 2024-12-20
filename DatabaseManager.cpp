#include "DatabaseManager.h"

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("application.db");
}

bool DatabaseManager::initialize() {
    if (!db.open()) {
        qDebug() << "Error: Cannot open database:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    QString createTableQuery =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "email TEXT UNIQUE, "
        "username TEXT, "
        "password TEXT, "
        "usertype TEXT)";
    if (!query.exec(createTableQuery)) {
        qDebug() << "Error creating table:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::isAdminRegistered() {
    QSqlQuery query("SELECT COUNT(*) FROM users WHERE usertype = 'admin'");
    if (query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

bool DatabaseManager::createUser(const QString& email, const QString& username, const QString& password, const QString& usertype) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (email, username, password, usertype) VALUES (:email, :username, :password, :usertype)");
    query.bindValue(":email", email);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":usertype", usertype);
    if (!query.exec()) {
        qDebug() << "Error inserting user:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::AlreadyHasAccount(QString email) {
    // Cria a consulta com um placeholder para o parâmetro
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :email");

    // Associa o valor ao placeholder
    query.bindValue(":email", email);

    // Executa a consulta
    if (query.exec() && query.next()) {
        // Retorna true se a contagem for maior que 0
        return query.value(0).toInt() > 0;
    }

    // Caso ocorra algum erro na execução
    return false;
}

bool DatabaseManager::HasEnoughQuantity(int Quantity, int id) {
    // Cria a consulta com um placeholder para o parâmetro
    QSqlQuery query;
    query.prepare("SELECT CASE WHEN quantidade >= :quantity THEN 0 ELSE 1 END AS resultado FROM entradas WHERE id = :id");

    // Associa o valor ao placeholder
    query.bindValue(":quantity", Quantity);
    query.bindValue(":id", id);

    // Executa a consulta
    if (query.exec() && query.next()) {
        // Retorna true se for 0
        return query.value(0).toInt() == 0;
    }

    // Caso ocorra algum erro na execução
    return false;
}
