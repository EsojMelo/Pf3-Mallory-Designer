#ifndef PURCHASEDIALOG_H
#define PURCHASEDIALOG_H

#include <QDialog>

namespace Ui {
class PurchaseDialog;
}

class PurchaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PurchaseDialog(QWidget *parent = nullptr);
    ~PurchaseDialog();
    void getId(const QString &id);
    void setEstampa(const QString &estampa); // Atualizar o label com a estampa
    void setTamanho(const QString &tamanho); // Atualizar o label com o tamanho
    int getQuantity() const;
    void setId(int id) {
        itemId = id;
    }


private slots:

    void on_pushButton_Cancel_clicked();

    void on_pushButton_Confirm_clicked();

private:
    Ui::PurchaseDialog *ui;
    int itemId;
    QString itemSize;
    QString itemParttern;
    int itemQuan;
};

#endif // PURCHASEDIALOG_H
