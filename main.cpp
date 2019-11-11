
#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include <strings.h>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"


using std::string;
using std::unique_ptr;

string commandBuffer;
State *currentState;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() {
    auto* r1 = new Room(&r1name, &r1desc);
    Room::addRoom(r1);
    auto* r2 = new Room(&r2name, &r2desc);
    Room::addRoom(r2);
    auto* r3 = new Room(&r3name, &r3desc);
    auto* r4 = new Room(&r4name, &r4desc);
    auto* r5 = new Room(&r5name, &r5desc);
    auto* i1 = new GameObject(i1name, i1desc, i1key);
    //GameObject::addObject(i1);
    auto* i2 = new GameObject(i2name, i2desc, i2key);
    //GameObject::addObject(i2);
    r1->configSouth(r2);
    r1->configEast(r3);
    r1->configWest(r4);
    r1->configNorth(r5);
    r1->addItem(i1);
    r1->addItem(i2);
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
    auto* i3 = new GameObject(i3name, i3desc, i3key);
    //GameObject::addObject(i3);
    auto* i4 = new GameObject(i4name, i4desc, i4key);
    //GameObject::addObject(i4);
    currentState->addItem(*i3);
    currentState->addItem(*i4);
}

/**
 * Moves player to specified room
 * @param direction
 */
void goToRoom(char direction) {
    Room *destinationRoom = nullptr;
    /* Determine which direction user inputted */
    if (direction == 'n')
        destinationRoom = currentState->getCurrentRoom()->getNorth();
    else if (direction == 's')
        destinationRoom = currentState->getCurrentRoom()->getSouth();
    else if (direction == 'e')
        destinationRoom = currentState->getCurrentRoom()->getEast();
    else if (direction == 'w')
        destinationRoom = currentState->getCurrentRoom()->getWest();

    if (destinationRoom == nullptr) { /* there isn't */
        wrapOut(&badExit);      /* Output the "can't go there" message */
        wrapEndPara();
    } else {                    /* There is */
        currentState->goTo(destinationRoom); /* Update state to that room - this will also describe it */
    }
}


/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver=false;
    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' ')); //If single word, 255, else the index of the space
        if (endOfVerb == 255) { //Single word input
            /* We could copy the verb to another string but there's no reason to, we'll just compare it in place. */
            /* INVENTORY command */
            /*
            if (commandBuffer.compare(0,endOfVerb,"inventory") == 0) {
                commandOk = true;
                auto iter = currentState->getInventory().begin();
                if (currentState->getInventory().empty()) {
                    cout << "You have no items in your inventory" << endl;
                    break;
                } else {
                    cout << "In your bag you have: " << endl;
                    for (int i = 0; i < currentState->getInventory().size(); i++) {
                        if (i == currentState->getInventory().size() - 1) {
                            cout << "and a ";
                            cout << iter->getName() << endl;
                            break;
                        }
                        cout << "a ";
                        cout << iter->getName() << endl;
                        advance(iter, 1);
                    }
                }

            }*/
            /* Command to go in direction */
            if ((commandBuffer.compare(0,endOfVerb,"north") == 0) || (commandBuffer.compare(0,endOfVerb,"n") == 0)) {
                commandOk = true; /* Confirm command has been handled */
                /* See if there's an exit in specified direction */
                goToRoom('n');
            } else if ((commandBuffer.compare(0,endOfVerb,"south") == 0) || (commandBuffer.compare(0,endOfVerb,"s") == 0)) {
                commandOk = true;
                goToRoom('s');
            } else if ((commandBuffer.compare(0,endOfVerb,"east") == 0) || (commandBuffer.compare(0,endOfVerb,"e") == 0)) {
                commandOk = true;
                goToRoom('e');
            } else if ((commandBuffer.compare(0,endOfVerb,"west") == 0) || (commandBuffer.compare(0,endOfVerb,"w") == 0)) {
                commandOk = true;
                goToRoom('w');
            }
        } else {
            /*
             * GET command - Gets the item specified from the room, puts it in player inventory
             */
            if (commandBuffer.compare(0,endOfVerb,"get") == 0) {
                commandOk = true;
                list<GameObject> roomItems = currentState->getCurrentRoom()->getItems();
                auto iter = roomItems.begin();
                for (int i = 0; i<roomItems.size(); i++) {
                    string itemOnFloor = iter->getKeyword();
                    string commandItem = commandBuffer.substr(endOfVerb+1);
                    if (commandItem == itemOnFloor)  {
                        cout << "YOU GOT IT BRUH" << endl;
                        GameObject gotItem = currentState->getCurrentRoom()->removeItem(commandItem);
                        currentState->addItem(gotItem);
                        break;
                    }
                    advance(iter, 1);
                }
            }
            else if (commandBuffer.compare(0,endOfVerb,"drop") == 0) {
                commandOk = true;
                cout << "DROP IT" << endl;
                GameObject testing = currentState->removeItem("pot");
                cout << testing.getName() << endl;
            }
        }

        /* Quit command */
        if ((commandBuffer.compare(0,endOfVerb,"quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if(!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}


int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}
