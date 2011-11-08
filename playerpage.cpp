#include "playerpage.h"
#include <QGridLayout>
#include <QLabel>

PlayerPage::PlayerPage(QWidget *parent) :
    QWidget(parent) {
    opList = new QComboBox;
    opAdd = new QPushButton(tr("Add"));
    opRemove = new QPushButton(tr("Remove"));

    whiteList = new QComboBox;
    whiteAdd = new QPushButton("Add");
    whiteRemove = new QPushButton("Remove");

    bannedPlayers = new QComboBox;
    bannedPlayersAdd = new QPushButton("Add");
    bannedPlayersRemove = new QPushButton("Remove");

    bannedIps = new QComboBox;
    bannedIpsAdd = new QPushButton("Add");
    bannedIpsRemove = new QPushButton("Remove");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel("Ops"), 0, 0);
    layout->addWidget(opList, 0, 1);
    layout->addWidget(opAdd, 0, 2);
    layout->addWidget(opRemove, 0, 3);
    layout->addWidget(new QLabel("White List"));
    layout->addWidget(whiteList);
    layout->addWidget(whiteAdd);
    layout->addWidget(whiteRemove);
    layout->addWidget(new QLabel("Banned Players"));
    layout->addWidget(bannedPlayers);
    layout->addWidget(bannedPlayersAdd);
    layout->addWidget(bannedPlayersRemove);
    layout->addWidget(new QLabel("Banned IPs"));
    layout->addWidget(bannedIps);
    layout->addWidget(bannedIpsAdd);
    layout->addWidget(bannedIpsRemove);
    layout->setRowStretch(4, 1);

    setLayout(layout);
}
