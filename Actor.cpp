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
    if (m_health < 0){
        setDead();
        getWorld()->playSound(SOUND_DEATH);
        
    }
    else
        getWorld()->playSound(SOUND_BLAST);
}

void Ship::addHealth(double amount){
    m_health += amount;
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
    if (getHealth() <= 0)
        setDead();
}

int NachenBlaster::getCabbages(){
    return m_cabbages / .3;
}

int NachenBlaster::getTorpedoes(){
    return m_torpedoes;
}

void NachenBlaster::repair(){
    if (getHealth() >= 40)
        addHealth(50 - getHealth());
    else
        addHealth(10);
}

void NachenBlaster::incTorpedoes(){
    m_torpedoes += 5;
}

void NachenBlaster::getKilled(){
    setDead();
    getWorld()->playSound(SOUND_DEATH);
}



/////////
//Alien//
/////////
Alien::Alien(StudentWorld* world, int imageID, double health, double startX, double startY, double speed, int direction): Ship(world, imageID, health, startX, startY, 0, 1.5, 1), m_travelSpeed(speed), m_flightDirection(direction){
    setAlien();
}

Alien::~Alien(){}

void Alien::doSomething(){
    if (!isAlive())
        return;
    if (getX() < 0){
        setDead();
        return;
    }
    if (handleCollisions())
        return;
    handleFlightPlan();
    fireProjectile();
    fly();
    handleCollisions();
}

void Alien::setFlightDirection(int direction){
    m_flightDirection = direction;
}

int Alien::getFlightDirection(){
    return m_flightDirection;
}

void Alien::fireProjectile(){
    if (getWorld()->playerInLineOfFire(this))
        shoot();
}

double Alien::getTravelSpeed(){
    return m_travelSpeed;
}

bool Alien::handleCollisions(){
    NachenBlaster* n = getWorld()->getCollidingPlayer(this);
    if (n == nullptr)
        return false;
    collideWithPlayer(n);
    getKilled();
    return true;
}

void Alien::getKilled(){
    setDead();
    getWorld()->recordAlienDestroyed();
    incScore();
    getWorld()->playSound(SOUND_DEATH);
    getWorld()->addActor(new Explosion(getWorld(), getX(), getY()));
}



/////////////
//PoorAlien//
/////////////
PoorAlien::PoorAlien(StudentWorld* world, int imageID, double health, double startX, double startY): Alien(world, imageID, health, startX, startY, 2.0, 0), m_flightPlan(0){}

void PoorAlien::handleFlightPlan(){
    if (getY() > 0 && getY() < VIEW_HEIGHT - 1 && m_flightPlan > 0)
        return;
    if (getY() <= 0)
        setFlightDirection(1);
    else if (getY() >= VIEW_HEIGHT - 1)
        setFlightDirection(-1);
    else
        setFlightDirection(randInt(-1, 1));
    m_flightPlan = randInt(1, 32);
}

void PoorAlien::fly(){
    switch (getFlightDirection()){
        case -1:
            moveTo(getX() - getTravelSpeed(), getY() - getTravelSpeed());
            break;
        case 0:
            moveTo(getX() - getTravelSpeed(), getY());
            break;
        case 1:
            moveTo(getX() - getTravelSpeed(), getY() + getTravelSpeed());
            break;
    }
    m_flightPlan--;
}

void PoorAlien::shoot(){
    if (randInt(1, 20 / getWorld()->getLevel() + 5) == 1){
        getWorld()->addActor(new Turnip(getWorld(), getX() - 14, getY()));
        getWorld()->playSound(SOUND_ALIEN_SHOOT);
    }
}

void PoorAlien::collideWithPlayer(NachenBlaster* player){
    player->takeDamage(5);
}

void PoorAlien::incScore(){
    getWorld()->increaseScore(250);
}



////////////
//Smallgon//
////////////
Smallgon::Smallgon(StudentWorld* world, double health, double startX, double startY): PoorAlien(world, IID_SMALLGON, health, startX, startY){}

Smallgon::~Smallgon(){}



////////////
//Smoregon//
////////////
Smoregon::Smoregon(StudentWorld* world, double health, double startX, double startY): PoorAlien(world, IID_SMOREGON, health, startX, startY){}

Smoregon::~Smoregon(){}

void Smoregon::dropGoodie(){
    if (randInt(1, 3) == 1){
        if (randInt(1, 2) == 1)
            getWorld()->addActor(new RepairGoodie(getWorld(), getX(), getY()));
        else
            getWorld()->addActor(new ExtraLifeGoodie(getWorld(), getX(), getY()));
    }
}

void Smallgon::dropGoodie(){}



//////////////
//Snagglegon//
//////////////
Snagglegon::Snagglegon(StudentWorld* world, double health, double startX, double startY): Alien(world, IID_SNAGGLEGON, health, startX, startY, 1.75, -1){}

Snagglegon::~Snagglegon(){}

void Snagglegon::handleFlightPlan(){
    if (getY() >= VIEW_HEIGHT - 1)
        setFlightDirection(-1);
    else if (getY() <= 0)
        setFlightDirection(1);
}

void Snagglegon::fly(){
    if (getFlightDirection() == 1)
        moveTo(getX() - getTravelSpeed(), getY() + getTravelSpeed());
    if (getFlightDirection() == -1)
        moveTo(getX() - getTravelSpeed(), getY() - getTravelSpeed());
}

void Snagglegon::shoot(){
    if (randInt(1, (15 / getWorld()->getLevel())+10) == 1){
        getWorld()->addActor(new FlatulenceTorpedo(getWorld(), getX() - 14, getY(), false));
        getWorld()->playSound(SOUND_TORPEDO);
    }
}

void Snagglegon::dropGoodie(){
    if (randInt(1, 6) == 1)
        getWorld()->addActor(new FlatulenceTorpedoGoodie(getWorld(), getX(), getY()));
}

void Snagglegon::collideWithPlayer(NachenBlaster* player){
    player->takeDamage(15);
}

void Snagglegon::incScore(){
    getWorld()->increaseScore(1000);
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

void Projectile::doSomething(){
    if (!isAlive())
        return;
    if (getX() < 0){
        setDead();
        return;
    }
    if (handleCollisions())
        return;
    fly();
    handleCollisions();
}

bool Projectile::handlePlayerCollisions(){
    NachenBlaster* n = getWorld()->getCollidingPlayer(this);
    if (n == nullptr)
        return false;
    setDead();
    damage(n);
    return true;
}

bool Projectile::handleAlienCollisions(){ //damage aliens
    Actor* n = getWorld()->getOneCollidingAlien(this);
    if (n == nullptr)
        return false;
    //take damage
    setDead();
    return true;
}




///////////
//Cabbage//
///////////
Cabbage::Cabbage(StudentWorld* world, double startX, double startY): Projectile(world, IID_CABBAGE, startX, startY){}

Cabbage::~Cabbage(){}

void Cabbage::fly(){
    moveTo(getX() + 8, getY());
    setDirection(getDirection() + 20);
}

bool Cabbage::handleCollisions(){
    return handleAlienCollisions();
}

void Cabbage::damage(Ship* target){
    target->takeDamage(2);
}



//////////
//Turnip//
//////////
Turnip::Turnip(StudentWorld* world, double startX, double startY): Projectile(world, IID_TURNIP, startX, startY){}

Turnip::~Turnip(){}

void Turnip::fly(){
    moveTo(getX() - 6, getY());
    setDirection(getDirection() + 20);
}

bool Turnip::handleCollisions(){
    return handlePlayerCollisions();
}

void Turnip::damage(Ship* target){
    target->takeDamage(2);
}



/////////////////////
//FlatulenceTorpedo//
/////////////////////
FlatulenceTorpedo::FlatulenceTorpedo(StudentWorld* world, double startX, double startY, bool fromPlayer): Projectile(world, IID_TORPEDO, startX, startY, 180), m_fromPlayer(fromPlayer){
    if (fromPlayer)
        setDirection(0);
}

FlatulenceTorpedo::~FlatulenceTorpedo(){}

void FlatulenceTorpedo::fly(){
    if (m_fromPlayer)
        moveTo(getX() + 8, getY());
    else
        moveTo(getX() - 8, getY());
}

bool FlatulenceTorpedo::handleCollisions(){
    if (m_fromPlayer)
        return handleAlienCollisions();
    else
        return handlePlayerCollisions();
}

void FlatulenceTorpedo::damage(Ship* target){
    target->takeDamage(8);
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
Goodie::Goodie(StudentWorld* world, int imageID, double startX, double startY): Actor(world, imageID, startX, startY, 0, 0.5, 1){}

void Goodie::doSomething(){
    if (!isAlive())
        return;
    if (handleCollisions())
        return;
    moveTo(getX() - .75, getY() - .75);
    handleCollisions();
}

bool Goodie::handleCollisions(){
    NachenBlaster* p = getWorld()->getCollidingPlayer(this);
    if (p == nullptr)
        return false;
    getWorld()->increaseScore(100);
    notifyPlayer(p);
    setDead();
    getWorld()->playSound(SOUND_GOODIE);
    return true;
}



////////////////
//RepairGoodie//
////////////////
RepairGoodie::RepairGoodie(StudentWorld* world, double startX, double startY): Goodie(world, IID_REPAIR_GOODIE, startX, startY){}

void RepairGoodie::notifyPlayer(NachenBlaster* player){
    player->repair();
}



///////////////////
//ExtraLifeGoodie//
///////////////////
ExtraLifeGoodie::ExtraLifeGoodie(StudentWorld* world, double startX, double startY): Goodie(world, IID_LIFE_GOODIE, startX, startY){}
void ExtraLifeGoodie::notifyPlayer(NachenBlaster* player){
    getWorld()->incLives();
}



///////////////////////////
//FlatulenceTorpedoGoodie//
///////////////////////////
FlatulenceTorpedoGoodie::FlatulenceTorpedoGoodie(StudentWorld* world, double startX, double startY): Goodie(world, IID_TORPEDO_GOODIE, startX, startY){}

void FlatulenceTorpedoGoodie::notifyPlayer(NachenBlaster* player){
    player->incTorpedoes();
}
