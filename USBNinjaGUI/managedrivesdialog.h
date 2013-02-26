#ifndef MANAGEDRIVESDIALOG_H
#define MANAGEDRIVESDIALOG_H

#include <QDialog>
#include <QtGui>

#include <../../USBNinjaDll/sql.h>

namespace Ui {
class ManageDrivesDialog;
}

class ManageDrivesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ManageDrivesDialog(QWidget *parent = 0);
    ~ManageDrivesDialog();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::ManageDrivesDialog *ui;
};

#endif // MANAGEDRIVESDIALOG_H
