#ifndef PLAYERPAGE_H
#define PLAYERPAGE_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>

class PlayerPage : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerPage(QWidget *parent = 0);
private:
    QComboBox *opList;
    QPushButton *opAdd;
    QPushButton *opRemove;
    QComboBox *whiteList;
    QPushButton *whiteAdd;
    QPushButton *whiteRemove;
    QComboBox *bannedPlayers;
    QPushButton *bannedPlayersAdd;
    QPushButton *bannedPlayersRemove;
    QComboBox *bannedIps;
    QPushButton *bannedIpsAdd;
    QPushButton *bannedIpsRemove;
};

#endif // PLAYERPAGE_H
