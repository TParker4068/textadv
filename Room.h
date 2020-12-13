//
// Created by DrMark on 10/2/2017.
//


#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H

#include <string>
#include <forward_list>
#include <list>
#include "GameObject.h"
#include <vector>

using std::string;

/**
 * Represents a room (accessible location in the game).
 */
class Room {
    /**
     * Short name used as a header.
     */
    const string* name;
    /**
     * Full description of the room.
     */
    const string* description;

    /**
     * One word key used for internal access. (save/load)
     */
    const string* key;

    /**
     * Pointer to room that is north of this one.
     */
    Room* north;

    /**
     * Pointer to room east of this one
     */
    Room* east;

    /**
     * Pointer to room south of this one
     */
    Room* south;

    /**
     * Pointer to room west of this one
     */
    Room* west;

    /*
     * List of GameObjects
     */
    std::list<GameObject *> roomGameObjects;
public:
    /**
     * Constructs a new Room.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    Room(const string *_name, const string *_desc);

    /**
     * constructs a new Room with a key
     * @param _name
     * @param _desc
     * @param _key
     */
    Room(const string *_name, const string *_desc, const string *_key);

    /**
     * Removes a destroyed room from the global list if it's there.
     */
    ~Room();

    /**
     * Outputs the name and description of the room
     * in standard format.
     */
    void describe() const;

    /**
     * List storing all rooms that have been registered via addRoom().
     */
    static std::list<Room*> rooms;

    /**
     * Creates a new Room with the given parameters and register it with the static list.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    static Room* addRoom(const string* _name, const string* _desc);
    static Room* addRoom(Room* room);

    /**
     * Getters and Setters for all directions
     */
    /* Room* getNorth() const;
    void setNorth(Room* _north);

    Room* getEast() const;
    void setEast(Room* _east);

    Room* getSouth() const;
    void setSouth(Room* _south);

    Room* getWest() const;
    void setWest(Room* _west); */

    /* Universal getters and setters for all exits */
    Room* getExit(uint8_t direction) const;
    void setExit(Room* _exit, uint8_t direction);

    /**
     * gets list of GameObjects in the room
     * @return list of GameObjects
     */
    std::list<GameObject*> getObjects() const;

    /**
     * adds GameObject to the rooms object list
     * @param obj GameObject
     */
    void addToRoom(GameObject *obj);

    void removeFromRoom(GameObject *obj);

    string getRoomKey();

    void clearRoom();


};

#endif //TEXTADV_ROOM_H
