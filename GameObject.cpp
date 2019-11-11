//
// Created by joshua on 05/11/2019.
//
#include "GameObject.h"
#include "wordwrap.h"
using namespace std;

GameObject::GameObject(string _name, string _description, string _keyword) :
    name(_name), description(_description), keyword(_keyword){}

string GameObject::getName() {
    return this->name;
}
string GameObject::getDescription() {
    return this->description;
}
string GameObject::getKeyword() {
    return this->keyword;
}

/*
 GameObject* GameObject::addObject(GameObject *object) {
    gameObjects.push_back(object);
    return object;
};*/

GameObject::

GameObject::~GameObject() = default;
