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

    QMenu *contextMenu = new QMenu(ui->treeWidget);
    ui->treeWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *deleteDrive = new QAction("Delete Device", contextMenu);
    ui->treeWidget->addAction(deleteDrive);

    connect(deleteDrive, SIGNAL(triggered()), this, SLOT(deleteDeviceHandler()));
}

ManageDrivesDialog::~ManageDrivesDialog()
{
    delete ui;
}

void ManageDrivesDialog::on_pushButton_clicked()
{
    done(0);
}

void ManageDrivesDialog::deleteDeviceHandler()
{
    QTreeWidgetItem *itm = ui->treeWidget->currentItem();
    int id = atoi(itm->text(0).toStdString().c_str());
    QMessageBox::information(this, "Test", QString::number(id));
}
