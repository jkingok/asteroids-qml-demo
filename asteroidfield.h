#ifndef ASTEROIDFIELD_H
#define ASTEROIDFIELD_H

#include <QQuickPaintedItem>

class AsteroidField : public QQuickPaintedItem
{
public:
    AsteroidField();
    ~AsteroidField();

    void paint(QPainter *painter);
};

#endif // ASTEROIDFIELD_H
