#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include <list>
#include <sstream>
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
    m_player->doSomething();
    
    //doSomething loop
    list<Actor*>::iterator obj = m_actors.begin();
    while (obj != m_actors.end()){
        if((*obj)->isAlive())
            (*obj)->doSomething();
        if (!m_player->isAlive())
            return GWSTATUS_PLAYER_DIED;
        //if required ships killed, next level
        obj++;
    }
    
    //removeDeadObjects loop
    obj = m_actors.begin();
    while (obj != m_actors.end()){
        if (!(*obj)->isAlive()){
            delete *obj;
            list<Actor*>::iterator temp = obj;
            temp--;
            m_actors.erase(obj);
            obj = temp;
        }
        obj++;
    }
    
    //stars
    if (randInt(1, 15) == 1)
        m_actors.push_back(new Star(this));
    
    updateDisplayText();
    
    //next tick
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp(){
    delete m_player;
    for (list<Actor*>::iterator obj = m_actors.begin(); obj != m_actors.end(); obj++)
        delete *obj;
}

void StudentWorld::updateDisplayText(){
    ostringstream stats;
    stats << "Lives: " << getLives() << " Health: " << m_player->getHealth() << "% Score: " << getScore() << " Level: " << getLevel() << " Cabbages: " << m_player->getCabbages() << "% Torpedoes: " << m_player->getTorpedoes();
    string text = stats.str();
    setGameStatText(text);
}
