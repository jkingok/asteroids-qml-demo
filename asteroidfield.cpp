#include <QDebug>
#include <QPainter>

#include "asteroid.h"
#include "asteroidcreator.h"

#include "asteroidfield.h"

AsteroidField::AsteroidField(QQuickItem * parent)
    : QQuickPaintedItem(parent)
{
    creator = new AsteroidCreator();
    connect(&creatorThread, &QThread::started, creator, &AsteroidCreator::createAsteroids);
    creator->moveToThread(&creatorThread);
    connect(&creatorThread, &QThread::finished, creator, &QObject::deleteLater);
    connect(creator, &AsteroidCreator::newAsteroid, this, &AsteroidField::asteroidCreated);
}

AsteroidField::~AsteroidField()
{
}

void AsteroidField::paint(QPainter *painter) {
    int w = width();
    int h = height();
    int r = qMin(w, h);

    painter->setPen(Qt::black);
    foreach (Asteroid * a, asteroids) {
        painter->drawEllipse(a->x() * w, a->y() * h, a->size() * r, a->size() * r);
    }
}

void AsteroidField::startField()
{
    qDebug() << "Starting field";
    creatorThread.start();
}

void AsteroidField::asteroidCreated(Asteroid * a)
{
    asteroids.push_back(a);
    update();
}
