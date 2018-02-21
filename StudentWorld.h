#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class NachenBlaster;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
private:
    std::list<Actor*> m_actors;
    NachenBlaster* m_player;
};

#endif // STUDENTWORLD_H_
