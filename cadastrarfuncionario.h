#ifndef CADASTRARFUNCIONARIO_H
#define CADASTRARFUNCIONARIO_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class CadastrarFuncionario;
}

class CadastrarFuncionario : public QDialog
{
    Q_OBJECT

public:
    explicit CadastrarFuncionario(QWidget *parent = nullptr);
    ~CadastrarFuncionario();

private slots:
    void on_pushButton_RegisterEmployee_clicked();

private:
    Ui::CadastrarFuncionario *ui;
};

#endif // CADASTRARFUNCIONARIO_H
