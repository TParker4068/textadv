//
// Created by DrMark on 10/2/2017.
//
#include "Room.h"
#include "wordwrap.h"
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
        name(_name), description(_desc), north(nullptr) {};

Room::Room(const string *_name, const string *_desc, const string *_key) :
        name(_name), description(_desc), key(_key) {};

/**
 * Remove destroyed rooms from the static list.
 */
Room::~Room() {
    Room::rooms.remove(this);
}

/**
 * Prints the description of a room (the name and long description)
 */
void Room::describe() const {
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();
    std::cout << "The items in this room are: " << std::endl;
    for (auto *iter : this->roomGameObjects) { /* iterator for list of gameObjects */
        std::cout << iter->getName() << std::endl;
    }
    
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
}

/*
 * Gets exit of room depending on inputted variable
 * @return an exit of the room if it exist in chose direction, or a nullptr otherwise
 */
Room* Room::getExit(uint8_t direction) const {
    Room* room;
    if (direction == 0) {
        room = this->north;
    } else if (direction == 1) {
        room = this->east;
    } else if (direction == 2) {
        room = this->south;
    } else if (direction ==3) {
        room = this->west;
    } else {
        room = nullptr; /* catches any wrongly inputted direction */
    }
    return room;
}

void Room::setExit(Room* _exit, uint8_t direction) {
    if (direction == 0) {
        this->north = _exit;
    } else if (direction == 1) {
        this->east = _exit;
    } else if (direction == 2) {
        this->south = _exit;
    } else if (direction == 3) {
        this->west = _exit;
    }
}

std::list<GameObject*> Room::getObjects() const {
    return this->roomGameObjects;
}

void Room::addToRoom(GameObject *obj) {
    roomGameObjects.push_back(obj);
}

void Room::removeFromRoom(GameObject *obj) {
    roomGameObjects.remove(obj);
}

string Room::getRoomKey() {
    return *key;
}

void Room::clearRoom() {
    roomGameObjects.clear();
}
/**
 * Gets the north exit of a room.
 * @return The room that is north of this one, or NULL if there is no exit.
 */
/* Room* Room::getNorth() const {
    return this->north;
} /*

/**
 * Sets the north exit of a room.
 * @param _north Pointer to the room to be north of this one.
 */

/* void Room::setNorth(Room* _north) {
    this->north = _north;
} */

/**
 * Gets the east exit
 * @return The room to the east of this one, or NULL if none existent
 */

/*Room* Room::getEast() const {
    return this->east;
}*/

/**
 * Set the east exit of a room
 * @param _east Pointer to the room east of this one.
 */
/* void Room::setEast(Room* _east) {
    this->east = _east;
} */

/**
 * Gets the south exit
 * @return The room to the south of this one, or NULL if none existent
 */
/* Room* Room::getSouth() const {
    return this->south;
} */

/**
 * Set the south exit of a room
 * @param _south Pointer to the room south of this one.
 */

/* void Room::setSouth(Room* _south) {
    this->south = _south;
} */

/**
 * Gets the west exit
 * @return The room to the west of this one, or NULL if none existent
 */
 /* Room* Room::getWest() const {
    return this->west;
} */

/**
 * Set the west exit of a room
 * @param _west Pointer to the room west of this one.
 */
/* void Room::setWest(Room* _west) {
    this->west = _west;
} */
