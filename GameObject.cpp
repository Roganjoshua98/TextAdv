//
// Created by joshua on 05/11/2019.
//
#include "GameObject.h"
#include "wordwrap.h"
using namespace std;

list<GameObject*> GameObject::items;

GameObject::GameObject(const string* _name, const string* _description, const string* _keyword) :
    name(_name), description(_description), keyword(_keyword){}

string GameObject::getName() {
    return *this->name;
}
string GameObject::getDescription() {
    return *this->description;
}
string GameObject::getKeyword() {
    return *this->keyword;
}

GameObject *GameObject::addItem(const string* _name, const string* _description, const string* _keyword) {
    auto *newItem = new GameObject(_name, _description, _keyword);
    GameObject::items.push_back(newItem);
    return newItem;
}

GameObject::~GameObject() {
    GameObject::items.remove(this);
}

list<GameObject*> GameObject::getItemsList() {
    return GameObject::items;
}
