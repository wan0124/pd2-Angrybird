#ifndef BOOM_H
#define BOOM_H

#include "gameitem.h"

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>


class boom:public b2ContactListener
{
public:
    boom();
    void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};

#endif // BOOM_H
