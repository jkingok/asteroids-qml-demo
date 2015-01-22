#ifndef ASTEROIDFIELD_H
#define ASTEROIDFIELD_H

#include <QQuickPaintedItem>
#include <QList>
#include <QPoint>
#include <QThread>

class Asteroid;
class AsteroidCreator;

class AsteroidField : public QQuickPaintedItem
{
    Q_OBJECT

public:
    AsteroidField(QQuickItem * parent = 0);
    ~AsteroidField();

    void paint(QPainter *painter);

public slots:
    void startField();

    void asteroidCreated(Asteroid * a);

protected:
    QThread creatorThread;
    AsteroidCreator * creator;
    QList<Asteroid *> asteroids;
};

#endif // ASTEROIDFIELD_H
