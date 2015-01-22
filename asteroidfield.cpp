#include <cmath>

#include <QDebug>
#include <QPainter>

#include "asteroid.h"
#include "asteroidcreator.h"
#include "asteroidupdater.h"

#include "asteroidfield.h"

AsteroidField::AsteroidField(QQuickItem * parent)
    : QQuickPaintedItem(parent), image(":/meteor.png")
{


    creator = new AsteroidCreator();
    connect(&taskThread, &QThread::started, creator, &AsteroidCreator::createAsteroids);
    creator->moveToThread(&taskThread);
    connect(&taskThread, &QThread::finished, creator, &QObject::deleteLater);
    connect(creator, &AsteroidCreator::newAsteroid, this, &AsteroidField::asteroidCreated);
    updater = new AsteroidUpdater(this);
    connect(&taskThread, &QThread::started, updater, &AsteroidUpdater::updateAsteroids);
    updater->moveToThread(&taskThread);
    connect(&taskThread, &QThread::finished, updater, &QObject::deleteLater);
    connect(updater, &AsteroidUpdater::updatedAsteroids, this, &AsteroidField::asteroidsUpdated);
}

AsteroidField::~AsteroidField()
{
}

void AsteroidField::paint(QPainter *painter) {
    int w = width();
    int h = height();
    int r = qMin(w, h);

    painter->setPen(Qt::black);
    {
        QMutexLocker lock(&mutex);
        //painter->drawImage(QRectF(0, 0, w, h), image);
        foreach (Asteroid * a, asteroids) {
            // Old drawing
//            painter->drawEllipse(a->x() * w - a->size() * r / 2,
//                                 a->y() * h - a->size() * r / 2,
//                                 a->size() * r,
//                                 a->size() * r);
//            painter->drawLine(QPointF(a->x() * w, a->y() * h),
//                              QPointF(
//                                a->x() * w + a->size() * r / 2 * sin(a->spin() * 2 * M_PI),
//                                a->y() * h + a->size() * r / 2 * cos(a->spin() * 2 * M_PI)));
            // New drawing
            QRectF re(a->x() * w - a->size() * r / 2,
                     a->y() * h - a->size() * r / 2,
                     a->size() * r,
                     a->size() * r);
//            painter->drawRect(re);
            painter->drawImage(
                        re,
                        image,
                        QRectF(((int) (a->spin() * 35) % 35) * 100, 0, 100, 100));
        }
    }

}

void AsteroidField::startField()
{
    qDebug() << "Starting field";
    taskThread.start();
}

void AsteroidField::asteroidCreated(Asteroid * a)
{
    QMutexLocker lock(&mutex);
    asteroids.push_back(a);
    update();
}

void AsteroidField::asteroidsUpdated()
{
    update();
}
