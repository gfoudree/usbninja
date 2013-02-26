#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <../../USBNinjaDll/sql.h>

#include "aboutdialog.h"
#include "managedrivesdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadData();
    void clearData();
    
private slots:
    void on_actionExit_triggered();

    void on_actionClear_Log_triggered();

    void on_actionAbout_triggered();

    void on_actionManage_Devices_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
