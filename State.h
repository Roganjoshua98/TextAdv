//
// Created by DrMark on 10/2/2017.
//

#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H


#include "Room.h"
#include <forward_list>
#include <list>
using namespace std;

class State {
    const Room *currentRoom;
    list<GameObject> inventory;
public:
    explicit State(const Room *startRoom);
    void goTo(const Room *target);
    void announceLoc() const;
    const Room* getCurrentRoom() const;
    list<GameObject> getInventory();
};


#endif //TEXTADV_STATE_H
