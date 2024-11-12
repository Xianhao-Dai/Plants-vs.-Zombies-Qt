//
// Created by 戴显灏 on 11/10/24.
//

#include "PVZAdventureController.h"

#include "src/src/basic/util/PVZGameInfoUtil.h"
#include "PVZAdventureWidget.h"
#include "src/src/basic/UI/PVZDialog.h"
#include "src/src/basic/UI/PVZSeedBankWidget.h"
#include "src/src/basic/UI/PVZSeedPickerWidget.h"
#include "src/src/basic/UI/PVZYardWidget.h"
#include "util/PVZAdventureUtil.h"

void PVZAdventureController::runAdventure() {
    setUpUI();
    adventureWidget->show();
}

void PVZAdventureController::setUpUI() {
    adventureLevel = PVZGameInfoUtil::getAdventureLevel();
    AdventureScene scene = BareYard;
    switch (adventureLevel.first) {
        case 1:
            if (adventureLevel.second == 1) {
                scene = BareYard;
            } else {
                scene = YardDaytime;
            }
        break;
        case 2:
            scene = YardNight;
        break;
        case 3:
            scene = PoolDaytime;
        break;
        case 4:
            scene = PoolNight;
        break;
        case 5:
            scene = RoofDaytime;
        break;
        case 6:
            scene = RoofNight;
        break;
        default:
            break;
    }
    adventureWidget = new PVZAdventureWidget(this, scene);
    if (adventureLevel.first == 1 && adventureLevel.second <= 6) {
        setUpDefaultGame();
    } else {
        setUpSelfPickGame();
    }
}

void PVZAdventureController::setUpDefaultGame() {
    connect(adventureWidget, &PVZAdventureWidget::bgAnimationFinished_1, [=]() {
        seedPickDidFinished();
    });
    connect(adventureWidget, &PVZAdventureWidget::bgAnimationFinished_2, [=]() {
        bank = new PVZSeedBankWidget(PVZAdventureUtil::defaultSeedsWithAdventureLevel(adventureLevel), adventureWidget);
        bank->move(10, 0);
        bank->show();
        yard = new PVZYardWidget(adventureWidget);
        yard->move(25, 75);
        yard->show();
        connect(bank, &PVZSeedBankWidget::seedDidClicked, yard, &PVZYardWidget::setReadyToPlant);
    });
}

void PVZAdventureController::setUpSelfPickGame() {
    connect(adventureWidget, &PVZAdventureWidget::bgAnimationFinished_1, [=]() {
        bank = new PVZSeedBankWidget({}, adventureWidget);
        bank->move(10, 0);
        bank->show();
        PVZSeedPickerWidget *picker = new PVZSeedPickerWidget({
            "tallnuts"
        }, {}, adventureWidget);
        picker->move(0, 100);
        picker->show();
    });
}
