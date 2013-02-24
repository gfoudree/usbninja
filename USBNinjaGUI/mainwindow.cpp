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

    std::vector<logUSB> usb;
    Sql sql;
    sql.dbConnect("C:\\users\\grant\\desktop\\log.db");
    sql.queryLog(&usb);

    for (int i = usb.size(), element = 0; i != 0; i--, element++)
    {
        QStringList parentData, childData;
        parentData << QString::number(i) << "REJECTED" << usb.at(element).date.c_str();
        parentData << usb.at(element).user.c_str() << usb.at(element).driveLabel.c_str();
        parentData << usb.at(element).driveName.c_str() << QString::number(usb.at(element).driveSize) + " MB";

        childData << "FF" << "TT"; //Try inserting a line edit or label here so you can make a header
        QTreeWidgetItem *parentItm = new QTreeWidgetItem(parentData);
        QTreeWidgetItem *childItm = new QTreeWidgetItem(childData);
        parentItm->addChild(childItm);
        ui->treeWidget->insertTopLevelItem(0, parentItm);
    }
    ui->treeWidget->setColumnWidth(0, 40);
    ui->treeWidget->resizeColumnToContents(2);
    ui->treeWidget->resizeColumnToContents(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}
