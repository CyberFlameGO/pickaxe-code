#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QStringList>
#include <QTabWidget>
#include <QTextStream>
#include <QIcon>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent) {
    serverPage = new ServerPage;
    playerPage = new PlayerPage;
    consolePage = new ConsolePage(this);
    connect(consolePage, SIGNAL(sendCommand(QString)), this, SLOT(issueCommand(QString)));
    QTabWidget *mainTabWidget = new QTabWidget();
    mainTabWidget->addTab(serverPage, tr("Server Settings"));
    mainTabWidget->addTab(playerPage, tr("Player Settings"));
    mainTabWidget->addTab(consolePage, tr("Console"));

    runButton = new QPushButton("Run!");
    connect(runButton, SIGNAL(clicked()), this, SLOT(runServer()));

    saveButton = new QPushButton("Save Settings");
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveSettings()));

    stopButton = new QPushButton("Stop");
    stopButton->setEnabled(false);
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopServer()));

    serverProcess = new QProcess;
    serverProcess->setProcessChannelMode(QProcess::MergedChannels);
    serverProcess->setWorkingDirectory(QDir::homePath() + "/.pickaxe");
    connect(serverProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()));
    connect(serverProcess, SIGNAL(finished(int)), this, SLOT(serverStopped()));


    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->addWidget(mainTabWidget);
    layout->addWidget(runButton);
    layout->addWidget(saveButton);
    layout->addWidget(stopButton);

    setLayout(layout);
    setWindowTitle(tr("PickAxe"));
    setWindowIcon(QIcon(":/images/icon.png"));
}

void MainWindow::runServer() {
    saveSettings();
    serverProcess->start("java", QStringList() << "-jar" << (QString() + "-Xms" + QString::number(serverPage->getRam()) + "m") << (QString() + "-Xmx" + QString::number(serverPage->getRam()) + "m") << serverPage->getServerPath() << "nogui");
    if(!serverProcess->waitForStarted()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to execute server"));
    } else {
        runButton->setEnabled(false);
        stopButton->setEnabled(true);
    }
}

void MainWindow::saveSettings() {
    serverPage->saveSettings();
}

void MainWindow::stopServer() {
    serverProcess->write("stop\r\n");
}

void MainWindow::serverStopped() {
    runButton->setEnabled(true);
    stopButton->setEnabled(false);
}

void MainWindow::processOutput() {
    QString out;
    QTextStream qout(&out);
    qout << serverProcess->readAllStandardOutput();
    consolePage->appendOutput(out);
}

void MainWindow::issueCommand(QString command) {
    serverProcess->write(command.toStdString().c_str());
}
