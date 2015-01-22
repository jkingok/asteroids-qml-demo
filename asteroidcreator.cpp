#include <QDebug>
#include <QTimer>

#include "asteroid.h"

#include "asteroidcreator.h"

AsteroidCreator::AsteroidCreator(QObject *parent) : QObject(parent)
{
}

AsteroidCreator::~AsteroidCreator()
{
    if (timer != NULL) delete timer;
}

void AsteroidCreator::createAsteroids()
{
    qDebug() << "Creating Asteroids";
    // Start a repeating timer that creates random asteroids
    if (timer == NULL) {
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &AsteroidCreator::nextAsteroid);
    }
    timer->setInterval(500);
    timer->setSingleShot(false);
    timer->start();
}

void AsteroidCreator::nextAsteroid()
{
    qreal rx = qrand() / (qreal) RAND_MAX;
    qreal ry = qrand() / (qreal) RAND_MAX;

    qDebug() << "New Asteroid" << rx << ry;
    emit newAsteroid(new Asteroid(rx, ry, 0, 0, 0, 0, 0.1f));
}


