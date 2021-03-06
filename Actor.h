#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;



class Actor: public GraphObject{
public:
    Actor(StudentWorld* world, int imageID, double startX, double startY, int dir = 0, double size = 1.0, int depth = 0);
    virtual ~Actor();
    virtual void doSomething() = 0;
    bool isAlive();
    bool isAlien();
    virtual void takeDamage(double damage);
protected:
    StudentWorld* getWorld();
    void setDead();
    void setAlien();
private:
    StudentWorld* m_world;
    bool m_isDead;
    bool m_isAlien;
};



class Ship: public Actor{
public:
    Ship(StudentWorld* world, int imageID, double health, double startX, double startY, int dir, double size, int depth);
    virtual ~Ship();
    double getHealth();
    virtual void getKilled() = 0;
    virtual void takeDamage(double amount);
    void addHealth(double amount);
private:
    double m_health;
};



class NachenBlaster: public Ship{
public:
    NachenBlaster(StudentWorld* world);
    virtual ~NachenBlaster();
    virtual void doSomething();
    int getCabbages();
    int getTorpedoes();
    void repair();
    void incTorpedoes();
    virtual void getKilled();
private:
    int m_cabbages;
    int m_torpedoes;
};



class Alien: public Ship{
public:
    Alien(StudentWorld* world, int imageID, double health, double startX, double startY, double speed, int direction);
    virtual ~Alien();
    virtual void doSomething();
    virtual void handleFlightPlan() = 0;
    virtual void fly() = 0; //using flight direction
    int getFlightDirection();
    virtual void shoot() = 0;
    virtual void dropGoodie() = 0;
    virtual void collideWithPlayer(NachenBlaster* player) = 0;
    virtual void getKilled();
    virtual void incScore() = 0;
protected:
    void setFlightDirection(int direction);
    double getTravelSpeed();
private:
    double m_travelSpeed;
    int m_flightDirection; //up: 1, left: 0, down: -1
    virtual bool handleCollisions();
};



class PoorAlien: public Alien{
public:
    PoorAlien(StudentWorld* world, int imageID, double health, double startX, double startY);
    virtual void handleFlightPlan();
    virtual void fly();
    virtual void shoot();
    virtual void collideWithPlayer(NachenBlaster* player);
    virtual void incScore();
private:
    int m_flightPlan;
};



class Smallgon: public PoorAlien{
public:
    Smallgon(StudentWorld* world, double health, double startX, double startY);
    virtual ~Smallgon();
    virtual void dropGoodie();
};



class Smoregon: public PoorAlien{
public:
    Smoregon(StudentWorld* world, double health, double startX, double startY);
    virtual ~Smoregon();
    virtual void dropGoodie();
};



class Snagglegon: public Alien{
public:
    Snagglegon(StudentWorld* world, double health, double startX, double startY);
    virtual ~Snagglegon();
    virtual void handleFlightPlan();
    virtual void fly();
    virtual void shoot();
    virtual void dropGoodie();
    virtual void collideWithPlayer(NachenBlaster* player);
    virtual void incScore();
};



class Star: public Actor{
public:
    Star(StudentWorld* world, double x = VIEW_WIDTH - 1); //use no parameters during tick, use randInt during init
    virtual ~Star();
    virtual void doSomething();
};



class Projectile: public Actor{
public:
    Projectile(StudentWorld* world, int imageID, double startX, double startY, int dir = 0);
    virtual void doSomething();
    virtual void fly() = 0;
    virtual ~Projectile();
    virtual void damage(Actor* target) = 0;
    virtual bool handleCollisions() = 0; //redirects to player/alien
protected:
    virtual bool handlePlayerCollisions();
    virtual bool handleAlienCollisions(); //calls damage
};



class Cabbage: public Projectile{
public:
    Cabbage(StudentWorld* world, double startX, double startY);
    virtual ~Cabbage();
    virtual void fly();
    virtual bool handleCollisions();
    virtual void damage(Actor* target);
};



class Turnip: public Projectile{
public:
    Turnip(StudentWorld* world, double startX, double startY);
    virtual ~Turnip();
    virtual void fly();
    virtual void damage(Actor* target);
    virtual bool handleCollisions();
};



class FlatulenceTorpedo: public Projectile{
public:
    FlatulenceTorpedo(StudentWorld* world, double startX, double startY, bool fromPlayer);
    virtual ~FlatulenceTorpedo();
    virtual void fly();
    virtual bool handleCollisions();
    virtual void damage(Actor* target);
private:
    bool m_fromPlayer;
};



class Explosion: public Actor{
public:
    Explosion(StudentWorld* world, double startX, double startY);
    virtual ~Explosion();
    virtual void doSomething();
private:
    int m_ticks;
};



class Goodie: public Actor{
public:
    Goodie(StudentWorld* world, int imageID, double startX, double startY);
    virtual ~Goodie();
    virtual void doSomething();
    virtual void notifyPlayer(NachenBlaster* player) = 0;
protected:
    virtual bool handleCollisions();
};



class RepairGoodie: public Goodie{
public:
    RepairGoodie(StudentWorld* world, double startX, double startY);
    virtual ~RepairGoodie();
    virtual void notifyPlayer(NachenBlaster* player);
};



class ExtraLifeGoodie: public Goodie{
public:
    ExtraLifeGoodie(StudentWorld* world, double startX, double startY);
    virtual ~ExtraLifeGoodie();
    virtual void notifyPlayer(NachenBlaster* player);
};



class FlatulenceTorpedoGoodie: public Goodie{
public:
    FlatulenceTorpedoGoodie(StudentWorld* world, double startX, double startY);
    virtual ~FlatulenceTorpedoGoodie();
    virtual void notifyPlayer(NachenBlaster* player);
};



#endif // ACTOR_H_
