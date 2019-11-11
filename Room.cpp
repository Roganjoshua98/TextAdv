//
// Created by DrMark on 10/2/2017.
//

#include "Room.h"
#include "wordwrap.h"
#include "strings.h"
#include <algorithm>
#include <iostream>

/**
 * Stores a static list of all rooms.
 */
std::list<Room*> Room::rooms;

/**
 * Room default constructor.
 * @param _name Room's name.
 * @param _desc Room's description.
 */
Room::Room(const string* _name, const string *_desc) :
        name(_name), description(_desc), north(nullptr), south(nullptr), east(nullptr), west(nullptr){};

/**
 * Remove destroyed rooms from the static list.
 */
Room::~Room() {
    Room::rooms.remove(this);
}

/**
 * Prints the description of a room (the name and long description)
 */
void Room::describe() {
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();

    //wrapOut(reinterpret_cast<const string *>("In the room there is: "));
    auto iter = items.begin();
    if (this->items.empty())
        return;
    else {
        cout << "In the room there is: " << endl;
        for (int i = 0; i < items.size(); i++) {
            if (i == items.size()-1) {
                cout << "and a ";
                cout << iter->getName() << endl;
                break;
            }
            cout << "a ";
            cout << iter->getName() << endl;
            advance(iter, 1);
        }
    }// NEEEEEEEEDS WORK
}
/**
 * Statically creates a room and then adds it to the global list.
 * @param _name Name for the new room.
 * @param _desc Description for the new room.
 * @return A pointer to the newly created room.
 */
Room* Room::addRoom(const string* _name, const string *_desc) {
    auto *newRoom = new Room(_name, _desc);
    Room::rooms.push_back(newRoom);
    return newRoom;
}

/**
 * Adds an existing room to the static list.
 * @param room Pointer to the room to add.
 * @return
 */
Room* Room::addRoom(Room* room) {
    Room::rooms.push_back(room);
    return room;
}

/**
 * Sets the north of current room, and the south of the north room
 * @param _north
 */
void Room::configNorth(Room* _north) {
    setNorth(_north);
    _north->setSouth(this);
}
void Room::configSouth(Room* _south) {
    setSouth(_south);
    _south->setNorth(this);
}
void Room::configEast(Room* _east) {
    setEast(_east);
    _east->setWest(this);
}
void Room::configWest(Room* _west) {
    setWest(_west);
    _west->setEast(this);
}

/**
 * Gets the north exit of a room.
 * @return The room that is north of this one, or NULL if there is no exit.
 */
Room* Room::getNorth() const {
    return this->north;
}
Room* Room::getSouth() const {
    return this->south;
}
Room* Room::getEast() const {
    return this->east;
}
Room* Room::getWest() const {
    return this->west;
}

/**
 * Sets the north exit of a room.
 * @param _north Pointer to the room to be north of this one.
 */
void Room::setNorth(Room* _north) {
    this->north = _north;
}
void Room::setSouth(Room* _south) {
    this->south = _south;
}
void Room::setEast(Room* _east) {
    this->east = _east;
}
void Room::setWest(Room* _west) {
    this->west = _west;
}

/**
 * Gets list of items in room
 * @return
 */
list<GameObject> Room::getItems() const {
    return this->items;
}

void Room::addItem(GameObject* _item) {
    this->items.push_back(*_item);
}


GameObject Room::removeItem(string _keyword) {
    auto iter = items.begin();
    while (!_keyword.compare(iter->getKeyword()) == 0) {
        advance(iter, 1);
    }
    GameObject item = *iter;
    this->items.erase(iter);
    return item;
}



