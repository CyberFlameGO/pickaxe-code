#ifndef CONSOLEPAGE_H
#define CONSOLEPAGE_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>

class ConsolePage : public QWidget
{
    Q_OBJECT
public:
    explicit ConsolePage(QWidget *parent = 0);
signals:
    void sendCommand(QString);
public slots:
    void appendOutput(QString output);
    void inputReady();
private:
    QTextEdit *console;
    QLineEdit *input;
};

#endif // CONSOLEPAGE_H
