#include "backbird.h"

backbird::backbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{

}

void backbird::Special()
{
    if(fire)
        g_body->SetLinearVelocity(b2Vec2(-20,g_body->GetLinearVelocity().y));
}
