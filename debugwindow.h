#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QDialog>

namespace Ui {
class DebugWindow;
}

class DebugWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DebugWindow(QWidget *parent = nullptr);
    ~DebugWindow();

private slots:
    void on_Confirmar_clicked();

private:
    Ui::DebugWindow *ui;
};

#endif // DEBUGWINDOW_H
