#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;



class Actor: public GraphObject{
public:
    Actor(StudentWorld* world, int imageID, double startX, double startY, int dir = 0, double size = 1.0, int depth = 0);
    virtual void doSomething() = 0;
    virtual bool isAlive() = 0;
    StudentWorld* getWorld();
private:
    StudentWorld* m_world;
};



class NachenBlaster: public Actor{
public:
    NachenBlaster(StudentWorld* world);
    virtual bool isAlive();
    virtual void doSomething();
private:
    int m_cabbages;
    int m_torpedoes;
    int m_health;
};



/*
class Alien: public Actor{
    
};

class Smallgon: public Alien{
    
};

class Smoregon: public Alien{
    
};

class Snagglegon: public Alien{
    
};
 */



class Star: public Actor{
public:
    Star(StudentWorld* world, int x = 255); //use no parameters during tick, use randInt during init
    virtual bool isAlive();
    virtual void doSomething();
};



/*
class Projectile: public Actor{
    
};

class Cabbage: public Projectile{
    
};

class Turnip: public Projectile{
    
};
class FlatulenceTorpedo: public Projectile{
    
};

class Explosion: public Actor{
    
};

class Goodie: public Actor{
    
};

class RepairGoodie: public Goodie{
    
};

class ExtraLifeGoodie: public Goodie{
    
};

class FlatulenceTorpedoGoodie: public Goodie{
    
};
*/

#endif // ACTOR_H_
