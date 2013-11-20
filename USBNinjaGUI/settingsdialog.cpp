#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    int portVal;

    ConfigParser configParser("C:\\users\\grant\\desktop\\usbsninja.conf");
    portVal = atoi((char*)configParser.getValue("port").c_str());

    ui->lineIP->setText(QString::fromStdString(configParser.getValue("ip")));
    ui->spinBoxPort->setValue(portVal);
    ui->lineUN->setText(QString::fromStdString(configParser.getValue("username")));
    ui->linePass->setText(QString::fromStdString(configParser.getValue("password")));
    ui->lineDB->setText(QString::fromStdString(configParser.getValue("database")));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_pushButton_clicked()
{
    char portStr[10];
    itoa(ui->spinBoxPort->value(), portStr, 10);

    ConfigParser configParser("C:\\users\\grant\\desktop\\usbsninja.conf");
    configParser.setValue("ip", ui->lineIP->text().toStdString());
    configParser.setValue("port", portStr);
    configParser.setValue("username",  ui->lineUN->text().toStdString());
    configParser.setValue("password", ui->linePass->text().toStdString());
    configParser.setValue("database", ui->lineDB->text().toStdString());

    done(0);
}

void SettingsDialog::on_pushButton_2_clicked()
{
    done(0);
}
