/*
 * Copyright (C) by Grant Foudree <grant907@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */
#include "logviewdialog.h"
#include "ui_logviewdialog.h"

LogviewDialog::LogviewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogviewDialog)
{
    ui->setupUi(this);

    QStringList columnTitles;
    columnTitles << "Date" << "Level" << "Info";
    ui->treeWidget->setHeaderLabels(columnTitles);

    refreshUI();

    QMenu *contextMenu = new QMenu(ui->treeWidget);
    ui->treeWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *deleteDrive = new QAction("Clear Log", contextMenu);
    ui->treeWidget->addAction(deleteDrive);

    connect(deleteDrive, SIGNAL(triggered()), this, SLOT(onClearLogfile()));
}

LogviewDialog::~LogviewDialog()
{
    delete ui;
}

void LogviewDialog::refreshUI()
{
    ui->treeWidget->clear();
    std::vector<logFileFormat> logFileData;
    parseLogFile(logFileData, ERR_LOG_FILE);

    /* Reverse elements so they are in proper order */
    std::reverse(logFileData.begin(), logFileData.end());

    for (std::vector<logFileFormat>::iterator it = logFileData.begin(); it != logFileData.end();
         it++)
    {
        QStringList itemData;
        itemData << it->date.c_str() << it->urgency.c_str() << it->info.c_str();

        QTreeWidgetItem *widgetItem = new QTreeWidgetItem(itemData);
        ui->treeWidget->insertTopLevelItem(0, widgetItem);
    }

    ui->treeWidget->resizeColumnToContents(1); //Clean things up...
}

bool LogviewDialog::parseLogFile(std::vector<logFileFormat> &data, char *filePath)
{
    /* Read the log data into a string */
    std::string logData;
    std::ifstream hFile(filePath);
    if (hFile.is_open())
    {
        while (hFile.good())
        {
            std::string tmp;
            std::getline(hFile, tmp);
            logData.append(tmp);
        }
        hFile.close();
    }
    else
    {
        return false;
    }

    /* Parse log file by lines (can't trust new line to work) */
    std::vector<std::string> lines;

    char *ln = strtok((char*)logData.c_str(), "[");
    while (ln != NULL)
    {
        std::string tmp = "[";
        tmp += ln;
        lines.push_back(tmp);
        ln = strtok(NULL, "[");
    }

    /* Use tokenizer to separate elements and place into struct */
    for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++)
    {
        logFileFormat lff;
        char *pch = strtok((char*)it->c_str(), "[ ]");
        if (pch != NULL)
            lff.date = pch;
        pch = strtok(NULL, " *");
        if (pch != NULL)
            lff.urgency = pch;
        pch = strtok(NULL, "*[");
        if (pch != NULL)
            lff.info = pch;
        data.push_back(lff);
    }
    return true;
}

void LogviewDialog::onClearLogfile()
{
    if (remove(ERR_LOG_FILE) != 0)
    {
        QMessageBox::critical(this, "Error", "Unable to delete the log file.");
    }
    else
    {
        refreshUI();
    }
}
