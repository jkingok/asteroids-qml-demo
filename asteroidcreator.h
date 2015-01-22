#ifndef ASTEROIDCREATOR_H
#define ASTEROIDCREATOR_H

#include <QObject>

class QTimer;

class AsteroidCreator : public QObject
{
    Q_OBJECT
public:
    explicit AsteroidCreator(QObject *parent = 0);
    ~AsteroidCreator();

signals:
    newAsteroid(int x, int y);

public slots:
    void createAsteroids();

private slots:
    void nextAsteroid();

protected:
    QTimer * timer;

};

#endif // ASTEROIDCREATOR_H
