#include "shot.h"

shot::shot(int x, int y, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setPos(x,y);
    scene->addItem(&g_pixmap);
}

void shot::ready(Bird *bird)
{
    bird->shoot = true;
    bird->g_body->SetType(b2_staticBody);
    bird->g_body->SetTransform(b2Vec2(shot_x,shot_y),0);
}
