#include <QDebug>
#include <QTimer>

#include "asteroid.h"

#include "asteroidcreator.h"

AsteroidCreator::AsteroidCreator(QObject *parent) : QObject(parent), timer(NULL)
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
    timer->setInterval(1500);
    timer->setSingleShot(false);
    timer->start();
}

void AsteroidCreator::nextAsteroid()
{
    qreal rx = qrand() / (qreal) RAND_MAX;
    qreal ry = qrand() / (qreal) RAND_MAX;
    qreal rxv = (qrand() / (qreal) RAND_MAX - 0.5) * 0.1;
    qreal ryv = (qrand() / (qreal) RAND_MAX - 0.5) * 0.1;
    qreal rs = qrand() / (qreal) RAND_MAX;
    qreal rsv = (qrand() / (qreal) RAND_MAX - 0.5) * 0.1;
    qreal rsi = qrand() / (qreal) RAND_MAX * 0.1 + 0.1;

    qDebug() << "New Asteroid" << rx << ry << rxv << ryv << rs << rsv;
    emit newAsteroid(new Asteroid(rx, ry, rxv, ryv, rs, rsv, rsi));
}


