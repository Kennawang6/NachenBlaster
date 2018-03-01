#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

double euclideanDistance(double x1, double y1, double x2, double y2);

/////////
//Actor//
/////////
Actor::Actor(StudentWorld* world, int imageID, double startX, double startY, int dir, double size, int depth): GraphObject(imageID, startX, startY, dir, size, depth), m_world(world), m_isDead(false), m_isAlien(false){}

Actor::~Actor(){}

StudentWorld* Actor::getWorld(){
    return m_world;
}

bool Actor::isAlive(){
    return !m_isDead;
}

void Actor::setDead(){
    m_isDead = true;
}

void Actor::setAlien(){
    m_isAlien = true;
}

bool Actor::isAlien(){
    return m_isAlien;
}




////////
//Ship//
////////
Ship::Ship(StudentWorld* world, int imageID, double health, double startX, double startY, int dir, double size, int depth): Actor(world, imageID, startX, startY, dir, size, depth), m_health(health){}

Ship::~Ship(){}

double Ship::getHealth(){
    return m_health * 2;
}

void Ship::takeDamage(double amount){
    m_health -= amount;
}



/////////////////
//NachenBlaster//
/////////////////
NachenBlaster::NachenBlaster(StudentWorld* world): Ship(world, IID_NACHENBLASTER, 50, 0, 128, 0, 1.0, 0), m_cabbages(30), m_torpedoes(10){}

NachenBlaster::~NachenBlaster(){}

void NachenBlaster::doSomething(){
    if (!isAlive())
        return;
    int ch;
    
    if(getWorld()->getKey(ch)){
        switch (ch){
            case KEY_PRESS_LEFT:
                if (getX() - 6 >= 0)
                    moveTo(getX() - 6, getY());
                break;
            case KEY_PRESS_RIGHT:
                if (getX() + 6 < VIEW_WIDTH)
                    moveTo(getX() + 6, getY());
                break;
            case KEY_PRESS_UP:
                if (getY() + 6 < VIEW_HEIGHT)
                    moveTo(getX(), getY() + 6);
                break;
            case KEY_PRESS_DOWN:
                if (getY() - 6 >= 0)
                    moveTo(getX(), getY() - 6);
                break;
                //euclidean collisions
            case KEY_PRESS_SPACE:
                if (m_cabbages > 5){
                    getWorld()->addActor(new Cabbage(getWorld(), getX() + 12, getY()));
                    getWorld()->playSound(SOUND_PLAYER_SHOOT);
                    m_cabbages -= 5;
                }
                break;
            case KEY_PRESS_ESCAPE:
                break;
            case KEY_PRESS_TAB:
                if (m_torpedoes > 0){
                    getWorld()->addActor(new FlatulenceTorpedo(getWorld(), getX() + 12, getY(), true));
                    getWorld()->playSound(SOUND_TORPEDO);
                    m_torpedoes--;
                }
                break;
        }
        //check collisions
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



/////////
//Alien//
/////////
Alien::Alien(StudentWorld* world, int imageID, double health, double startX, double startY, double speed, int direction): Ship(world, imageID, health, startX, startY, 0, 1.5, 1), m_travelSpeed(speed), m_flightPlan(0), m_flightDirection(direction){
    setAlien();
}

Alien::~Alien(){}

double Alien::getFlightPlan(){
    return m_flightPlan;
}

void Alien::handleFlightPlan(){
    if (getY() > 0 && getY() < VIEW_HEIGHT - 1 && m_flightPlan > 0)
        return;
    if (getY() <= 0)
        m_flightDirection = 1;
    else if (getY() >= VIEW_HEIGHT - 1)
        m_flightDirection = -1;
    else
        m_flightDirection = randInt(-1, 1);
    m_flightPlan = randInt(1, 32);
}

void Alien::setFlightDirection(int direction){
    m_flightDirection = direction;
}

void Alien::fly(){
    switch (m_flightDirection){
        case -1:
            moveTo(getX() - m_travelSpeed, getY() - m_travelSpeed);
            break;
        case 0:
            moveTo(getX() - m_travelSpeed, getY());
            break;
        case 1:
            moveTo(getX() - m_travelSpeed, getY() + m_travelSpeed);
            break;
    }
    m_flightPlan--;
}

void Alien::fireProjectile(){
    if (getX() > getWorld()->getPlayer()->getX() && getY() >= getWorld()->getPlayer()->getY() - 4 && getY() <= getWorld()->getPlayer()->getY() + 4)
        if (randInt(1, 20 / getWorld()->getLevel() + 5) == 1){
            getWorld()->addActor(new Turnip(getWorld(), getX() - 14, getY()));
            getWorld()->playSound(SOUND_ALIEN_SHOOT);
        }
}



////////////
//Smallgon//
////////////
Smallgon::Smallgon(StudentWorld* world, double health, double startX, double startY): Alien(world, IID_SMALLGON, health, startX, startY, 2.0, 0){}

Smallgon::~Smallgon(){}

void Smallgon::doSomething(){
    if (!isAlive())
        return;
    if (getX() < 0){
        setDead();
        return;
    }
    
    //collision detection
    
    handleFlightPlan();
    fireProjectile();
    fly();
    if (getX() < 0)
        setDead();
}



////////////
//Smoregon//
////////////
Smoregon::Smoregon(StudentWorld* world, double health, double startX, double startY): Alien(world, IID_SMOREGON, health, startX, startY, 2.0, 0){}

Smoregon::~Smoregon(){}

void Smoregon::doSomething(){
    if (!isAlive())
        return;
    if (getX() < 0){
        setDead();
        return;
    }
    
    //collision detection
    
    handleFlightPlan();
    fireProjectile();
    fly();
    if (getX() < 0)
        setDead();
}



//////////////
//Snagglegon//
//////////////
Snagglegon::Snagglegon(StudentWorld* world, double health, double startX, double startY): Alien(world, IID_SNAGGLEGON, health, startX, startY, 1.75, -1){}

Snagglegon::~Snagglegon(){}

void Snagglegon::doSomething(){
    if (!isAlive())
        return;
    if (getX() < 0){
        setDead();
        return;
    }
    
    //collisions
    
    handleFlightPlan();
    fireProjectile();
    fly();
    if (getX() < 0)
        setDead();
}

void Snagglegon::handleFlightPlan(){
    if (getY() >= VIEW_HEIGHT - 1)
        setFlightDirection(-1);
    else if (getY() <= 0)
        setFlightDirection(1);
}



////////
//Star//
////////
Star::Star(StudentWorld* world, double x): Actor(world, IID_STAR, x, randInt(0, VIEW_HEIGHT), 0, randInt(1, 10)/20.0, 3){}

Star::~Star(){}

void Star::doSomething(){
    moveTo(getX() - 1, getY());
}



//////////////
//Projectile//
//////////////
Projectile::Projectile(StudentWorld* world, int imageID, double startX, double startY, int dir): Actor(world, imageID, startX, startY, dir, 0.5, 1){}

Projectile::~Projectile(){}

void Projectile::alienCollsion(double damage){
    Actor* n = getWorld()->getOneCollidingAlien(this);
    if (n == nullptr)
        return;
        
        //decrease n's health
        
        setDead();
}

void Projectile::playerCollsion(double damage){
    NachenBlaster* p = getWorld()->getCollidingPlayer(this);
    if (p == nullptr)
        return;
    p->takeDamage(damage);
    setDead();
}



///////////
//Cabbage//
///////////
Cabbage::Cabbage(StudentWorld* world, double startX, double startY): Projectile(world, IID_CABBAGE, startX, startY){}

Cabbage::~Cabbage(){}

void Cabbage::doSomething(){
    if (!isAlive())
        return;
    if (getX() >= VIEW_WIDTH){
        setDead();
        return;
    }
    
    alienCollsion(2);
    
    moveTo(getX() + 8, getY());
    setDirection(getDirection() + 20);
    
    alienCollsion(2);
}



//////////
//Turnip//
//////////
Turnip::Turnip(StudentWorld* world, double startX, double startY): Projectile(world, IID_TURNIP, startX, startY){}

Turnip::~Turnip(){}

void Turnip::doSomething(){
    if (!isAlive())
        return;
    if (getX() < 0){
        setDead();
        return;
    }
    
    alienCollsion(2);
    
    moveTo(getX() - 6, getY());
    setDirection(getDirection() + 20);
    
    alienCollsion(2);
}



/////////////////////
//FlatulenceTorpedo//
/////////////////////
FlatulenceTorpedo::FlatulenceTorpedo(StudentWorld* world, double startX, double startY, bool fromPlayer): Projectile(world, IID_TORPEDO, startX, startY, 180), m_fromPlayer(fromPlayer){
    if (fromPlayer)
        setDirection(0);
}

FlatulenceTorpedo::~FlatulenceTorpedo(){}

void FlatulenceTorpedo::doSomething(){
    if (!isAlive())
        return;
    if (getX() < 0 || getX() >= VIEW_WIDTH){
        setDead();
        return;
    }
    
    if (m_fromPlayer)
        alienCollsion(8);
    else
        playerCollsion(8);
    
    if (m_fromPlayer)
        moveTo(getX() + 8, getY());
    else
        moveTo(getX() - 8, getY());
    
    if (m_fromPlayer)
        alienCollsion(8);
    else
        playerCollsion(8);
}



/////////////
//Explosion//
/////////////
Explosion::Explosion(StudentWorld* world, double startX, double startY):Actor(world, IID_EXPLOSION, startX, startY, 0, 1, 0), m_ticks(0){
    getWorld()->playSound(SOUND_BLAST);
}

Explosion::~Explosion(){}

void Explosion::doSomething(){
    setSize(1.5 * getSize());
    m_ticks++;
    if (m_ticks >= 4)
        setDead();
}



//////////
//Goodie//
//////////



////////////////
//RepairGoodie//
////////////////



///////////////////
//ExtraLifeGoodie//
///////////////////



/////////////////
//TorpedoGoodie//
/////////////////
