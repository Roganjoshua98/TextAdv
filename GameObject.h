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
    const string* name;
    /* Long description of object */
    const string* description;
    /* Keyword for user to refer to object in commands */
    const string* keyword;
public:
    /* Constructor and desctructor */
    GameObject(const string* _name, const string* _description, const string* _keyword);
    ~GameObject();
    static GameObject* addItem(const string* _name, const string* _description, const string* _keyword);
    string getName();
    string getDescription();
    string getKeyword();

    static list<GameObject *> items;
    static list<GameObject*> getItemsList();
};
