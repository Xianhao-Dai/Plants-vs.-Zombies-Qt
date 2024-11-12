cmake_minimum_required(VERSION 3.0)
project(Plants_Vs__Zombies)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Plants_Vs__Zombies main.cpp
        src/src/PVZGameEntrance.cpp
        src/src/PVZGameEntrance.h
        src/src/basic/util/PVZWidgetUtil.h
        src/src/game_widget/PVZGameStartWidget.cpp
        src/src/game_widget/PVZGameStartWidget.h
        rsc.qrc
        src/src/basic/util/PVZResourceLoaderUtil.cpp
        src/src/basic/util/PVZResourceLoaderUtil.h
        src/src/basic/UI/PVZPushButton.cpp
        src/src/basic/UI/PVZPushButton.h
        src/src/game_widget/PVZMenuWidget.cpp
        src/src/game_widget/PVZMenuWidget.h
        src/src/basic/UI/PVZDialog.cpp
        src/src/basic/UI/PVZDialog.h
        src/src/basic/UI/PVZDialogButton.cpp
        src/src/basic/UI/PVZDialogButton.h
        src/src/adventure/PVZAdventureWidget.cpp
        src/src/adventure/PVZAdventureWidget.h
        src/src/adventure/PVZAdventureController.cpp
        src/src/adventure/PVZAdventureController.h
        src/src/basic/util/PVZGameInfoUtil.cpp
        src/src/basic/util/PVZGameInfoUtil.h
        src/src/basic/UI/PVZSeedPickerWidget.cpp
        src/src/basic/UI/PVZSeedPickerWidget.h
        src/src/entity/plants/PVZBasicPlant.h
        src/src/basic/UI/PVZSeedCardButton.cpp
        src/src/basic/UI/PVZSeedCardButton.h
        src/src/basic/UI/PVZSeedBankWidget.cpp
        src/src/basic/UI/PVZSeedBankWidget.h
        src/src/adventure/util/PVZAdventureUtil.cpp
        src/src/adventure/util/PVZAdventureUtil.h
        src/src/basic/UI/PVZYardWidget.cpp
        src/src/basic/UI/PVZYardWidget.h
        src/src/basic/UI/PVZGridWidget.cpp
        src/src/basic/UI/PVZGridWidget.h
)

target_link_libraries(Plants_Vs__Zombies
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

