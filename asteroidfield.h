#ifndef ASTEROIDFIELD_H
#define ASTEROIDFIELD_H

#include <QQuickPaintedItem>
#include <QList>
#include <QPoint>
#include <QThread>

#include <asteroidcreator.h>

class AsteroidField : public QQuickPaintedItem
{
    Q_OBJECT

public:
    AsteroidField(QQuickItem * parent = 0);
    ~AsteroidField();

    void paint(QPainter *painter);

public slots:
    void startField();

    void asteroidCreated(int x, int y);

protected:
    QThread creatorThread;
    AsteroidCreator * creator;
    QList<QPoint> asteroids;
};

#endif // ASTEROIDFIELD_H
