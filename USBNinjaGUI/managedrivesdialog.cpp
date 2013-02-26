#include "managedrivesdialog.h"
#include "ui_managedrivesdialog.h"

ManageDrivesDialog::ManageDrivesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageDrivesDialog)
{
    ui->setupUi(this);

    QStringList columnTitles;
    columnTitles << "ID" << "Date Authorized" << "USBNinja Serial" << "Name" << "Size";
    ui->treeWidget->setHeaderLabels(columnTitles);
    ui->treeWidget->setColumnWidth(0, 40);

    std::vector<authedDrive> authedDrv;
    Sql sql;
    sql.dbConnect("C:\\users\\grant\\desktop\\log.db");
    sql.queryAuthedDrives(&authedDrv);
    sql.dbDisconnect();

    for (int i = authedDrv.size(), element = 0; i != 0; i--, element++)
    {
        QStringList data;
        data << QString::number(i) << authedDrv.at(element).dateAuthorized.c_str();
        data << authedDrv.at(element).serial.c_str() << authedDrv.at(element).driveName.c_str();
        data << QString::number(authedDrv.at(element).driveSize);

        QTreeWidgetItem *itm = new QTreeWidgetItem(data);
        ui->treeWidget->insertTopLevelItem(0, itm);
    }
    ui->treeWidget->resizeColumnToContents(2);
}

ManageDrivesDialog::~ManageDrivesDialog()
{
    delete ui;
}

void ManageDrivesDialog::on_pushButton_clicked()
{
    done(0);
}
