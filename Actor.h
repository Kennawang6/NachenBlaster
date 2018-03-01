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
    void setDead();
    void setAlien();
    bool isAlien();
    StudentWorld* getWorld();
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
    void takeDamage(double amount);
private:
    double m_health;
};



class NachenBlaster: public Ship{
public:
    NachenBlaster(StudentWorld* world);
    virtual ~NachenBlaster();
    virtual void doSomething();
    int getCabbages();//could become double?
    int getTorpedoes();
private:
    int m_cabbages;
    int m_torpedoes;
};



class Alien: public Ship{
public:
    Alien(StudentWorld* world, int imageID, double health, double startX, double startY, double speed);
    virtual ~Alien();
private:
    double m_travelSpeed;
    int m_flightPlan;
};



class Smallgon: public Alien{
public:
    Smallgon(StudentWorld* world, double health, double startX, double startY);
    virtual ~Smallgon();
    virtual void doSomething();
};



class Smoregon: public Alien{
public:
    Smoregon(StudentWorld* world, double health, double startX, double startY);
    virtual ~Smoregon();
    virtual void doSomething();
};



class Snagglegon: public Alien{
public:
    Snagglegon(StudentWorld* world, double health, double startX, double startY);
    virtual ~Snagglegon();
    virtual void doSomething();
};



class Star: public Actor{
public:
    Star(StudentWorld* world, double x = VIEW_WIDTH); //use no parameters during tick, use randInt during init
    virtual ~Star();
    virtual void doSomething();
};



class Projectile: public Actor{
public:
    Projectile(StudentWorld* world, int imageID, double startX, double startY, int dir = 0);
    virtual ~Projectile();
protected:
    void handleCollsion(int damage);
};



class Cabbage: public Projectile{
public:
    Cabbage(StudentWorld* world, double startX, double startY);
    virtual ~Cabbage();
    virtual void doSomething();
};



class Turnip: public Projectile{
public:
    Turnip(StudentWorld* world, double startX, double startY);
    virtual ~Turnip();
    virtual void doSomething();
};



class FlatulenceTorpedo: public Projectile{
public:
    FlatulenceTorpedo(StudentWorld* world, double startX, double startY, bool fromPlayer);
    virtual ~FlatulenceTorpedo();
    virtual void doSomething();
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
    Goodie(StudentWorld* world, double startX, double startY);
};

class RepairGoodie: public Goodie{
    
};

class ExtraLifeGoodie: public Goodie{
    
};

class FlatulenceTorpedoGoodie: public Goodie{
    
};


#endif // ACTOR_H_
