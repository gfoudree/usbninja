#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList columnTitles;
    columnTitles << "ID" << "Action" << "Date" << "User" << "Label" << "Manufacturer" << "Size";
    ui->treeWidget->setHeaderLabels(columnTitles);

    loadData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearData()
{
    ui->treeWidget->clear();
}

void MainWindow::loadData()
{
    std::vector<logUSB> usb;
    Sql sql;
    sql.dbConnect("C:\\users\\grant\\desktop\\log.db");
    sql.queryLog(&usb);
    sql.dbDisconnect();

    for (int i = usb.size(), element = 0; i != 0; i--, element++)
    {
        QStringList parentData, childData, childHeader;
        parentData << QString::number(i) << "REJECTED" << usb.at(element).date.c_str();
        parentData << usb.at(element).user.c_str() << usb.at(element).driveLabel.c_str();
        parentData << usb.at(element).driveName.c_str() << QString::number(usb.at(element).driveSize) + " MB";

        childHeader << "" << "Drive Letter" << "Serial" << "GUID" << "USBNinja Serial";

        childData << "" << QString(usb.at(element).driveLetter) << usb.at(element).driveSerial.c_str();
        childData << usb.at(element).driveGUID.c_str() << usb.at(element).usbninjaSerial.c_str();

        QTreeWidgetItem *parentItm = new QTreeWidgetItem(parentData);
        QTreeWidgetItem *childItmHeader = new QTreeWidgetItem(childHeader);
        QTreeWidgetItem *childItm = new QTreeWidgetItem(childData);

        for (int i = 0; i < childItmHeader->columnCount(); i++)
            childItmHeader->setForeground(i, Qt::lightGray);

        parentItm->addChild(childItmHeader);
        parentItm->addChild(childItm);
        ui->treeWidget->insertTopLevelItem(0, parentItm);
    }
    ui->treeWidget->setColumnWidth(0, 40);
    ui->treeWidget->resizeColumnToContents(2);
    ui->treeWidget->resizeColumnToContents(5);
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionClear_Log_triggered()
{
    clearData();
    loadData();
}
