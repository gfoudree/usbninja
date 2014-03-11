#include "daemonstatusdialog.h"
#include "ui_daemonstatusdialog.h"

DaemonStatusDialog::DaemonStatusDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DaemonStatusDialog)
{
    ui->setupUi(this);

    QStringList colTitles, data;
    colTitles << "Process Image" << "PID" << "Start Time";
    ui->treeWidget->setHeaderLabels(colTitles);

    wchar_t *szImg = L"notepad.exe";
    char cSzImg[25];
    wcstombs(cSzImg, szImg, sizeof(cSzImg));

    QString startTime = QString::fromStdString(procStartTime(getPid(szImg)));
    if (startTime.compare("") != 0)
    {
        data << cSzImg << QString::number(getPid(szImg)) << startTime;
        QTreeWidgetItem *it = new QTreeWidgetItem(data);
        ui->treeWidget->insertTopLevelItem(0 ,it);
        ui->label->setText(("RUNNING"));
        ui->label->setStyleSheet("QLabel {color: green; }");
    }
    else
    {
        ui->label->setText("STOPPED");
        ui->label->setStyleSheet("QLabel {color: red; }");
    }
}

DaemonStatusDialog::~DaemonStatusDialog()
{
    delete ui;
}


DWORD DaemonStatusDialog::getPid(wchar_t *szExe)
{
    HANDLE hProcSnap;
    PROCESSENTRY32 pe32;

    hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcSnap == INVALID_HANDLE_VALUE)
    {
         ErrorLog::logErrorToFile("*NORMAL*", "Unable to obtain process snapshot ", ErrorLog::winErrToStr(GetLastError()));
         CloseHandle(hProcSnap);
         return -1;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcSnap, &pe32))
    {
         ErrorLog::logErrorToFile("*NORMAL*", "Unable to obtain Process32First ", ErrorLog::winErrToStr(GetLastError()));
         CloseHandle(hProcSnap);
         return -1;
    }
    do
    {
        if (wcscmp(pe32.szExeFile, szExe) == 0)
        {
            CloseHandle(hProcSnap);
            return pe32.th32ProcessID;
        }
    }
    while (Process32Next(hProcSnap, &pe32));
    CloseHandle(hProcSnap);
    return -1;
}

std::string DaemonStatusDialog::procStartTime(DWORD pid)
{
    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
    if (hProc == INVALID_HANDLE_VALUE)
    {
        ErrorLog::logErrorToFile("*NORMAL*", "Unable to obtain process handle ", ErrorLog::winErrToStr(GetLastError()));
        return "";
    }
    FILETIME ft[4]; //createTime, exitTime, kernelTime, userTime
    if (!GetProcessTimes(hProc, &ft[0], &ft[1], &ft[2], &ft[3]))
    {
        ErrorLog::logErrorToFile("*NORMAL*", "Unable to obtain process times ", ErrorLog::winErrToStr(GetLastError()));
        return "";
    }
    SYSTEMTIME sysTime[4];

    for (int i = 0; i < 4; i++)
    {
        if (!FileTimeToSystemTime(&ft[i], &sysTime[i]))
        {
            ErrorLog::logErrorToFile("*NORMAL*", "Unable to convert time format ", ErrorLog::winErrToStr(GetLastError()));
            return "";
        }
    }

    std::stringstream ss;
    ss << sysTime[0].wMonth << "/" << sysTime[0].wDay << "/" << sysTime[0].wYear << "_";
    ss << sysTime[0].wHour << ":" << sysTime[0].wMinute << ":" << sysTime[0].wSecond;

    return ss.str();
}
