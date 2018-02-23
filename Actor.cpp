#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/////////
//Actor//
/////////
Actor::Actor(StudentWorld* world, int imageID, double startX, double startY, int dir, double size, int depth): GraphObject(imageID, startX, startY, dir, size, depth), m_world(world){

}

StudentWorld* Actor::getWorld(){
    return m_world;
}



/////////////////
//NachenBlaster//
/////////////////
NachenBlaster::NachenBlaster(StudentWorld* world): Actor(world, IID_NACHENBLASTER, 0, 128), m_cabbages(30), m_torpedoes(0), m_health(50){
    
}

bool NachenBlaster::isAlive(){
    if (m_health < 0)
        return false;
    else
        return true;
}

void NachenBlaster::doSomething(){
    if (!isAlive())
        return;
    int ch;
    if(getWorld()->getKey(ch)){
        switch (ch){
            case KEY_PRESS_LEFT:
                if (getX() > 5)
                    moveTo(getX() - 6, getY());
                break;
            case KEY_PRESS_RIGHT:
                if (getX() < VIEW_WIDTH - 5)
                    moveTo(getX() + 6, getY());
                break;
            case KEY_PRESS_UP:
                if (getY() < VIEW_HEIGHT - 5)
                    moveTo(getX(), getY() + 6);
                break;
            case KEY_PRESS_DOWN:
                if (getY() > 5)
                    moveTo(getX(), getY() - 6);
                break;
            
            //case KEY_SPACE:
            //case KEY_PRESS_ESCAPE:
            //case KEY_PRESS_TAB:
        }
    }
}

int NachenBlaster::getCabbages(){
    return m_cabbages / .3;
}

int NachenBlaster::getTorpedoes(){
    return m_torpedoes;
}

int NachenBlaster::getHealth(){
    return m_health * 2;
}



////////
//Star//
////////
Star::Star(StudentWorld* world, int x): Actor(world, IID_STAR, x, randInt(0, VIEW_HEIGHT), 0, randInt(1, 10)/20.0, 3){
    //for init
}

bool Star::isAlive(){
    if (getX() >= 0)
        return true;
    else
        return false;
}

void Star::doSomething(){
    moveTo(getX() - 1, getY());
}
