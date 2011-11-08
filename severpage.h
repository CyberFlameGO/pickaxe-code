#ifndef SEVERPAGE_H
#define SEVERPAGE_H

#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>

class ServerPage : public QWidget
{
    Q_OBJECT
public:
    explicit ServerPage(QWidget *parent = 0);
    const QString getServerPath();
    enum diff{
        peaceful = 0,
        easy = 1,
        normal = 2,
        hard = 3
    };
    enum mode {
        survival = 0,
        creative = 1
    };
    int getRam();
    void loadSettings();
    void saveSettings();
private slots:
    void serverOpen();
private:
    QLineEdit *serverPath;
    QPushButton *serverBrowse;
    QComboBox *worldSelector;
    QPushButton *worldAdd;
    QPushButton *worldRemove;
    QLineEdit *serverIp; //Text
    QLineEdit *serverPort; //Number 1-65535
    QLineEdit *levelSeed; //Alphanumeric
    QSpinBox *maxPlayers; //Number 0-999
    QSpinBox *viewDistance; //Number 3-15
    QComboBox *difficulty; // Enum 0-3
    QComboBox *gameMode; //Enum 0 or 1
    QSpinBox *ramSize; //Number as text
    QLineEdit *motd; //Text
    QCheckBox *allowNether; //Boolean
    QCheckBox *spawnMonsters; //Boolean
    QCheckBox *spawnAnimals; //Boolean
    QCheckBox *onlineMode; //Boolean
    QCheckBox *pvp; //Boolean
    QCheckBox *whiteList; //Boolean
    QCheckBox *allowFlight;//Boolean
};

#endif // SEVERPAGE_H
