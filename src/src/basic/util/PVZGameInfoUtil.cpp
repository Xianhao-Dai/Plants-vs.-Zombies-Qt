//
// Created by 戴显灏 on 11/10/24.
//

#include "PVZGameInfoUtil.h"

#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QStandardPaths>

// static QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/info/game_info.txt";
static QString filePath = "/Users/daixianhao/CLionProjects/Plants Vs. Zombies/src/info/game_info.txt";

QString PVZGameInfoUtil::userName;
std::pair<int, int> PVZGameInfoUtil::adventureLevel;

QString PVZGameInfoUtil::getUserName() {
    if (userName.isEmpty()) {
        loadGameInfo();
    }
    return userName;
}

void PVZGameInfoUtil::setUserName(QString userName) {
    PVZGameInfoUtil::userName = userName;
    saveGameInfo();
}

std::pair<int, int> PVZGameInfoUtil::getAdventureLevel() {
    if (adventureLevel.first == 0) {
        loadGameInfo();
    }
    return adventureLevel;
}

void PVZGameInfoUtil::setAdventureLevel(std::pair<int, int> adventureLevel) {
    PVZGameInfoUtil::adventureLevel = adventureLevel;
    saveGameInfo();
}

void PVZGameInfoUtil::loadGameInfo() {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList parts = line.split(" ", Qt::SkipEmptyParts);
            if (parts.count() > 1) {
                if (parts.at(0) == "user_name") {
                    userName = parts.at(1);
                } else if (parts.at(0) == "adventure_level") {
                    QStringList levelPair = parts.at(1).split("-", Qt::SkipEmptyParts);
                    if (levelPair.count() > 1) {
                        adventureLevel = std::pair(levelPair.at(0).toInt(), levelPair.at(1).toInt());
                    }
                }
            } else {
                userName = "";
                adventureLevel = std::pair(1, 1);
            }
        }
    }
    file.close();
}

void PVZGameInfoUtil::saveGameInfo() {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "user_name " << userName << "\n" << "adventure_level " << adventureLevel.first << "-" << adventureLevel.second << "\n";
    }
    file.close();
}