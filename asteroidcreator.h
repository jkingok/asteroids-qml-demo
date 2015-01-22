#ifndef ASTEROIDCREATOR_H
#define ASTEROIDCREATOR_H

#include <QObject>

class Asteroid;
class QTimer;

class AsteroidCreator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int creationInterval READ creationInterval WRITE setCreationInterval NOTIFY creationIntervalChanged)
    Q_PROPERTY(int minPerInterval READ minPerInterval WRITE setMinPerInterval NOTIFY minPerIntervalChanged)
    Q_PROPERTY(int maxPerInterval READ maxPerInterval WRITE setMaxPerInterval NOTIFY maxPerIntervalChanged)
    Q_PROPERTY(qreal minSize READ minSize WRITE setMinSize NOTIFY minSizeChanged)
    Q_PROPERTY(qreal maxSize READ maxSize WRITE setMaxSize NOTIFY maxSizeChanged)
    Q_PROPERTY(qreal minPrimaryVelocity READ minPrimaryVelocity WRITE setMinPrimaryVelocity NOTIFY minPrimaryVelocityChanged)
    Q_PROPERTY(qreal maxPrimaryVelocity READ maxPrimaryVelocity WRITE setMaxPrimaryVelocity NOTIFY maxPrimaryVelocityChanged)

public:
    explicit AsteroidCreator(QObject *parent = 0);
    ~AsteroidCreator();

    int creationInterval() const
    {
        return m_creationInterval;
    }

    int minPerInterval() const
    {
        return m_minPerInterval;
    }

    int maxPerInterval() const
    {
        return m_maxPerInterval;
    }

    qreal minSize() const
    {
        return m_minSize;
    }

    qreal maxSize() const
    {
        return m_maxSize;
    }

    qreal minPrimaryVelocity() const
    {
        return m_minPrimaryVelocity;
    }

    qreal maxPrimaryVelocity() const
    {
        return m_maxPrimaryVelocity;
    }

signals:
    newAsteroid(Asteroid * asteroid);

    void creationIntervalChanged(int arg);

    void minPerIntervalChanged(int arg);

    void maxPerIntervalChanged(int arg);

    void minSizeChanged(qreal arg);

    void maxSizeChanged(qreal arg);

    void minPrimaryVelocityChanged(qreal arg);

    void maxPrimaryVelocityChanged(qreal arg);

public slots:
    void createAsteroids();

    void setCreationInterval(int arg)
    {
        if (m_creationInterval == arg)
            return;

        m_creationInterval = arg;
        emit creationIntervalChanged(arg);
    }

    void setMinPerInterval(int arg)
    {
        if (m_minPerInterval == arg)
            return;

        m_minPerInterval = arg;
        emit minPerIntervalChanged(arg);
    }

    void setMaxPerInterval(int arg)
    {
        if (m_maxPerInterval == arg)
            return;

        m_maxPerInterval = arg;
        emit maxPerIntervalChanged(arg);
    }

    void setMinSize(qreal arg)
    {
        if (m_minSize == arg)
            return;

        m_minSize = arg;
        emit minSizeChanged(arg);
    }

    void setMaxSize(qreal arg)
    {
        if (m_maxSize == arg)
            return;

        m_maxSize = arg;
        emit maxSizeChanged(arg);
    }

    void setMinPrimaryVelocity(qreal arg)
    {
        if (m_minPrimaryVelocity == arg)
            return;

        m_minPrimaryVelocity = arg;
        emit minPrimaryVelocityChanged(arg);
    }

    void setMaxPrimaryVelocity(qreal arg)
    {
        if (m_maxPrimaryVelocity == arg)
            return;

        m_maxPrimaryVelocity = arg;
        emit maxPrimaryVelocityChanged(arg);
    }

private slots:
    void nextAsteroid();

protected:
    QTimer * timer;

    int m_creationInterval;

    int m_minPerInterval;

    int m_maxPerInterval;

    qreal m_minSize;

    qreal m_maxSize;

    qreal m_minPrimaryVelocity;

    qreal m_maxPrimaryVelocity;

};

#endif // ASTEROIDCREATOR_H
