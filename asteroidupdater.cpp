#include <QDebug>
#include <QList>
#include <QMutexLocker>
#include <QQuickItem>
#include <QRectF>
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

    QList<QQuickItem *> * bullets = provider->getBullets();
    QMutableListIterator<QQuickItem *> it2(*bullets);
    while (it2.hasNext()) {
        QQuickItem * b = it2.next();
        // Check if it destroys any asteroids
        QRectF r1(b->x() / b->parentItem()->width(), b->y() / b->parentItem()->height(),
                  b->width() / b->parentItem()->width(), b->y() / b->parentItem()->height());
        bool collided = false;
        it.toFront();
        while (it.hasNext()) {
            Asteroid * a = it.next();
            QRectF r2(a->x() - a->size() / 2, a->y() - a->size() / 2,
                      a->size(), a->size());
            if (r2.intersects(r1)) {
                // Collision!
                collided = true;
                it.remove();
                delete a;
                changed = true;
                qDebug() << "Destroyed Asteroid by bullet";
            }
        }
        if (collided) emit bulletCollided(b);
    }

    QQuickItem * ship = provider->ship();
    // Check if it is destroyed by any asteroids
    if (ship->isVisible()) {
        QRectF r1(ship->x() / ship->parentItem()->width(), ship->y() / ship->parentItem()->height(),
                  ship->width() / ship->parentItem()->width(), ship->y() / ship->parentItem()->height());
        bool collided = false;
        it.toFront();
        while (it.hasNext()) {
            Asteroid * a = it.next();
            QRectF r2(a->x() - a->size() / 2, a->y() - a->size() / 2,
                      a->size(), a->size());
            if (r2.intersects(r1)) {
                // Collision!
                collided = true;
                it.remove();
                delete a;
                changed = true;
                qDebug() << "Destroyed Asteroid by ship";
            }
        }
        if (collided) emit shipDestroyed();
    }

    if (changed) emit updatedAsteroids();
}
