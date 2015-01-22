#ifndef ASTEROIDUPDATER_H
#define ASTEROIDUPDATER_H

#include <QObject>

class Asteroid;
class AsteroidProvider;
class QQuickItem;
class QTimer;

class AsteroidUpdater : public QObject
{
    Q_OBJECT
public:
    explicit AsteroidUpdater(AsteroidProvider * provider, QObject *parent = 0);
    ~AsteroidUpdater();

signals:
    void shipDestroyed();
    void bulletCollided(QQuickItem * b);
    void bulletDestroyedAsteroids(int number);
    void updatedAsteroids();

public slots:
    void stopAsteroids();

    void updateAsteroids();

private slots:
    void nextUpdate();

protected:
    QTimer * timer;

    bool m_stopping;

private:
    AsteroidProvider * provider;

};

#endif // ASTEROIDUPDATER_H
