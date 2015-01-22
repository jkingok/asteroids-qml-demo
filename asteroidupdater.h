#ifndef ASTEROIDUPDATER_H
#define ASTEROIDUPDATER_H

#include <QObject>

class Asteroid;
class AsteroidProvider;
class QTimer;

class AsteroidUpdater : public QObject
{
    Q_OBJECT
public:
    explicit AsteroidUpdater(AsteroidProvider * provider, QObject *parent = 0);
    ~AsteroidUpdater();

signals:
    updatedAsteroids();

public slots:
    void updateAsteroids();

private slots:
    void nextUpdate();

protected:
    QTimer * timer;

private:
    AsteroidProvider * provider;

};

#endif // ASTEROIDUPDATER_H
