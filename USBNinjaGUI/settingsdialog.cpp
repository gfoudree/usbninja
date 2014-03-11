#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    int portVal;

    ConfigParser configParser((char*)Paths::getConfigPath().c_str());
    portVal = atoi((char*)configParser.getValue("port").c_str());

    ui->lineIP->setText(QString::fromStdString(configParser.getValue("ip")));
    ui->spinBoxPort->setValue(portVal);
    ui->lineUN->setText(QString::fromStdString(configParser.getValue("username")));
    ui->linePass->setText(QString::fromStdString(configParser.getValue("password")));
    ui->lineDB->setText(QString::fromStdString(configParser.getValue("database")));

    if (configParser.getValue("SQLenabled") == "1")
        ui->checkBoxSQL->setChecked(true);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_pushButton_clicked()
{
    ConfigParser configParser((char*)Paths::getConfigPath().c_str());

    std::ostringstream ostr;
    ostr << ui->spinBoxPort->value();

    configParser.setValue("port", ostr.str());
    configParser.setValue("username",  ui->lineUN->text().toStdString());
    configParser.setValue("password", ui->linePass->text().toStdString());
    configParser.setValue("database", ui->lineDB->text().toStdString());

    if (ui->checkBoxSQL->isChecked())
        configParser.setValue("SQLenabled", "1");
    else
        configParser.setValue("SQLenabled", "0");

    /* Verify IP is a valid IP */
    QRegExp ipChk(R"(^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$)");

    std::string ip = ui->lineIP->text().toStdString();
    if (ipChk.exactMatch(QString::fromStdString(ip)))
        configParser.setValue("ip", ui->lineIP->text().toStdString());
    else
        QMessageBox::information(this, "Error", "An invalid IP was entered, it will not be stored in the configuration file.");

    done(0);
}

void SettingsDialog::on_pushButton_2_clicked()
{
    done(0);
}
