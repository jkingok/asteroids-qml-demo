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

    Q_PROPERTY(QQuickItem * ship READ ship WRITE setShip NOTIFY shipChanged)
    Q_PROPERTY(int asteroidsShotDown READ asteroidsShotDown WRITE setAsteroidsShotDown NOTIFY asteroidsShotDownChanged)

public:
    AsteroidField(QQuickItem * parent = 0);
    ~AsteroidField();

    void paint(QPainter *painter);

public slots:
    void startField();
    void stopField();

    void asteroidCreated(Asteroid * a);

    void bulletCreated(QObject * item);

    void bulletDestroyed(QObject * item);

    void asteroidsUpdated();

    void setShip(QQuickItem * arg);

    void setAsteroidsShotDown(int arg)
    {
        if (m_asteroidsShotDown == arg)
            return;

        m_asteroidsShotDown = arg;
        emit asteroidsShotDownChanged(arg);
    }

protected:
    QThread taskThread;
    AsteroidCreator * creator;
    AsteroidUpdater * updater;
    QMutex mutex;
    QList<Asteroid *> asteroids;
    QList<QQuickItem *> bullets;
    QQuickItem * m_ship;
    QImage image;
    int m_asteroidsShotDown;

    // AsteroidProvider interface
public:
    QMutex *getMutex() { return &mutex; }
    QList<Asteroid *> *getList() { return &asteroids; }
    QList<QQuickItem *> *getBullets() { return &bullets; }
    QQuickItem * ship() const
    {
        return m_ship;
    }
    int asteroidsShotDown() const
    {
        return m_asteroidsShotDown;
    }

private slots:
    void incrementScore(int by);

signals:
    void shipChanged(QQuickItem * arg);

    void shipDestroyed();
    void bulletCollided(QQuickItem * bullet);
    void asteroidsShotDownChanged(int arg);
};

#endif // ASTEROIDFIELD_H
