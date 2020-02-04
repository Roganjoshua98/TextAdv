//
// Created by Joshua Reyes-Traverso.
//

#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H


#include "Room.h"
using namespace std;

class State {
    Room* currentRoom;
    vector<GameObject*> inventory;
public:
    explicit State(Room *startRoom);
    void goTo(Room *target);
    void announceLoc() const;
    Room* getCurrentRoom();
    vector<GameObject*> getInventory();
    void addItem(GameObject* item);
    GameObject* removeItem(int index);
};


#endif //TEXTADV_STATE_H
