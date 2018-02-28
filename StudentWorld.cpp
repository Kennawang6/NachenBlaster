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
    for (list<Actor*>::iterator obj = m_actors.begin(); obj != m_actors.end(); obj++)
        delete *obj;
    delete m_player;
}

int StudentWorld::init()
{
    m_aliensLeft = 6 + getLevel() * 4;
    m_player = new NachenBlaster(this);
    for (int i = 0; i < 30; i++)
        m_actors.push_back(new Star(this, randInt(0, VIEW_WIDTH)));
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move(){
    m_player->doSomething();
    
    //loops through all actors
    list<Actor*>::iterator obj = m_actors.begin();
    while (obj != m_actors.end()){
        //do something
        if((*obj)->isAlive())
            (*obj)->doSomething();
        //remove dead objects
        if (!(*obj)->isAlive()){
            delete (*obj);
            list<Actor*>::iterator temp = obj;
            temp--;
            m_actors.erase(obj);
            obj = temp;
        }
        if (!m_player->isAlive())
            return GWSTATUS_PLAYER_DIED;
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
    m_player = nullptr;
    while (!m_actors.empty()){
        delete *m_actors.begin();
        m_actors.pop_front();
    }
}

void StudentWorld::fireCabbage(){
    m_actors.push_back(new Cabbage(this, m_player->getX() + 12, m_player->getY()));
    playSound(SOUND_PLAYER_SHOOT);
}

void StudentWorld::fireTorpedo(bool playerFired, int startX, int startY){
    m_actors.push_back(new FlatulenceTorpedo(this, startX, startY, playerFired));
    playSound(SOUND_TORPEDO);
}

void StudentWorld::killedAlien(){
    m_aliensLeft--;
}

void StudentWorld::updateDisplayText(){
    ostringstream stats;
    stats << "Lives: " << getLives() << " Health: " << m_player->getHealth() << "% Score: " << getScore() << " Level: " << getLevel() << " Cabbages: " << m_player->getCabbages() << "% Torpedoes: " << m_player->getTorpedoes();
    string text = stats.str();
    setGameStatText(text);
}
