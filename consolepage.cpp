#include "consolepage.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QProcess>

ConsolePage::ConsolePage(QWidget *parent) :
    QWidget(parent) {
    console = new QTextEdit();
    console->setFocusPolicy(Qt::NoFocus);
    console->setReadOnly(true);
    console->setFixedWidth(650);

    input = new QLineEdit();
    connect(input, SIGNAL(returnPressed()), this, SLOT(inputReady()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(console);
    layout->addWidget(input);

    setLayout(layout);
}

void ConsolePage::inputReady() {
    emit sendCommand(input->text() + "\r\n");
    console->append(input->text());
    input->clear();
}

void ConsolePage::appendOutput(QString output) {
    console->append(output);
}
