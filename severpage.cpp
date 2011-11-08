#include "severpage.h"
#include "mainwindow.h"
#include <QGridLayout>
#include <QFileDialog>
#include <QLabel>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

ServerPage::ServerPage(QWidget *parent) :
    QWidget(parent) {
    //Setup window with default server options
    serverPath = new QLineEdit;
    serverBrowse = new QPushButton("Browse");
    connect(serverBrowse, SIGNAL(clicked()), this, SLOT(serverOpen()));

    worldSelector = new QComboBox;
    worldSelector->addItem("world");
    worldAdd = new QPushButton("Add");
    worldRemove = new QPushButton("Remove");

    serverIp = new QLineEdit;

    serverPort = new QLineEdit("25565");

    levelSeed = new QLineEdit;

    maxPlayers = new QSpinBox;
    maxPlayers->setRange(0, 999);
    maxPlayers->setValue(20);

    difficulty = new QComboBox;
    difficulty->addItem("Peaceful");
    difficulty->addItem("Easy");
    difficulty->addItem("Normal");
    difficulty->addItem("Hard");
    difficulty->setCurrentIndex(1);

    gameMode = new QComboBox;
    gameMode->addItem("Survival");
    gameMode->addItem("Creative");
    gameMode->setCurrentIndex(0);

    viewDistance = new QSpinBox;
    viewDistance->setRange(3, 15);
    viewDistance->setValue(10);

    motd = new QLineEdit("A Minecraft Server");

    ramSize = new QSpinBox;
    ramSize->setRange(1, 4096);
    ramSize->setValue(1024);

    allowFlight = new QCheckBox("Allow Flight");
    allowNether = new QCheckBox("Allow Nether");
    allowNether->setChecked(true);
    onlineMode = new QCheckBox("Online Mode");
    onlineMode->setChecked(true);
    pvp = new QCheckBox("PvP");
    pvp->setChecked(true);
    spawnAnimals = new QCheckBox("Spawn Animals");
    spawnAnimals->setChecked(true);
    spawnMonsters = new QCheckBox("Spawn Monsters");
    spawnMonsters->setChecked(true);
    whiteList = new QCheckBox("White List");


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel("Server File"), 0, 0);
    layout->addWidget(serverPath, 0, 1, 1, 2);
    layout->addWidget(serverBrowse, 0, 3);
    layout->addWidget(new QLabel("World"), 1, 0);
    layout->addWidget(worldSelector, 1, 1);
    layout->addWidget(worldAdd, 1, 2);
    layout->addWidget(worldRemove, 1, 3);
    layout->addWidget(new QLabel("Server IP"), 2, 0);
    layout->addWidget(serverIp, 2, 1, 1, 3);
    layout->addWidget(new QLabel("Server Port"), 3, 0);
    layout->addWidget(serverPort, 3, 1, 1, 3);
    layout->addWidget(new QLabel("Level Seed"), 4, 0);
    layout->addWidget(levelSeed, 4, 1, 1, 3);
    layout->addWidget(new QLabel("Max Players"), 5, 0);
    layout->addWidget(maxPlayers, 5, 1, 1, 3);
    layout->addWidget(new QLabel("Difficulty"), 6, 0);
    layout->addWidget(difficulty, 6, 1 ,1, 3);
    layout->addWidget(new QLabel("Game Mode"), 7, 0);
    layout->addWidget(gameMode, 7, 1, 1, 3);
    layout->addWidget(new QLabel("View Distance"), 8, 0);
    layout->addWidget(viewDistance, 8, 1, 1, 3);
    layout->addWidget(new QLabel("MotD"), 9, 0);
    layout->addWidget(motd, 9, 1, 1, 3);
    layout->addWidget(new QLabel("RAM (MiB)"), 10, 0);
    layout->addWidget(ramSize, 10, 1, 1, 3);
    layout->addWidget(allowFlight);
    layout->addWidget(allowNether);
    layout->addWidget(onlineMode);
    layout->addWidget(pvp);
    layout->addWidget(spawnAnimals);
    layout->addWidget(spawnMonsters);
    layout->addWidget(whiteList);

    setLayout(layout);
    loadSettings();
}

void ServerPage::serverOpen() {
    serverPath->setText(QFileDialog::getOpenFileName(this, tr("Server File"), QDir::homePath(), tr("Jar Files(*.jar)")));
}

const QString ServerPage::getServerPath() {
    return serverPath->text();
}

int ServerPage::getRam() {
    return ramSize->value();
}

void ServerPage::loadSettings() {
    QString filePath(QDir::homePath() + "/.pickaxe/server.properties");

    if(!QFile::exists(filePath)) {
        return;
    }
    QFile settingsFile(filePath);
    if(!settingsFile.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Couldn't open server.properties"));
        return;
    }
    QTextStream in(&settingsFile);
    QString temp;
    while(!in.atEnd()) {
        temp = in.readLine();
        if(temp.contains("level-name") && (temp.section('=', 1, 1) != "world")) {
            worldSelector->addItem(temp.section('=', 1, 1));
            worldSelector->setCurrentIndex(worldSelector->count()-1);
        } else if (temp.contains("server-ip")) {
            serverIp->setText(temp.section('=', 1, 1));
        } else if(temp.contains("server-port")) {
            serverPort->setText(temp.section('=', 1, 1));
        } else if(temp.contains("level-seed")) {
            levelSeed->setText(temp.section('=',1 ,1));
        } else if(temp.contains("max-players")) {
            maxPlayers->setValue(temp.section('=', 1, 1).toInt());
        } else if (temp.contains("difficulty")) {
            difficulty->setCurrentIndex(temp.section('=', 1, 1).toInt());
        } else if (temp.contains("gamemode")) {
            gameMode->setCurrentIndex(temp.section('=', 1, 1).toInt());
        } else if (temp.contains("view-distance")) {
            viewDistance->setValue(temp.section('=', 1, 1).toInt());
        } else if (temp.contains("motd")) {
            motd->setText(temp.remove(0, 5));
        } else if(temp.contains("allow-flight")) {
            if(temp.section('=', 1, 1) == "true") {
                allowFlight->setChecked(true);
            } else {
                allowFlight->setChecked(false);
            }
        } else if(temp.contains("allow-nether")) {
            if(temp.section('=', 1, 1) == "true") {
                allowNether->setChecked(true);
            } else {
                allowNether->setChecked(false);
            }
        } else if(temp.contains("online-mode")) {
            if(temp.section('=', 1, 1) == "true") {
                onlineMode->setChecked(true);
            } else {
                onlineMode->setChecked(false);
            }
        } else if(temp.contains("pvp")) {
            if(temp.section('=', 1, 1) == "true") {
                pvp->setChecked(true);
            } else {
                pvp->setChecked(false);
            }
        } else if(temp.contains("spawn-animals")) {
            if(temp.section('=', 1, 1) == "true") {
                spawnAnimals->setChecked(true);
            } else {
                spawnAnimals->setChecked(false);
            }
        } else if(temp.contains("spawn-monsters")) {
            if(temp.section('=', 1, 1) == "true") {
                spawnMonsters->setChecked(true);
            } else {
                spawnMonsters->setChecked(false);
            }
        } else if(temp.contains("white-list")) {
            if(temp.section('=', 1, 1) == "true") {
                whiteList->setChecked(true);
            } else {
                whiteList->setChecked(false);
            }
        }
    }
    settingsFile.close();
}

void ServerPage::saveSettings() {
    QString filePath(QDir::homePath() + "/.pickaxe/server.properties");

    QFile settingsFile(filePath);
    if(!settingsFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Couldn't save settings! Program will exit"));
    }
    int diff;
    int mode;
    QString flight;
    QString nether;
    QString online;
    QString PvP;
    QString animals;
    QString monsters;
    QString white;

    if(difficulty->currentText() == "Peaceful") {
        diff = ServerPage::peaceful;
    } else if(difficulty->currentText() == "Easy") {
        diff = ServerPage::easy;
    } else if(difficulty->currentText() == "Normal") {
        diff = ServerPage::normal;
    } else if(difficulty->currentText() == "Hard") {
        diff = ServerPage::hard;
    }

    if(gameMode->currentText() == "Survival") {
        mode = ServerPage::survival;
    } else if(gameMode->currentText() == "Creative") {
        mode = ServerPage::creative;
    }

    if(allowFlight->checkState()) {
        flight = "true";
    } else {
        flight = "false";
    }
    if(allowNether->checkState()) {
        nether = "true";
    } else {
        nether = "false";
    }
    if(onlineMode->checkState()) {
        online = "true";
    } else {
        online = "false";
    }
    if(pvp->checkState()) {
        PvP = "true";
    } else {
        PvP = "false";
    }
    if(spawnAnimals->checkState()) {
        animals = "true";
    } else {
        animals = "false";
    }
    if(spawnMonsters->checkState()) {
        monsters = "true";
    } else {
        monsters = "false";
    }
    if(whiteList->checkState()) {
        white = "true";
    } else {
        white = "false";
    }

    QTextStream out(&settingsFile);
    out << "#Minecraft server properties\n";
    out << "#Created by Pickaxe\n";
    out << "level-name=" << worldSelector->currentText() << "\n";
    out << "server-ip=" << serverIp->text() << "\n";
    out << "server-port=" << serverPort->text() << "\n";
    out << "level-seed=" << levelSeed->text() << "\n";
    out << "max-players=" << maxPlayers->value() << "\n";
    out << "difficulty=" << diff << "\n";
    out << "gamemode=" << mode << "\n";
    out << "view-distance=" << viewDistance->text() << "\n";
    out << "motd=" << motd->text() << "\n";
    out << "allow-flight=" << flight << "\n";
    out << "allow-nether=" << nether << "\n";
    out << "online-mode=" << online << "\n";
    out << "pvp=" << PvP << "\n";
    out << "spawn-animals=" << animals << "\n";
    out << "spawn-monsters=" << monsters << "\n";
    out << "white-list=" << white << "\n";

    settingsFile.close();
}
