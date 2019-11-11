//
// Created by joshua on 05/11/2019.
//

#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H

#endif //TEXTADV_GAMEOBJECT_H
#include <string>
#include <forward_list>
#include <list>
using namespace std;

class GameObject {
    /* Short name for object */
    string name;
    /* Long description of object */
    string description;
    /* Keyword for user to refer to object in commands */
    string keyword;
public:
    /* Constructor and desctructor */
    GameObject(string _name, string _description, string _keyword);
    ~GameObject();
    /* Static list of all gameObjects initiated */
    static list<GameObject*> gameObjects;
    //static GameObject* addObject(GameObject* room);
    string getName();
    string getDescription();
    string getKeyword();
};
