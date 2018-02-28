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
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void fireCabbage();
    void fireTorpedo(bool playerFired, int startX, int startY);
    void killedAlien();
private:
    std::list<Actor*> m_actors;
    NachenBlaster* m_player;
    void updateDisplayText();
    int m_aliensLeft;
};

#endif // STUDENTWORLD_H_
