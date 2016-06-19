#include "wall.h"

wall::wall(b2World *world):GameItem(world)
{
    dead = false;
    life = 500;
}

void wall::create(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
{

    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(w*2,h*2);

    b2BodyDef bodydef;
    bodydef.position.Set(x,y-h/2);
    bodydef.type = b2_dynamicBody;
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w,h);
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyBox;
    fixturedef.density = Box_DENSITY;
    fixturedef.friction = Box_FRICTION;
    fixturedef.restitution = Box_RESTITUTION;
    paint();
    g_body->CreateFixture(&fixturedef);
    scene->addItem(&g_pixmap);
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
}