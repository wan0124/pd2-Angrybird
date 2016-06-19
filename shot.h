#ifndef SHOT_H
#define SHOT_H

#include "gameitem.h"
#include "bird.h"
#include <QPixmap>
#include <QGraphicsScene>

#define shot_x 3.8f
#define shot_y 4.5f

class shot : public GameItem
{
public:
    shot(int x, int y, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void ready(Bird *bird);
};

#endif // SHOT_H
