//
// Created by 戴显灏 on 11/10/24.
//

#include "PVZSeedCardButton.h"

#include "src/src/basic/util/PVZResourceLoaderUtil.h"

PVZSeedCardButton::PVZSeedCardButton(QString id, QSize size, bool enabled, QWidget *parent) : PVZPushButton(parent, "/plants/" + id + ".png") {
    QPixmap bg = PVZResourceLoaderUtil::loadScaledPixmap("/bg/bg_seed_card.png", size.width(), size.height());
    icon = PVZResourceLoaderUtil::resizePixmap(icon, size.width() / 2, size.height() / 2, Qt::KeepAspectRatio);
    QPixmap newIcon = PVZResourceLoaderUtil::overlapPixmaps({bg, icon});
    iconPath = "";
    highlightedIconPath = "";
    icon = newIcon;
    highlightedIcon = PVZResourceLoaderUtil::adjustBrightness(icon, 0.6);
    this->setIcon(icon);
    this->setIconSize(QSize(icon.width(), icon.height()));
    this->setFixedSize(QSize(icon.width(), icon.height()));
}
