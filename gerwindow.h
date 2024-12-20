#ifndef GERWINDOW_H
#define GERWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
class GerWindow;
}

class GerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GerWindow(QWidget *parent = nullptr);
    ~GerWindow();

private slots:

    void on_pushButton_ManageEmployee_clicked();

    void on_estoqueButton_RegisterEmployee_clicked();

    void on_pushButton_2_clicked();

    void on_homeButton_2_clicked();

    void handleAddEntrada();
    void handleRemoveEntrada();
    void handleAddSaida();
    void handleRemoveSaida();

private:
    Ui::GerWindow *ui;
    QSqlDatabase db;

    void setupDatabase();
    void loadDataFromDatabase();
    void addItemToTreeWidget(QTreeWidget *treeWidget, const QString &title);
    void addItemToDatabase(const QString &table, const QString &size, const QString &pattern, int quantity);
    void removeSelectedItemFromTreeWidget(QTreeWidget *treeWidget);
    void removeItemFromDatabase(const QString &table, const QString &size, const QString &pattern, int quantity);
};

#endif // GERWINDOW_H
