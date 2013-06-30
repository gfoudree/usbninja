#ifndef LOGVIEWDIALOG_H
#define LOGVIEWDIALOG_H

#include <QDialog>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>

struct logFileFormat;

namespace Ui {
class LogviewDialog;
}

class LogviewDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LogviewDialog(QWidget *parent = 0);
    ~LogviewDialog();
    
private:
    bool parseLogFile(std::vector<logFileFormat> &data,  char *filePath);
    Ui::LogviewDialog *ui;
};


struct logFileFormat
{
    std::string date;
    std::string urgency;
    std::string info;
};

#endif // LOGVIEWDIALOG_H
