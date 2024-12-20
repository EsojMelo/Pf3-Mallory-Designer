#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#include <QDialog>
#include <DatabaseManager.h>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Funcionarios;
}

class Funcionarios : public QDialog
{
    Q_OBJECT

public:
    explicit Funcionarios(QWidget *parent = nullptr);
    ~Funcionarios();

private:
    Ui::Funcionarios *ui;
    QSqlTableModel *model;
};

#endif // FUNCIONARIOS_H
