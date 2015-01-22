#include "asteroidfield.h"

#include <QPainter>

AsteroidField::AsteroidField()
{

}

AsteroidField::~AsteroidField()
{

}

void AsteroidField::paint(QPainter *painter) {
    painter->setPen(Qt::black);
    painter->drawEllipse(100, 100, 100, 100);
}
