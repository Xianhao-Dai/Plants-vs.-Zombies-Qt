//
// Created by 戴显灏 on 11/10/24.
//

#ifndef PVZGAMEINFOUTIL_H
#define PVZGAMEINFOUTIL_H
#include <QtCore/qstring.h>

class PVZGameInfoUtil {
public:
    static QString getUserName();
    static void setUserName(QString userName);
    static std::pair<int, int> getAdventureLevel();
    static void setAdventureLevel(std::pair<int, int> adventureLevel);
private:
    static void loadGameInfo();
    static void saveGameInfo();
    static QString userName;
    static std::pair<int, int> adventureLevel;
};



#endif //PVZGAMEINFOUTIL_H
