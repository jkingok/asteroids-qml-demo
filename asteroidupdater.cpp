#include <QDebug>
#include <QList>
#include <QMutexLocker>
#include <QTimer>

#include "asteroid.h"
#include "asteroidprovider.h"
#include "asteroidupdater.h"

AsteroidUpdater::AsteroidUpdater(AsteroidProvider * provider, QObject *parent) : QObject(parent), provider(provider), timer(NULL)
{

}

AsteroidUpdater::~AsteroidUpdater()
{
    if (timer != NULL) delete timer;
}

void AsteroidUpdater::updateAsteroids()
{
    qDebug() << "Updating Asteroids";
    // Start a repeating timer that updates the state
    if (timer == NULL) {
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &AsteroidUpdater::nextUpdate);
    }
    timer->setInterval(50);
    timer->setSingleShot(false);
    timer->start();
}

void AsteroidUpdater::nextUpdate()
{
    QMutexLocker lock(provider->getMutex());
    QList<Asteroid *> * list = provider->getList();
    QDateTime now = QDateTime::currentDateTime();
    bool changed = false;
    foreach (Asteroid * a, *list) {
        if (now > a->lastUpdate()) {
            qreal delta = a->lastUpdate().msecsTo(now) / 1000.0f;
            if (a->xVelocity() != 0.0f) {
                a->setX(a->x() + a->xVelocity() * delta);
                changed = true;
            }
            if (a->yVelocity() != 0.0f) {
                a->setY(a->y() + a->yVelocity() * delta);
                changed = true;
            }
            if (a->rotationalVelocity() != 0.0f) {
                a->setSpin(a->spin() + a->rotationalVelocity() * delta);
                changed = true;
            }
            a->setLastUpdate(now);
        }
    }
    if (changed) emit updatedAsteroids();
}
