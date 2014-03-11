#ifndef DAEMONSTATUSDIALOG_H
#define DAEMONSTATUSDIALOG_H

#include <QDialog>
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <sstream>

#include "../../USBNinjaDll/errorlog.h"

namespace Ui {
class DaemonStatusDialog;
}

class DaemonStatusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DaemonStatusDialog(QWidget *parent = 0);
    static DWORD getPid(wchar_t *szExe);
    static std::string procStartTime(DWORD pid);

    ~DaemonStatusDialog();


private:
    Ui::DaemonStatusDialog *ui;
};

#endif // DAEMONSTATUSDIALOG_H
