#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "severpage.h"
#include "playerpage.h"
#include "consolepage.h"
#include <QWidget>
#include <QPushButton>
#include <QProcess>
#include <QString>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
private slots:
    void runServer();
    void saveSettings();
    void stopServer();
    void serverStopped();
    void processOutput();
    void issueCommand(QString command);
private:
    ServerPage *serverPage;
    PlayerPage *playerPage;
    ConsolePage *consolePage;
    QPushButton *runButton;
    QPushButton *saveButton;
    QPushButton *stopButton;
    QProcess *serverProcess;
};

#endif // MAINWINDOW_H
