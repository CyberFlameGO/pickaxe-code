/*********************************
 * Application: PickAxe          *
 * File: main.cpp                *
 * Last Edited: 5/11/11          *
 * Author: Xapphire13            *
 * Contact: xapphire13@gmail.com *
 *********************************/
#include <QApplication>
#include "mainwindow.h"
#include <QDir>
#include <QMessageBox>
#include <QString>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow mainWindow;

    //Make program path
    QDir *path = new QDir;
    if(!path->exists(QDir::homePath() + "/.pickaxe")) {
        if(!path->mkpath(QDir::homePath() + "/.pickaxe")) {
            QMessageBox *errorBox = new QMessageBox(QMessageBox::Critical, "Fatal Error", "Couldn't create working directory");
            errorBox->exec();
            return 0;
        }
    }

    mainWindow.show();
    app.exec();
    return 0;
}
