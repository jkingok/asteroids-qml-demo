#include "asteroid.h"

Asteroid::Asteroid(qreal x, qreal y, qreal xV, qreal yV, qreal sp, qreal rV, qreal si, QObject *parent) : QObject(parent),
    m_x(x), m_y(y), m_xVelocity(xV), m_yVelocity(yV), m_spin(sp), m_rotationalVelocity(rV), m_size(si)
{

}

Asteroid::~Asteroid()
{

}

