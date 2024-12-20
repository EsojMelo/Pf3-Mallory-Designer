#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

using namespace std;


class TypeUser {
public:
    QString customer = "Cliente";
    QString admin = "Admin";
    QString employee = "Funcionario";
};

class DatabaseManager {
public:
    static DatabaseManager& instance();

    TypeUser typeUser;
    bool initialize();
    bool isAdminRegistered();
    static bool createUser(const QString& email, const QString& username, const QString& password, const QString& usertype);
    static bool AlreadyHasAccount(QString username);
    bool HasEnoughQuantity(int Quantity, int id);

private:
    DatabaseManager();
    QSqlDatabase db;
};


#endif // DATABASEMANAGER_H
