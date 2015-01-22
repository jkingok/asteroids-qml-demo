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
    timer->setInterval(1000);
    timer->setSingleShot(false);
    timer->start();
}

void AsteroidCreator::nextAsteroid()
{
    // Lets make a random number of Asteroids per time interval
    int n = qrand() % 3 + 1;
    for (int i = 0; i < n; i++) {
        // Now we make all Asteroids come in from the right
        // And never move right
        qreal rsi = qrand() / (qreal) RAND_MAX * 0.05 + 0.025;
        qreal rx = 1.0 + rsi;
        qreal ry = qrand() / (qreal) RAND_MAX;
        qreal rxv = -(qrand() / (qreal) RAND_MAX) * 0.05;
        qreal ryv = (qrand() / (qreal) RAND_MAX - 0.5) * 0.05;
        qreal rs = qrand() / (qreal) RAND_MAX;
        qreal rsv = (qrand() / (qreal) RAND_MAX - 0.5) * 0.1;

        qDebug() << "New Asteroid" << rx << ry << rxv << ryv << rs << rsv;
        emit newAsteroid(new Asteroid(rx, ry, rxv, ryv, rs, rsv, rsi));
    }
}


