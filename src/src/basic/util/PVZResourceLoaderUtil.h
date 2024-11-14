//
// Created by 戴显灏 on 11/6/24.
//

#ifndef RESOURCELOADERUTIL_H
#define RESOURCELOADERUTIL_H
#include <QtGui/qpixmap.h>


class PVZResourceLoaderUtil {
public:
    /*General*/
    static QPixmap loadPixmap(const QString& path, const QString& prefix="default");
    static QPixmap loadFullWindowPixmap(const QString& path, const QString& prefix="default");
    static QPixmap loadScaledPixmap(const QString& path, double scale, const QString& prefix="default");
    static QPixmap loadScaledPixmap(const QString& path, int width, int height, Qt::AspectRatioMode mode=Qt::IgnoreAspectRatio, const QString& prefix="default");
    static QPixmap loadScaledPixmapOnWidth(const QString& path, int width, const QString& prefix="default");
    static QPixmap loadScaledPixmapOnHeight(const QString& path, int height, const QString& prefix="default");
    static QPixmap resizePixmap(const QPixmap& pixmap, int width, int height, Qt::AspectRatioMode mode=Qt::IgnoreAspectRatio);
    static void resizeMovie(QMovie *movie, int width, int height, Qt::AspectRatioMode mode=Qt::IgnoreAspectRatio);
    static QPixmap loadRotatedPixmap(const QString& path, int angle, const QString& prefix="default");
    static QPixmap rotatedPixmap(const QPixmap& pixmap, int angle);
    static QPixmap horizontallyJoinPixmaps(std::initializer_list<QPixmap> pList, Qt::Alignment align=Qt::AlignCenter);
    static QPixmap verticallyJoinPixmaps(std::initializer_list<QPixmap> pList, Qt::Alignment align=Qt::AlignCenter);
    static QPixmap overlapPixmaps(QPixmap pixmap_1, QPixmap pixmap_2, QPoint offset_1, QPoint offset_2, Qt::Alignment align=Qt::AlignCenter);
    static QPixmap overlapPixmaps(std::initializer_list<QPixmap> pList, Qt::Alignment align=Qt::AlignCenter);
    static QPixmap adjustBrightness(const QPixmap& pixmap, double brightness);
    static QPixmap adjustAlpha(const QPixmap& pixmap, double alpha);

    /*Plants*/
    static QPixmap loadPlantPixmap(const QString& seedName, const QString& prefix="default");

private:
    static QString getAbsolutePath(const QString& path, const QString& prefix="default");

    static QMap<QString, QPixmap> pixmapCache;
};



#endif //RESOURCELOADERUTIL_H
