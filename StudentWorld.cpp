#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include <list>
#include <sstream>
#include <cmath>
using namespace std;



GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir){
    m_player = nullptr;
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
    m_nAliens = 0;
    m_player = new NachenBlaster(this);
    for (int i = 0; i < 30; i++)
        m_actors.push_back(new Star(this, randInt(0, VIEW_WIDTH)));
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move(){
    m_player->doSomething();
    
    introduceAlien();
    
    //loops through all actors
    list<Actor*>::iterator obj = m_actors.begin();
    while (obj != m_actors.end()){
        //do something
        if((*obj)->isAlive())
            (*obj)->doSomething();
        //remove dead objects
        if (!(*obj)->isAlive()){
            if ((*obj)->isAlien())
                m_nAliens--;
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

Actor* StudentWorld::getOneCollidingAlien(const Actor* a) const{
    list<Actor*>::const_iterator obj = m_actors.begin();
    while (obj != m_actors.end()){
        if((*obj)->isAlien() && euclideanDistance(a->getX(), a->getY(), (*obj)->getX(), (*obj)->getY()) < .75 * (a->getRadius() + (*obj)->getRadius()))
            return *obj;
        obj++;
    }
    return nullptr;
}

NachenBlaster* StudentWorld::getCollidingPlayer(const Actor* a) const{
    if(euclideanDistance(a->getX(), a->getY(), m_player->getX(), m_player->getY()) < .75 * (a->getRadius() + m_player->getRadius()))
        return m_player;
    else
        return nullptr;
}

bool StudentWorld::playerInLineOfFire(const Actor* a) const{
    if (m_player->getY() - a->getY() <= 4 && m_player->getY() - a->getY() >= -4)
        return true;
    else
        return false;
}

void StudentWorld::addActor(Actor* a){
    m_actors.push_back(a);
}

void StudentWorld::recordAlienDestroyed(){
    m_aliensLeft--;
}

void StudentWorld::updateDisplayText(){
    ostringstream stats;
    stats << "Lives: " << getLives() << " Health: " << m_player->getHealth() << "% Score: " << getScore() << " Level: " << getLevel() << " Cabbages: " << m_player->getCabbages() << "% Torpedoes: " << m_player->getTorpedoes();
    string text = stats.str();
    setGameStatText(text);
}

void StudentWorld::introduceAlien(){
    if (m_nAliens < m_aliensLeft && m_nAliens < 4 + getLevel() / 2){
        //introducing new alien
        int s1 = 60;
        int s2 = 20 + getLevel() * 5;
        int s3 = 5 + getLevel() * 10;
        int r = randInt(1, s1 + s2 + s3);
        if (r <= s1)
            m_actors.push_back(new Smallgon(this, 5 * (1 + (getLevel() - 1) * .1), VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1)));
        if (r > s1 && r <= s1 + s2)
            addActor(new Smoregon(this, 5 * (1 + (getLevel() - 1) * .1), VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1)));
        if (r > s1 + s2)
            addActor(new Snagglegon(this, 10 * (1 + (getLevel() - 1) * .1), VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1)));
        m_nAliens++;
    }
}

double euclideanDistance(double x1, double y1, double x2, double y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
