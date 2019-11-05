//
// Created by DrMark on 10/2/2017.
//

#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H


#include "Room.h"

class State {
    const Room *currentRoom;
public:
    explicit State(const Room *startRoom);
    void goTo(const Room *target);
    void announceLoc() const;
    const Room* getCurrentRoom() const;
};


#endif //TEXTADV_STATE_H
