#ifndef ASTEROIDPROVIDER_H
#define ASTEROIDPROVIDER_H

#include <QList>

class Asteroid;
class QMutex;
class QQuickItem;

class AsteroidProvider {
public:
    virtual QMutex * getMutex() =0;
    virtual QList<Asteroid *> * getList() =0;
    virtual QList<QQuickItem *> * getBullets() =0;
    virtual QQuickItem * ship() const =0;
};

#endif // ASTEROIDPROVIDER_H

