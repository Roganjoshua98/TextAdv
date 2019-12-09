
#include <iostream>
#include <iomanip>
#include <vector>
#include <forward_list>
#include <strings.h>
#include <fstream>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"


using std::string;
using std::unique_ptr;

int maxSize = 255;  //The maximum size of any list of items. Important for checkItems, get, drop and examine methods.
string saveFileName = "savefile.txt";
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
    Room* r1 = Room::addRoom(&r1name, &r1desc);
    Room* r2 = Room::addRoom(&r2name, &r2desc);
    Room* r3 = Room::addRoom(&r3name, &r3desc);
    Room* r4 = Room::addRoom(&r4name, &r4desc);
    Room* r5 = Room::addRoom(&r5name, &r5desc);
    GameObject* i1 = GameObject::addItem(i1name, i1desc, i1key);
    GameObject* i2 = GameObject::addItem(i2name, i2desc, i2key);
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
    GameObject* i3 = GameObject::addItem(i3name, i3desc, i3key);
    GameObject* i4 = GameObject::addItem(i4name, i4desc, i4key);
    GameObject* test = *GameObject::items.end();
    GameObject* testicles = test;
    currentState->addItem(i3);
    currentState->addItem(testicles);
}

bool loadIventory(list<string> keys) {
    try {
        for (string key : keys) {
            for (auto & item : GameObject::items) {
                if (key == item->getKeyword()) {
                    currentState->addItem(item);
                    break;
                }
            }
        }
    } catch (exception& e) {
        cout << "Uh oh! The save file has not been written to properly." << endl;
        cout << "Starting new game" << endl;
        Room::rooms.clear();
        GameObject::items.clear();
        initRooms();
        initState();
        return false;
    }
    return true;
}

bool loadRoom(list<string> names) {
    bool x;
    string roomName;
    Room* currentRoom = nullptr;
    for (auto & room : Room::rooms)
        if (roomName == room->getName()) {
            currentRoom = room;
            break;
        }
    try {
        for (string name : names) {
            auto iter = GameObject::items.begin();
            for (int i = 0; i < GameObject::items.size(); i++) {
                if (name == (*iter)->getKeyword()) {
                    currentRoom->addItem(*iter);
                    break;
                }
                advance(iter, 1);
            }
        }
    } catch (exception& e) {
        cout << "Uh oh! The save file has not been written on properly." << endl;
        Room::rooms.clear();
        GameObject::items.clear();
        initRooms();
        initState();
        return false;
    }
    return true;
}

void load() {
    cout << "Loading file..." << endl;
    /* Load all rooms and items*/
    auto* r1 = Room::addRoom(&r1name, &r1desc);
    auto* r2 = Room::addRoom(&r2name, &r2desc);
    auto* r3 = Room::addRoom(&r3name, &r3desc);
    auto* r4 = Room::addRoom(&r4name, &r4desc);
    auto* r5 = Room::addRoom(&r5name, &r5desc);
    r1->configSouth(r2);
    r1->configEast(r3);
    r1->configWest(r4);
    r1->configNorth(r5);
    auto* i1 = GameObject::addItem(i1name, i1desc, i1key);
    auto* i2 = GameObject::addItem(i2name, i2desc, i2key);
    auto* i3 = GameObject::addItem(i3name, i3desc, i3key);
    auto* i4 = GameObject::addItem(i4name, i4desc, i4key);

    ifstream file (saveFileName);
    if (file.is_open()) {
        string textLine;
        getline(file, textLine); //First line is always the player's location, so no check needed
        for (auto & room : Room::rooms)
            if (textLine == room->getName()) {
                currentState = new State(room);
                break;
            }

        list<string> itemNames;
        bool fileLoadedCorrectly = true;
        while (!file.eof() && fileLoadedCorrectly) {
            getline(file, textLine);

            if (textLine == "Inventory:") {  //Between "Inventory:" and "ENDINVENTORY", all lines are item keywords
                cout << "Loading inventory..." << endl;
                getline(file, textLine);
                while (textLine != "ENDINVENTORY") {
                    itemNames.push_back(textLine);
                    getline(file, textLine);
                }
                fileLoadedCorrectly = loadIventory(itemNames);
            }

            else {    //If not "Inventory:", the line will be a room name
                cout << "Loading items for " << textLine << "..." << endl;
                itemNames.clear();
                getline(file, textLine);
                while (textLine != "ENDROOM") {  //All following lines before "ENDROOM" are item keywords in the room
                    itemNames.push_back(textLine);
                    getline(file, textLine);
                }
                fileLoadedCorrectly = loadRoom(itemNames);
            }

        }

        if (fileLoadedCorrectly)
            cout << "File successfully loaded" << endl;
        else
            cout << "File load was unsuccessful. New game started" << endl;
        file.close();
    } else {
        cout << "Unable to load file. Starting new game." << endl;
        initRooms();
        initState();
    }
}

void save() {
    cout << "Saving file..." << endl;
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

int checkItem(vector<GameObject *> items, string searchItem) {
    auto iter = items.begin();
    for (int i = 0; i < items.size(); i++) {
        if (searchItem == (*iter)->getKeyword())
            return i;
        advance(iter, 1);
    }
    return maxSize;
}

bool get(string searchItem) {
    vector<GameObject*> roomItems = currentState->getCurrentRoom()->getItems();
    int index = checkItem(roomItems, searchItem);
    if (index != maxSize) {
        currentState->addItem(currentState->getCurrentRoom()->removeItem(index));
        cout << "You picked up the " << roomItems.at(index)->getName() << endl;
        return true;
    }
    return false;
}

bool drop(string searchItem) {
    vector<GameObject*> inventory = currentState->getInventory();
    int index = checkItem(inventory, searchItem);
    if (index != maxSize) {
        currentState->getCurrentRoom()->addItem(currentState->removeItem(index));
        cout << "You dropped the " << inventory.at(index)->getName() << endl;
        return true;
    }
    return false;
}

bool examine(string searchItem) {
    vector<GameObject*> roomItems = currentState->getCurrentRoom()->getItems();
    int index = checkItem(roomItems, searchItem);
    if (index != maxSize) {
        cout << (roomItems.at(index))->getDescription() << endl;
        return true;
    }
    return false;
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
            if (commandBuffer.compare(0,endOfVerb,"inventory") == 0) {
                commandOk = true;
                if (currentState->getInventory().empty())
                    cout << "You have no items in your inventory" << endl;
                else {
                    vector<GameObject*> inventory = currentState->getInventory();
                    auto iter = inventory.begin();
                    cout << "In your bag you have: " << endl;
                    for (int i = 0; i < inventory.size(); i++) {
                        if (i == inventory.size()-1 && i != 0) {
                            cout << "and a ";
                            cout << (*iter)->getName() << endl;
                            break;
                        }
                        cout << "a ";
                        cout << (*iter)->getName() << endl;
                        advance(iter, 1);
                    }
                }
            }

            /* DESCRIBE command - Describes the room again */
            else if (commandBuffer.compare(0,endOfVerb,"describe") == 0) {
                commandOk = true;
                currentState->getCurrentRoom()->describe();
            }

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

            /* Quit command */
            else if ((commandBuffer.compare(0, endOfVerb, "quit") == 0)) {
                commandOk = true;
                gameOver = true;
            }
        } else {
            string searchItem = commandBuffer.substr(endOfVerb + 1);    //Item that player wants action to be done on
            /*
             * GET command - Gets the item specified from the room, puts it in player inventory
             */
            if (commandBuffer.compare(0, endOfVerb, "get") == 0) {
                commandOk = true;
                if (!get(searchItem))
                    cout << "You search the room, but that item is nowhere to be found" << endl;
            }
            /*
             * DROP command - Drops specified item from inventory onto room floor
             */
            else if (commandBuffer.compare(0, endOfVerb, "drop") == 0) {
                commandOk = true;
                if (!drop(searchItem))
                    cout << "The item you are looking for is not in your inventory" << endl;
            }
            /*
             * EXAMINE command - Brings the long description of a specified object
             */
            else if (commandBuffer.compare(0, endOfVerb, "examine") == 0) {
                commandOk = true;
                if (!examine(searchItem))
                    cout << "You try to imagine what the item might look like, since it is nowhere to be found" << endl;
            }
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if (!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}



int main() {
    initWordWrap();

    string s;
    cout << "Would you like to continue from last adventure? (y/n)" << endl;
    cin >> s;
    char c = s[0];
    bool loadDone = false;
    while (!loadDone) {
        switch (c) {
            case 'y' :
                load();
                loadDone = true;
                break;
            case 'n' :
                initRooms();
                initState();
                loadDone = true;
                break;
            default:
                cout << "Please enter 'y' for yes or 'n' for no" << endl;
                cin >> s;
                c = s[0];
                break;
        }
    }

    currentState->announceLoc();
    gameLoop();
    return 0;
}
