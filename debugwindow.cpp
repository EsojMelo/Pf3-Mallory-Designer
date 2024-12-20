#include "debugwindow.h"
#include "ui_debugwindow.h"
#include "clientwindow.h"
#include "mainwin.hpp"
#include "gerwindow.h"

DebugWindow::DebugWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DebugWindow)
{
    ui->setupUi(this);
}

DebugWindow::~DebugWindow()
{
    delete ui;
}

void DebugWindow::on_Confirmar_clicked()
{
    int index = ui->comboBox->currentIndex();
    if (index == 1) {
        ClientWindow *clientWindow = new ClientWindow(this);
        clientWindow->show();
    } else if (index == 3) {
        MainWindow *mainWindow = new MainWindow(this);
        mainWindow->show();
    } else if (index == 2) {
       GerWindow *gerWindow = new GerWindow(this);
       gerWindow->show();
    }
}
