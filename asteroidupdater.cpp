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
    QMutableListIterator<Asteroid *> it(*list);
    while (it.hasNext()) {
        Asteroid * a = it.next();
        if (now > a->lastUpdate()) {
            // If the asteroid is offscreen we must remove it
            if ((a->x() + a->size() < 0 && a->xVelocity() < 0)
                    || (a->x() - a->size() > 1 && a->xVelocity() > 0)
                    || (a->y() + a->size() < 0 && a->yVelocity() < 0)
                    || (a->y() - a->size() > 1 && a->yVelocity() > 0)) {
                it.remove();
                delete a;
                changed = true;
                qDebug() << "Deleted Asteroid";
            } else {
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
                    while (a->spin() < 0)
                        a->setSpin(a->spin() + 1);
                    changed = true;
                }
                a->setLastUpdate(now);
            }
        }
    }
    if (changed) emit updatedAsteroids();
}
