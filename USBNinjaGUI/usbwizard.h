#ifndef USBWIZARD_H
#define USBWIZARD_H
#define _MEGABYTE 0x01
#define _GIGABYTE 0x02

#include <QWizard>
#include <QMessageBox>

#include "authdrive.h"
#include "../../USBNinjaDll/usbdevice.h"
#include "../../USBNinjaDll/usbkey.h"
#include "../../USBNinjaDll/usbbpb.h"

namespace Ui {
class USBWizard;
}

class USBWizard : public QWizard
{
    Q_OBJECT

public:
    explicit USBWizard(QWidget *parent = 0);
    ~USBWizard();

private slots:
    void on_USBWizard_currentIdChanged(int id);

private:
    Ui::USBWizard *ui;
    QString device;

    int convToGB(ULONGLONG *new_size, ULONGLONG orig_size);

    void setupFirstPage();
    void setupSecondPage();

};

#endif // USBWIZARD_H
