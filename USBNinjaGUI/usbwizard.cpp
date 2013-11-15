#include "usbwizard.h"
#include "ui_usbwizard.h"

USBWizard::USBWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::USBWizard)
{
    //Setup background
    setPixmap(QWizard::BackgroundPixmap, QPixmap(":/new/prefix1/resources/background.png"));
    ui->setupUi(this);

    setupFirstPage();
}

USBWizard::~USBWizard()
{
    delete ui;
}

void USBWizard::setupFirstPage()
{
    //Load available drives
    ui->comboBox->addItem(" ");
    DWORD numDrives;
    std::vector<char> usbDrives = UsbDevice::getUSBDrives(&numDrives);
    int i = 0;
    for (std::vector<char>::const_iterator itt = usbDrives.begin(); i < numDrives; std::advance(itt, 4), i++)
    {
        if ((*itt != '\0') && (*itt != 'C'))
        {
            UINT drvFilter = GetDriveTypeA(UsbDevice::ltrtstr(*itt).c_str());
            if ((drvFilter == DRIVE_REMOVABLE) || (drvFilter == DRIVE_FIXED))
            {
                std::string fs;
                UsbDevice::GetVolumeFilesystem(*itt, &fs);
                if ((strcmp(fs.c_str(), "FAT32") == 0) || (strcmp(fs.c_str(), "FAT16") == 0))
                    ui->comboBox->addItem(QString(*itt) + ":\\");
            }
        }
    }
}

void USBWizard::setupSecondPage()
{
    DriveInfo drvInfo;
    device = ui->comboBox->currentText();

    if (UsbDevice::getDriveInfo(&drvInfo, device.toStdString()))
    {
        ui->labelLetter->setText(device);
        ui->labelName->setText(QString(drvInfo.devName));
        ui->labelFS->setText(QString(drvInfo.devFs));

        ULONGLONG freeSpace, totalSpace;
        if (convToGB(&freeSpace, drvInfo.fSpace) == _GIGABYTE)
            ui->labelFSpace->setText(QString("%1 %2").arg(QString::number(freeSpace)).arg(QString("GB")));
        else
            ui->labelFSpace->setText(QString("%1 %2").arg(QString::number(freeSpace)).arg(QString("MB")));
        if (convToGB(&totalSpace, drvInfo.tSpace) == _GIGABYTE)
            ui->labelTSpace->setText(QString("%1 %2").arg(QString::number(totalSpace)).arg(QString("GB")));
        else
            ui->labelTSpace->setText(QString("%1 %2").arg(QString::number(totalSpace)).arg(QString("MB")));
    }
}

void USBWizard::on_USBWizard_currentIdChanged(int id)
{
    switch (id)
    {
        case 1:
        {
            if (ui->comboBox->currentText() == " ")
            {
                this->restart();
                QMessageBox::critical(this, "Error", "Please select a valid device first");
            }
            else
            {
                setupSecondPage();
            }
        }
        break;
    }
}

int USBWizard::convToGB(ULONGLONG *new_size, ULONGLONG orig_size)
{
    if ((orig_size >> 20) > 1024)
    {
        *new_size = (orig_size >> 30);
        return _GIGABYTE;
    }
    else
    {
        *new_size = (orig_size >> 20);
        return _MEGABYTE;
    }
}
