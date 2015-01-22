#include <QDebug>
#include <QTimer>

#include "asteroid.h"

#include "asteroidcreator.h"

AsteroidCreator::AsteroidCreator(QObject *parent) : QObject(parent), timer(NULL),
    m_creationInterval(1000),
    m_minPerInterval(1),
    m_maxPerInterval(2),
    m_minSize(0.05),
    m_maxSize(0.075),
    m_minPrimaryVelocity(-0.06),
    m_maxPrimaryVelocity(-0.01)
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
        connect(this, &AsteroidCreator::creationIntervalChanged, timer, &QTimer::setInterval);
        connect(timer, &QTimer::timeout, this, &AsteroidCreator::nextAsteroid);
    }
    timer->setInterval(m_creationInterval);
    timer->setSingleShot(false);
    timer->start();
}

void AsteroidCreator::nextAsteroid()
{
    // Lets make a random number of Asteroids per time interval
    int n = (m_maxPerInterval - m_minPerInterval > 0)
            ? (qrand() % (m_maxPerInterval - m_minPerInterval + 1)) + m_minPerInterval
            : 1;
    for (int i = 0; i < n; i++) {
        // Now we make all Asteroids come in from the right
        // And never move right
        qreal rsi = m_minSize + (qrand() / (qreal) RAND_MAX * (m_maxSize - m_minSize));
        qreal rx = 1.0 + rsi;
        qreal ry = qrand() / (qreal) RAND_MAX;
        qreal rxv = m_minPrimaryVelocity + ((qrand() / (qreal) RAND_MAX) * (m_maxPrimaryVelocity - m_minPrimaryVelocity));
        qreal ryv = (qrand() / (qreal) RAND_MAX - 0.5) * 0.05;
        qreal rs = qrand() / (qreal) RAND_MAX * 0.5 + 0.25;
        qreal rsv = (qrand() / (qreal) RAND_MAX - 0.5) * 0.1;

        qDebug() << "New Asteroid" << rx << ry << rxv << ryv << rs << rsv;
        emit newAsteroid(new Asteroid(rx, ry, rxv, ryv, rs, rsv, rsi));
    }
}




