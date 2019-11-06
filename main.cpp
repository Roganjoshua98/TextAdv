
#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
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
    auto* r2 = new Room(&r2name, &r2desc);
    auto* r3 = new Room(&r3name, &r3desc);
    auto* r4 = new Room(&r4name, &r4desc);
    auto* r5 = new Room(&r5name, &r5desc);
    auto* i1 = new GameObject(&i1name, &i1desc, &i1key);
    auto* i2 = new GameObject(&i2name, &i2desc, &i2key);
    Room::addRoom(r1);
    Room::addRoom(r2);
    r1->configSouth(r2);
    r1->configEast(r3);
    r1->configWest(r4);
    r1->configNorth(r5);
    r1->addItem(*i1);
    r1->addItem(*i2);
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
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
        }
        else {
            if (commandBuffer.compare(0,endOfVerb,"get") == 0) {
                auto roomItems = currentState->getCurrentRoom()->getItems();
                auto iter = roomItems.begin();
                for (int i = 0; i<roomItems.size(); i++) {
                    advance(iter, i);
                    const string* gotItem = iter->getKeyword();
                    if (commandBuffer.compare(3,endOfVerb,gotItem) == 0) {
                        cout << "YOU GOT THE ITEM" << endl;
                    }
                }
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