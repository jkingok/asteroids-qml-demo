#ifndef ASTEROIDFIELD_H
#define ASTEROIDFIELD_H

#include <QImage>
#include <QQuickPaintedItem>
#include <QList>
#include <QMutex>
#include <QPoint>
#include <QThread>

#include "asteroidprovider.h"

class Asteroid;
class AsteroidCreator;
class AsteroidUpdater;

class AsteroidField : public QQuickPaintedItem, public AsteroidProvider
{
    Q_OBJECT

public:
    AsteroidField(QQuickItem * parent = 0);
    ~AsteroidField();

    void paint(QPainter *painter);

public slots:
    void startField();

    void asteroidCreated(Asteroid * a);

    void asteroidsUpdated();

protected:
    QThread taskThread;
    AsteroidCreator * creator;
    AsteroidUpdater * updater;
    QMutex mutex;
    QList<Asteroid *> asteroids;
    QImage image;

    // AsteroidProvider interface
public:
    QMutex *getMutex() { return &mutex; }
    QList<Asteroid *> *getList() { return &asteroids; }
};

#endif // ASTEROIDFIELD_H
