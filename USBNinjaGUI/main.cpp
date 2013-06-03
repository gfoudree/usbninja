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
 
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    SetLastError(0);
    CreateMutexA(0, FALSE, "Local\\$USBNINJA_GUI_MUTEX$");
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        exit(1);
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
