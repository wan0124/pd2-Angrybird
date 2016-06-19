#ifndef BACKBIRD_H
#define BACKBIRD_H

#include "gameitem.h"
#include "bird.h"

#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

class backbird:public Bird
{
public:
    backbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void Special();
};

#endif // BACKBIRD_H
