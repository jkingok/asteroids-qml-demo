#include "asteroidfield.h"

#include <QDebug>
#include <QPainter>

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
    painter->setPen(Qt::black);
    foreach (QPoint p, asteroids) {
        painter->drawEllipse(p.x(), p.y(), 100, 100);
    }
}

void AsteroidField::startField()
{
    qDebug() << "Starting field";
    creatorThread.start();
}

void AsteroidField::asteroidCreated(int x, int y)
{
    asteroids.push_back(QPoint(x, y));
    update();
}
