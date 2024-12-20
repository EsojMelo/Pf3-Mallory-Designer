#ifndef PAYMENTINFORMATION_H
#define PAYMENTINFORMATION_H

#include <QDialog>

namespace Ui {
class PaymentInformation;
}

class PaymentInformation : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentInformation(QWidget *parent = nullptr);
    void setEstampa(const QString &estampa);
    void setQuantity(int quantity);
    int getQuantity() const;
    ~PaymentInformation();
    void setId(int id) {
        itemId = id;
    }
    void getSize(QString size){
        itemSize = size;
    }

private slots:

    void on_pushButton_confirmpayment_clicked();

    void on_pushButton_2_clicked();

private:
    QString itemSize;
    int itemId;
    Ui::PaymentInformation *ui;

};

#endif // PAYMENTINFORMATION_H
