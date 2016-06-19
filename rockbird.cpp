#include "rockbird.h"

rockbird::rockbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{

}

void rockbird::Special()
{
    if(fire)
        g_body->SetLinearVelocity(b2Vec2(0,-20));
}
