#ifndef WALL_H
#define WALL_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define Box_DENSITY 20.0f
#define Box_FRICTION 0.8f
#define Box_RESTITUTION 0.2f

class wall:public GameItem
{
public:
    wall(b2World *world);

    void create(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

};

#endif // WALL_H
