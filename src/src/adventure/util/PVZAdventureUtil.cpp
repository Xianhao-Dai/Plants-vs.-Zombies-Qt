//
// Created by 戴显灏 on 11/11/24.
//

#include "PVZAdventureUtil.h"

#include <QtCore/qstring.h>


vector<QString>PVZAdventureUtil::defaultSeedsWithAdventureLevel(pair<int, int> adventureLevel) {
    if (adventureLevel.first > 1 || adventureLevel.second > 6) {
        return vector<QString>();
    }
    vector<QString> seeds = {"peashooter"};
    if (adventureLevel.second >= 2) {
        seeds.push_back("sunflower");
    }
    if (adventureLevel.second >= 3) {
        seeds.push_back("cherrybomb");
    }
    if (adventureLevel.second >= 4) {
        seeds.push_back("nuts");
    }
    if (adventureLevel.second >= 5) {
        seeds.push_back("potatomine");
    }
    if (adventureLevel.second >= 6) {
        seeds.push_back("tallnuts");
    }
    return seeds;
}
