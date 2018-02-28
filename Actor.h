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
    virtual bool isAlive() = 0;
    StudentWorld* getWorld();
private:
    StudentWorld* m_world;
};



class Ship: public Actor{ //does ship have any unique stuff?
public:
    Ship(StudentWorld* world, int imageID, int health, double startX, double startY, int dir = 0, double size = 1.0, int depth = 0);
    virtual ~Ship();
    virtual bool isAlive() = 0;
    virtual void doSomething() = 0;
    int getHealth();
private:
    int m_health;
};



class NachenBlaster: public Ship{
public:
    NachenBlaster(StudentWorld* world);
    virtual ~NachenBlaster();
    virtual bool isAlive();
    virtual void doSomething();
    int getCabbages();//could become double?
    int getTorpedoes();
private:
    int m_cabbages;
    int m_torpedoes;
};



class Alien: public Ship{
public:
    Alien(StudentWorld* world, int imageID, int health, double startX, double startY, int dir = 0, double speed = 2.0);
    virtual ~Alien();
    virtual bool isAlive() = 0;
    virtual void doSomething() = 0;
private:
    double m_travelSpeed;
};


//may need regrouping to combine smoregon and smallgon?
class Smallgon: public Alien{
public:
    Smallgon(StudentWorld* world);
    virtual ~Smallgon();
private:
    int m_flightPlan;
};



class Smoregon: public Alien{
public:
    Smoregon(StudentWorld* world);
    virtual ~Smoregon();
private:
    int m_flightPlan;
};



class Snagglegon: public Alien{
public:
    Snagglegon(StudentWorld* world);
    virtual ~Snagglegon();
};



class Star: public Actor{
public:
    Star(StudentWorld* world, int x = VIEW_WIDTH); //use no parameters during tick, use randInt during init
    virtual ~Star();
    virtual bool isAlive();
    virtual void doSomething();
};



class Projectile: public Actor{
public:
    Projectile(StudentWorld* world, int imageID, int startX, int startY, int dir = 0);
    virtual ~Projectile();
    virtual void doSomething() = 0;
    virtual bool isAlive() = 0;
};



class Cabbage: public Projectile{
public:
    Cabbage(StudentWorld* world, int startX, int startY);
    virtual ~Cabbage();
    virtual void doSomething();
    virtual bool isAlive();
};



class Turnip: public Projectile{
public:
    Turnip(StudentWorld* world, int startX, int startY);
    virtual ~Turnip();
    virtual void doSomething();
    virtual bool isAlive();
};



class FlatulenceTorpedo: public Projectile{
public:
    FlatulenceTorpedo(StudentWorld* world, int startX, int startY, bool fromPlayer);
    virtual ~FlatulenceTorpedo();
    virtual bool isAlive();
    virtual void doSomething();
private:
    bool m_fromPlayer;
};



class Explosion: public Actor{
public:
    Explosion(StudentWorld* world, double startX, double startY);
    virtual ~Explosion();
    virtual void doSomething();
    virtual bool isAlive();
};



class Goodie: public Actor{
    
};

class RepairGoodie: public Goodie{
    
};

class ExtraLifeGoodie: public Goodie{
    
};

class FlatulenceTorpedoGoodie: public Goodie{
    
};


#endif // ACTOR_H_
