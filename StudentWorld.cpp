#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include <list>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir){
    //initialize new data members?
}

StudentWorld::~StudentWorld(){
    cleanUp();
}

int StudentWorld::init()
{
    m_player = new NachenBlaster(this);
    for (int i = 0; i < 30; i++)
        m_actors.push_back(new Star(this, randInt(0, 255)));
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move(){
    if (!m_player->isAlive())
        return GWSTATUS_PLAYER_DIED;
    m_player->doSomething();
    list<Actor*>::iterator obj = m_actors.begin();
    while (obj != m_actors.end()){
        (*obj)->doSomething(); //why
        if (!(*obj)->isAlive()){
            delete *obj;
            list<Actor*>::iterator temp = obj;
            temp--;
            m_actors.erase(obj);
            obj = temp;
        }
        obj++;
    }
    if (randInt(1, 15) == 1)
        m_actors.push_back(new Star(this));
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp(){
    delete m_player;
    for (list<Actor*>::iterator obj = m_actors.begin(); obj != m_actors.end(); obj++)
        delete *obj;
}
