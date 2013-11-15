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

void USBWizard::loadUsbInfo()
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

void USBWizard::on_comboBox_activated(const QString &arg1)
{
    if (arg1 == " ")
    {
        ui->labelFS->clear();
        ui->labelFSpace->clear();
        ui->labelLetter->clear();
        ui->labelTSpace->clear();
        ui->labelName->clear();
    }
    else
    {
        loadUsbInfo();
    }
}

void USBWizard::on_USBWizard_accepted()
{
    /* Signature:
     *
     * NINJA(serial)(crc32)
     */

    /* Get drive letter */

    char drvLtr = device.toStdString().at(0);

    /* Query drive information so we can log it... */
    DriveInfoS drvInfoS;
    UsbDevice::GetVolumeSize(drvLtr, (unsigned int *)&drvInfoS.diskSize);
    UsbDevice::GetVolumeLabel(drvLtr, &drvInfoS.driveName);
    UsbDevice::GetVolumeFilesystem(drvLtr, &drvInfoS.driveFilesystem);

    /* Setup buffer to write to BPB of device */
    char *buf;
    bool isFat32 = UsbBPB::isFat32(drvLtr);
    if (isFat32)
    {
        /* Device is FAT32 */
        buf = (char*)malloc(FAT32_BPB_BOOTCODE_LEN+1);
        memset(buf, 0, FAT32_BPB_BOOTCODE_LEN+1);
        isFat32 = true;
    }
    else
    {
        /* Assume it is FAT16 */
        buf = (char*)malloc(FAT16_BPB_BOOTCODE_LEN+1);
        memset(buf, 0, FAT16_BPB_BOOTCODE_LEN+1);
        isFat32 = false;
    }

    /* Generate serial key & format it to a buffer */
    UsbKey usbKey;
    UsbKeyhdr serialStamp;

    serialStamp.magic = "NINJA";
    serialStamp.serialkey = usbKey.generateRandStr(25);
    serialStamp.crc32 = usbKey.generateCrc32(
                (unsigned char*)serialStamp.serialkey.c_str(),
                serialStamp.serialkey.length());

    sprintf(buf, "%s%s%s", serialStamp.magic.c_str(), serialStamp.serialkey.c_str(),
            serialStamp.crc32.c_str());


    UsbBPB bpb;
    bpb.openDevice(drvLtr);
    if (isFat32)
    {
        if (!bpb.writeBPBCode32((unsigned char*)buf))
        {
            QMessageBox::critical(this, "Error", "There was an error writing the raw data to the "
                                  "usb disk, please make sure you have sufficient privileges then "
                                  "try again.");
            return;
        }
    }
    else
    {
        if (!bpb.writeBPBCode16((unsigned char*)buf))
        {
            QMessageBox::critical(this, "Error", "There was an error writing the raw data to the "
                                  "usb disk, please make sure you have sufficient privileges then "
                                  "try again.");
            return;
        }
    }

    /* Log authorized drive to the database */
    AuthDrive drv;

    drv.date = drv.dateAndTime();
    drv.serial = serialStamp.serialkey;

    if (strcmp(ui->plainTextEdit->toPlainText().toStdString().c_str(), "Add description here.") == 0)
        drv.notes = " ";
    else
        drv.notes = ui->plainTextEdit->toPlainText().toStdString();

    drv.driveName = drvInfoS.driveName;
    drv.driveSize = drvInfoS.diskSize;
    drv.logEntry();
}
