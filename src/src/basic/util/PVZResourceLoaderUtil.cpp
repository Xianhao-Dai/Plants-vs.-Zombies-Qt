//
// Created by 戴显灏 on 11/6/24.
//

#include "PVZResourceLoaderUtil.h"

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

QString PVZResourceLoaderUtil::getAbsolutePath(const QString& path, const QString& prefix) {
    return ":/" + prefix + "/src/assets" + path;
}

QMap<QString, QPixmap> PVZResourceLoaderUtil::pixmapCache = QMap<QString, QPixmap>();


