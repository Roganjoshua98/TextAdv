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
    Room* currentRoom;
    list<GameObject> inventory;
public:
    explicit State(Room *startRoom);
    void goTo(Room *target);
    void announceLoc() const;
    Room* getCurrentRoom();
    list<GameObject> getInventory();
    void addItem(GameObject item);
    GameObject removeItem(string _keyword);
};


#endif //TEXTADV_STATE_H
