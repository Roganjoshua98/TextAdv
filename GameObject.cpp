//
// Created by joshua on 05/11/2019.
//
#include "GameObject.h"
#include "wordwrap.h"
using namespace std;

GameObject::GameObject(const string* _name, const string* _description, const string* _keyword) :
    name(_name), description(_description), keyword(_keyword){}

const string * GameObject::getName() const {
    return this->name;
}
const string *GameObject::getDescription() const {
    return this->description;
}
const string* GameObject::getKeyword() const {
    return this->keyword;
};

GameObject::~GameObject() = default;
