#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <mainwin.hpp>


namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_Login_clicked();

    void on_pushButton_CreateAccount_clicked();

    void on_pushButton_Debug_clicked();

private:
    Ui::LoginWindow *ui;
    MainWindow *mainWindow;
};

#endif // LOGINWINDOW_H
