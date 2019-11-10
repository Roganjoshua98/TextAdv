//
// Created by DrMark on 10/2/2017.
//

#include "State.h"
#include <forward_list>
#include <list>
using namespace std;

/**
 * Current state of the game.
 */

/**
 * Display the description of the room the player is in. */

void State::announceLoc() const {
    this->currentRoom->describe();
}

/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(const Room *startRoom) : currentRoom(startRoom) {};

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(const Room *target) {
    this->currentRoom = target;
    this->announceLoc();
}

/**
 * Return a pointer to the current room.
 * @return Pointer to the current room.
 */
const Room* State::getCurrentRoom() {
    return this->currentRoom;
}

list<GameObject> State::getInventory() {
    return this->inventory;
}

void State::addItem(GameObject item) {

}
