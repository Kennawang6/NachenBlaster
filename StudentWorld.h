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
    Actor* getOneCollidingAlien(const Actor* a) const;
    NachenBlaster* getCollidingPlayer(const Actor* a) const;
    bool playerInLineOfFire(const Actor* a) const;
    void addActor(Actor* a);
    void recordAlienDestroyed();
    NachenBlaster* getPlayer();
private:
    std::list<Actor*> m_actors;
    NachenBlaster* m_player;
    void updateDisplayText();
    int m_aliensLeft;
    int m_nAliens;
    void introduceAlien();
};

double euclideanDistance(double x1, double y1, double x2, double y2);

#endif // STUDENTWORLD_H_
