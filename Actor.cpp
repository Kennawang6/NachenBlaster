#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/////////
//Actor//
/////////
Actor::Actor(StudentWorld* world, int imageID, double startX, double startY, int dir, double size, int depth): GraphObject(imageID, startX, startY, dir, size, depth), m_world(world){

}

Actor::~Actor(){}

StudentWorld* Actor::getWorld(){
    return m_world;
}



////////
//Ship//
////////
Ship::Ship(StudentWorld* world, int imageID, int health, double startX, double startY, int dir, double size, int depth): Actor(world, imageID, startX, startY, dir, size, depth), m_health(health){

}

Ship::~Ship(){}

int Ship::getHealth(){
    return m_health * 2;
}



/////////
//Alien//
/////////
Alien::Alien(StudentWorld* world, int imageID, int health, double startX, double startY, int dir, double speed): Ship(world, imageID, health, startX, startY, dir, 1.5, 1), m_travelSpeed(speed){
    
}

Alien::~Alien(){
    getWorld()->killedAlien();
}



////////////
//Smallgon//
////////////
//Smallgon::Smallgon(StudentWorld* world): Alien(world, IID_SMALLGON, 5 * (1 + (world->getLevel() – 1) * .1), x, y)



/////////////////
//NachenBlaster//
/////////////////
NachenBlaster::NachenBlaster(StudentWorld* world): Ship(world, IID_NACHENBLASTER, 50, 0, 128), m_cabbages(30), m_torpedoes(10){
    
}

NachenBlaster::~NachenBlaster(){}

bool NachenBlaster::isAlive(){
    if (getHealth() < 0)
        return false;
    else
        return true;
}

void NachenBlaster::doSomething(){
    if (!isAlive())
        return;
    int ch;
    
    if(getWorld()->getKey(ch)){
        switch (ch){
            case KEY_PRESS_LEFT:
                if (getX() > 5)
                    moveTo(getX() - 6, getY());
                break;
            case KEY_PRESS_RIGHT:
                if (getX() < VIEW_WIDTH - 5)
                    moveTo(getX() + 6, getY());
                break;
            case KEY_PRESS_UP:
                if (getY() < VIEW_HEIGHT - 5)
                    moveTo(getX(), getY() + 6);
                break;
            case KEY_PRESS_DOWN:
                if (getY() > 5)
                    moveTo(getX(), getY() - 6);
                break;
            //euclidean collisions
            case KEY_PRESS_SPACE:
                if (m_cabbages > 5){
                    getWorld()->fireCabbage();
                    m_cabbages -= 5;
                }
                break;
            case KEY_PRESS_ESCAPE:
                break;
            case KEY_PRESS_TAB:
                if (m_torpedoes > 0){
                    getWorld()->fireTorpedo(true, getX() + 12, getY());
                    m_torpedoes--;
                }
                break;
        }
    }
    if (m_cabbages < 30)
        m_cabbages++;
}

int NachenBlaster::getCabbages(){
    return m_cabbages / .3;
}

int NachenBlaster::getTorpedoes(){
    return m_torpedoes;
}



////////
//Star//
////////
Star::Star(StudentWorld* world, int x): Actor(world, IID_STAR, x, randInt(0, VIEW_HEIGHT), 0, randInt(1, 10)/20.0, 3){
    //for init
}

Star::~Star(){}

bool Star::isAlive(){
    if (getX() >= 0)
        return true;
    else
        return false;
}

void Star::doSomething(){
    moveTo(getX() - 1, getY());
}



//////////////
//Projectile//
//////////////
Projectile::Projectile(StudentWorld* world, int imageID, int startX, int startY, int dir): Actor(world, imageID, startX, startY, dir, 0.5, 1){}

Projectile::~Projectile(){}



///////////
//Cabbage//
///////////
Cabbage::Cabbage(StudentWorld* world, int startX, int startY): Projectile(world, IID_CABBAGE, startX, startY){}

Cabbage::~Cabbage(){}

void Cabbage::doSomething(){
    if (!isAlive())
        return;
    moveTo(getX() + 8, getY());
    setDirection(getDirection() + 20);
}

bool Cabbage::isAlive(){
    if (getX() > VIEW_WIDTH)
        return false;
    //also euclidian collisions
    return true;
}



/////////////////////
//FlatulenceTorpedo//
/////////////////////
FlatulenceTorpedo::FlatulenceTorpedo(StudentWorld* world, int startX, int startY, bool fromPlayer): Projectile(world, IID_TORPEDO, startX, startY, 180), m_fromPlayer(fromPlayer){
    if (fromPlayer)
        setDirection(0);
}

FlatulenceTorpedo::~FlatulenceTorpedo(){}

bool FlatulenceTorpedo::isAlive(){
    if (getX() < 0 || getX() > VIEW_WIDTH)
        return false;
    //euclid
    return true;
}

void FlatulenceTorpedo::doSomething(){
    if (!isAlive())
        return;
    if (m_fromPlayer)
        moveTo(getX() + 8, getY());
    else
        moveTo(getX() - 8, getY());
}



/////////////
//Explosion//
/////////////
Explosion::Explosion(StudentWorld* world, double startX, double startY):Actor(world, IID_EXPLOSION, startX, startY, 0, 1, 0){}

Explosion::~Explosion(){}

void Explosion::doSomething(){
    setSize(1.5 * getSize());
}

bool Explosion::isAlive(){
    if (getSize() > 5)
        return false;
    return true;
}
