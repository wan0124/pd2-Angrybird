#ifndef ROCKBIRD_H
#define ROCKBIRD_H

#include "gameitem.h"
#include "bird.h"

#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

class rockbird:public Bird
{
public:
    rockbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void Special();
};

#endif // ROCKBIRD_H
