#ifndef ASTEROID_H
#define ASTEROID_H

#include <QObject>

class Asteroid : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal xVelocity READ xVelocity WRITE setXVelocity NOTIFY xVelocityChanged)
    Q_PROPERTY(qreal yVelocity READ yVelocity WRITE setYVelocity NOTIFY yVelocityChanged)
    Q_PROPERTY(qreal spin READ spin WRITE setSpin NOTIFY spinChanged)
    Q_PROPERTY(qreal rotationalVelocity READ rotationalVelocity WRITE setRotationalVelocity NOTIFY rotationalVelocityChanged)
    Q_PROPERTY(qreal size READ size WRITE setSize NOTIFY sizeChanged)

public:
    explicit Asteroid(qreal x, qreal y, qreal xV, qreal yV, qreal sp, qreal rV, qreal si, QObject *parent = 0);
    ~Asteroid();

    qreal x() const
    {
        return m_x;
    }

    qreal y() const
    {
        return m_y;
    }

    qreal xVelocity() const
    {
        return m_xVelocity;
    }

    qreal yVelocity() const
    {
        return m_yVelocity;
    }

    qreal spin() const
    {
        return m_spin;
    }

    qreal rotationalVelocity() const
    {
        return m_rotationalVelocity;
    }

    qreal size() const
    {
        return m_size;
    }

signals:

    void xChanged(qreal arg);

    void yChanged(qreal arg);

    void xVelocityChanged(qreal arg);

    void yVelocityChanged(qreal arg);

    void spinChanged(qreal arg);

    void rotationalVelocityChanged(qreal arg);

    void sizeChanged(qreal arg);

public slots:
    void setX(qreal arg)
    {
        if (m_x == arg)
            return;

        m_x = arg;
        emit xChanged(arg);
    }
    void setY(qreal arg)
    {
        if (m_y == arg)
            return;

        m_y = arg;
        emit yChanged(arg);
    }
    void setXVelocity(qreal arg)
    {
        if (m_xVelocity == arg)
            return;

        m_xVelocity = arg;
        emit xVelocityChanged(arg);
    }
    void setYVelocity(qreal arg)
    {
        if (m_yVelocity == arg)
            return;

        m_yVelocity = arg;
        emit yVelocityChanged(arg);
    }
    void setSpin(qreal arg)
    {
        if (m_spin == arg)
            return;

        m_spin = arg;
        emit spinChanged(arg);
    }
    void setRotationalVelocity(qreal arg)
    {
        if (m_rotationalVelocity == arg)
            return;

        m_rotationalVelocity = arg;
        emit rotationalVelocityChanged(arg);
    }
    void setSize(qreal arg)
    {
        if (m_size == arg)
            return;

        m_size = arg;
        emit sizeChanged(arg);
    }

protected:
    qreal m_x;

    qreal m_y;

    qreal m_xVelocity;

    qreal m_yVelocity;

    qreal m_spin;

    qreal m_rotationalVelocity;

    qreal m_size;
};

#endif // ASTEROID_H
