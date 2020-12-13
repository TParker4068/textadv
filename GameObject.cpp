//
// Created by 16061795 on 08/11/2019.
//

#include "GameObject.h"

std::list<GameObject*> GameObject::gameObjects;

/**
 * GameObject constructor
 * @param _name name of GameObject
 * @param _description description of GameObject
 * @param _keyword keyword of GameObject
 */
GameObject::GameObject(const string _name, const string _description, const string _keyword) :
        name(_name), description(_description), keyword(_keyword){
};



const string GameObject::getName() const {
    return this->name;
}

const string GameObject::getKey() const {
    return this->keyword;
}

const string GameObject::getDesc() const {
    return this->description;
}

GameObject *GameObject::addObject(GameObject *obj) {
    gameObjects.push_back(obj);
}

