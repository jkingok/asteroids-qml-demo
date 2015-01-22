#ifndef ASTEROIDPROVIDER_H
#define ASTEROIDPROVIDER_H

#include <QList>

class Asteroid;
class QMutex;

class AsteroidProvider {
public:
    virtual QMutex * getMutex() =0;
    virtual QList<Asteroid *> * getList() =0;
};

#endif // ASTEROIDPROVIDER_H

