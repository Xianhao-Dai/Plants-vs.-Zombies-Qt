//
// Created by 戴显灏 on 11/6/24.
//

#include "PVZResourceLoaderUtil.h"

#include <QMovie>

#include "PVZWidgetUtil.h"
#include "src/src/PVZGameEntrance.h"

#include <QPainter>

QPixmap PVZResourceLoaderUtil::loadPixmap(const QString& path, const QString& prefix) {
    QString absolutePath = PVZResourceLoaderUtil::getAbsolutePath(path, prefix);
    if (pixmapCache.contains(absolutePath)) {
        return pixmapCache[absolutePath];
    }
    QPixmap pixmap(absolutePath);
    pixmapCache[absolutePath] = pixmap;
    return pixmap;
}

QPixmap PVZResourceLoaderUtil::loadFullWindowPixmap(const QString& path, const QString& prefix) {
    return PVZResourceLoaderUtil::loadScaledPixmap(path, PVZWidgetUtil::mainWidgetWidth, PVZWidgetUtil::mainWidgetHeight, Qt::KeepAspectRatio, prefix);
}

QPixmap PVZResourceLoaderUtil::loadScaledPixmap(const QString& path, double scale, const QString& prefix) {
    QPixmap pixmap = PVZResourceLoaderUtil::loadPixmap(path, prefix);
    QSize size = pixmap.size();
    return PVZResourceLoaderUtil::resizePixmap(pixmap,static_cast<int>(size.width() * scale), static_cast<int>(size.height() * scale), Qt::KeepAspectRatio);
}

QPixmap PVZResourceLoaderUtil::loadScaledPixmap(const QString& path, int width, int height, Qt::AspectRatioMode mode, const QString& prefix) {
    QPixmap pixmap = PVZResourceLoaderUtil::loadPixmap(path, prefix);
    return PVZResourceLoaderUtil::resizePixmap(pixmap, width, height, mode);
}

QPixmap PVZResourceLoaderUtil::loadScaledPixmapOnWidth(const QString& path, int width, const QString& prefix) {
    QPixmap pixmap = PVZResourceLoaderUtil::loadPixmap(path, prefix);
    return PVZResourceLoaderUtil::resizePixmap(pixmap, width, pixmap.height(), Qt::IgnoreAspectRatio);
}

QPixmap PVZResourceLoaderUtil::loadScaledPixmapOnHeight(const QString& path, int height, const QString& prefix) {
    QPixmap pixmap = PVZResourceLoaderUtil::loadPixmap(path, prefix);
    return PVZResourceLoaderUtil::resizePixmap(pixmap, pixmap.width(), height, Qt::IgnoreAspectRatio);
}

QPixmap PVZResourceLoaderUtil::resizePixmap(const QPixmap &pixmap, int width, int height, Qt::AspectRatioMode mode) {
    if (mode == Qt::KeepAspectRatio) {
        QSize size = pixmap.size();
        double scaleOnWidth = static_cast<double>(width) / static_cast<double>(size.width());
        double scaleOnHeight = static_cast<double>(height) / static_cast<double>(size.height());
        double scale = scaleOnWidth > scaleOnHeight ? scaleOnWidth : scaleOnHeight;
        return pixmap.scaled(QSize(static_cast<int>(size.width() * scale), static_cast<int>(size.height() * scale)), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    } else if (mode == Qt::IgnoreAspectRatio) {
        return pixmap.scaled(QSize(width, height), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
}

const QSize &PVZResourceLoaderUtil::resizeMovie(QMovie *movie, int width, int height, Qt::AspectRatioMode mode) {
    QSize size = movie->currentPixmap().size();
    if (size.width() < width && size.height() < height) {
        return size;
    }
    if (mode == Qt::KeepAspectRatio) {
        double scaleOnWidth = static_cast<double>(width) / static_cast<double>(size.width());
        double scaleOnHeight = static_cast<double>(height) / static_cast<double>(size.height());
        double scale = scaleOnWidth < scaleOnHeight ? scaleOnWidth : scaleOnHeight;
        movie->setScaledSize(QSize(static_cast<int>(size.width() * scale), static_cast<int>(size.height() * scale)));
        return QSize(static_cast<int>(size.width() * scale), static_cast<int>(size.height() * scale));
    } else if (mode == Qt::IgnoreAspectRatio) {
        movie->setScaledSize(QSize(width, height));
        return QSize(width, height);
    }
    return size;
}

QPixmap PVZResourceLoaderUtil::loadRotatedPixmap(const QString &path, int angle, const QString &prefix) {
    QPixmap pixmap = PVZResourceLoaderUtil::loadPixmap(path, prefix);
    return PVZResourceLoaderUtil::rotatedPixmap(pixmap, angle);
}

QPixmap PVZResourceLoaderUtil::rotatedPixmap(const QPixmap &pixmap, int angle) {
    QTransform transform;
    transform.rotate(angle);
    return pixmap.transformed(transform, Qt::SmoothTransformation);
}

QPixmap PVZResourceLoaderUtil::horizontallyJoinPixmaps(std::initializer_list<QPixmap> pList, Qt::Alignment align) {
    int width = 0;
    int height = 0;
    for (QPixmap p : pList) {
        width += p.width();
        height = height > p.height() ? height : p.height();
    }
    QImage image = QImage(QSize(width, height), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(image.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    for (QPixmap p : pList) {
        if (align == Qt::AlignTop) {
            painter.drawPixmap(0, 0, p);
        } else if (align == Qt::AlignCenter) {
            painter.drawPixmap(0, height / 2 - p.height() / 2, p);
        } else if (align == Qt::AlignBottom) {
            painter.drawPixmap(0, height - p.height(), p);
        }
        painter.translate(p.width(), 0);
    }
    return QPixmap::fromImage(image);
}

QPixmap PVZResourceLoaderUtil::verticallyJoinPixmaps(std::initializer_list<QPixmap> pList, Qt::Alignment align) {
    int width = 0;
    int height = 0;
    for (QPixmap p : pList) {
        height += p.height();
        width = width > p.width() ? width : p.width();
    }
    QImage image = QImage(QSize(width, height), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(image.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    for (QPixmap p : pList) {
        if (align == Qt::AlignLeft) {
            painter.drawPixmap(0, 0, p);
        } else if (align == Qt::AlignCenter) {
            painter.drawPixmap(width / 2 - p.width() / 2, 0, p);
        } else if (align == Qt::AlignRight) {
            painter.drawPixmap(width - p.width(), 0, p);
        }
        painter.translate(0, p.height());
    }
    return QPixmap::fromImage(image);
}

QPixmap PVZResourceLoaderUtil::overlapPixmaps(QPixmap pixmap_1, QPixmap pixmap_2, QPoint offset_1, QPoint offset_2, Qt::Alignment align) {
    int width = pixmap_1.width() > pixmap_2.width() ? pixmap_1.width() : pixmap_2.width();
    int height = pixmap_1.height() > pixmap_2.height() ? pixmap_1.height() : pixmap_2.height();
    QImage image = QImage(QSize(width, height), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(image.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    int originX_1 = 0;
    int originY_1 = 0;
    int originX_2 = 0;
    int originY_2 = 0;
    if (align & Qt::AlignLeft) {
        originX_1 = originX_2 = 0;
    } else if (align & Qt::AlignHCenter) {
        originX_1 = width / 2 - pixmap_1.width() / 2;
        originX_2 = width / 2 - pixmap_2.width() / 2;
    } else if (align & Qt::AlignRight) {
        originX_1 = width - pixmap_1.width();
        originX_2 = width - pixmap_2.width();
    }
    if (align & Qt::AlignTop) {
        originY_1 = originY_2 = 0;
    } else if (align & Qt::AlignVCenter) {
        originY_1 = height / 2 - pixmap_1.height() / 2;
        originY_2 = height / 2 - pixmap_2.height() / 2;
    } else if (align & Qt::AlignBottom) {
        originY_1 = height - pixmap_1.height();
        originY_2 = height - pixmap_2.height();
    }
    originX_1 += offset_1.x();
    originY_1 += offset_1.y();
    originX_2 += offset_2.x();
    originY_2 += offset_2.y();
    painter.drawPixmap(originX_1, originY_1, pixmap_1);
    painter.drawPixmap(originX_2, originY_2, pixmap_2);
    return QPixmap::fromImage(image);
}

QPixmap PVZResourceLoaderUtil::overlapPixmaps(std::initializer_list<QPixmap> pList, Qt::Alignment align) {
    int width = 0;
    int height = 0;
    for (QPixmap p : pList) {
        width = width > p.width() ? width : p.width();
        height = height > p.height() ? height : p.height();
    }
    QImage image = QImage(QSize(width, height), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(image.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    for (QPixmap p : pList) {
        int originX = 0;
        int originY = 0;
        if (align & Qt::AlignLeft) {
            originX = 0;
        } else if (align & Qt::AlignHCenter) {
            originX = width / 2 - p.width() / 2;
        } else if (align & Qt::AlignRight) {
            originX = width - p.width();
        }
        if (align & Qt::AlignTop) {
            originY = 0;
        } else if (align & Qt::AlignVCenter) {
            originY = height / 2 - p.height() / 2;
        } else if (align & Qt::AlignBottom) {
            originY = height - p.height();
        }
        painter.drawPixmap(originX, originY, p);
    }
    return QPixmap::fromImage(image);
}

QPixmap PVZResourceLoaderUtil::adjustBrightness(const QPixmap& pixmap, double brightness) {
    if (brightness < 0) {
        brightness = 0;
    }
    QImage originImage = pixmap.toImage();
    QColor oldcolor;
    QImage newImage = QImage(originImage.width(), originImage.height(), QImage::Format_ARGB32);
    for (int y = 0; y < originImage.height(); y++) {
        for (int x = 0; x < originImage.width(); x++) {
            int r = 0,g = 0,b = 0,a = 0;
            oldcolor = originImage.pixel(x, y);
            r = oldcolor.red() * brightness;
            g = oldcolor.green() * brightness;
            b = oldcolor.blue() * brightness;
            a = qAlpha(originImage.pixel(x, y));
            r = r > 255 ? 255 : r;
            g = g > 255 ? 255 : g;
            b = b > 255 ? 255 : b;
            newImage.setPixel(x, y, qRgba(r, g, b, a));
        }
    }
    return QPixmap::fromImage(newImage);
}

QPixmap PVZResourceLoaderUtil::adjustAlpha(const QPixmap& pixmap, double alpha) {
    if (alpha < 0) {
        alpha = 0;
    }
    if (alpha > 1) {
        alpha = 1;
    }
    QImage originImage = pixmap.toImage();
    QColor oldcolor;
    QImage newImage = QImage(originImage.width(), originImage.height(), QImage::Format_ARGB32);
    for (int y = 0; y < originImage.height(); y++) {
        for (int x = 0; x < originImage.width(); x++) {
            oldcolor = originImage.pixel(x, y);
            int r = oldcolor.red();
            int g = oldcolor.green();
            int b = oldcolor.blue();
            int a = qAlpha(originImage.pixel(x, y)) * alpha;
            newImage.setPixel(x, y, qRgba(r, g, b, a));
        }
    }
    return QPixmap::fromImage(newImage);
}

QPixmap PVZResourceLoaderUtil::loadPlantPixmap(const QString& seedName, const QString& prefix) {
    QString path = "/plants/" + seedName + ".png";
    return loadPixmap(path, prefix);
}

QString PVZResourceLoaderUtil::getAbsolutePath(const QString& path, const QString& prefix) {
    return ":/" + prefix + "/src/assets" + path;
}

QMap<QString, QPixmap> PVZResourceLoaderUtil::pixmapCache = QMap<QString, QPixmap>();


