#include <QDebug>
#include <QTimer>

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
    int rx = qrand() % 360;
    int ry = qrand() % 360;

    qDebug() << "New Asteroid" << rx << ry;
    emit newAsteroid(rx, ry);
}


