
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
#include "GameObject.h"
#include <fstream>
#include <stdexcept>

using std::string;
using std::unique_ptr;
using namespace std;

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
    auto * r2 = new Room(&r2name, &r2desc, &r2key);
    auto * r1 = new Room(&r1name, &r1desc, &r1key);
    auto * r3 = new Room(&r3name, &r3desc, &r3key); /* new room */
    auto * r4 = new Room(&r4name, &r4desc, &r4key); /* new room */
    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
    r1->setExit(r2, 0);
    r2->setExit(r1, 2);
    r2->setExit(r3, 1);
    r3->setExit(r2, 3);
    r3->setExit(r4, 1);
    r4->setExit(r3, 3);
    GameObject *sword = new GameObject(swordName, swordDesc, swordKey);
    GameObject *shield = new GameObject(shieldName, shieldDesc, shieldKey);
    GameObject *rope = new GameObject(ropeName, ropeDesc, ropeKey);
    GameObject::addObject(sword);
    GameObject::addObject(shield);
    GameObject::addObject(rope);

    r1->addToRoom(sword);
    r1->addToRoom(shield);
    r2->addToRoom(rope);


}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
    GameObject *torch = new GameObject(torchName, torchDesc, torchKey);
    GameObject::addObject(torch);
    currentState->addInv(torch);
}
/**
 * Updates the room the player is in based on a variable input, or tells user they can't go that way.
 * @param direction
 */
void useExit(uint8_t direction) {
    Room *goRoom = nullptr;
    goRoom = currentState->getCurrentRoom()->getExit(direction); /* creates pointer to new room */
    if (goRoom == nullptr) { /* true if the exit doesn't exist */
        wrapOut(&badExit); /* outputs "you can't go that way" */
        wrapEndPara();
    } else {
        currentState->goTo(goRoom); /* updates player state */
    }
}
/**
 * Checks user inventory and the list of objects in current room against inputted keyword to find and return a pointer to GameObject if there's a match
 * @param _object pointer to user inputted word
 * @return a GameObject object, or a nullptr if there's no match
 */
GameObject *getObjectRoom(string &_object) {
    GameObject *object = nullptr;
    for (auto *iterator : currentState->getCurrentRoom()->getObjects()) {
        if (iterator->getKey() == _object) {
            object = iterator;
        }
    }
    return object;
}

GameObject *getObjectInv(string &_object) {
    GameObject *object = nullptr;
    for (auto *iterator : currentState->getInv()) {
        if (iterator->getKey() == _object) {
            object = iterator;
        }
    }
    return object;
}

bool save(const string filename, State *s) {
    ofstream fout(filename, ios_base::out);
    if (!fout.good()) return false;
    fout << "CurrentRoom : ";
    fout << s->getCurrentRoom()->getRoomKey() << endl;
    if (!fout.good()) return false;
    fout << "inventory : ";
    for (auto& o : s->getInv()) {
        fout << o->getKey() << " ";
        if (!fout.good()) return false;
    }
    fout << endl;
    for(auto& r : Room::rooms) {
        fout << r->getRoomKey() <<" : ";
        if (!fout.good()) return false;
        for (auto& obj : r->getObjects()) {
            fout << obj->getKey() << " ";
        }
        fout << endl;
        if (!fout.good()) return false;
    }
    fout.close();
    return true;

}

Room *getRoom(string key) {
    Room *room = nullptr;
    for (auto iterator : Room::rooms) {
        if (iterator->getRoomKey().compare(key) == 0) {
            room = iterator;
        }
    }
    return room;
}

GameObject *getObject(string key) {
    GameObject *object = nullptr;
    for (auto obj : GameObject::gameObjects) {
        if (obj->getKey().compare(key) == 0) {
            object = obj;
        }
    }
    return object;
}


bool load(string filename, State *s) {
    fstream fin(filename, ios_base::in);
    if (!fin.good()) {
        wrapOut(&noFile);
        wrapEndPara();
        return false;
    }
    string str;
    fin >> str;
    if (str.compare("CurrentRoom") != 0 || !fin.good()) {
        wrapOut(&badFormat);
        wrapEndPara();
        return false;
    }
    char c;
    fin >> c;
    if(!fin.good()) return false;
    string roomLoc;
    fin >> roomLoc >> ws;
    if (!fin.good()) return false;
    while (!fin.eof()) {
        string line;
        getline(fin, line);
        auto endOfWord = static_cast<uint8_t>(line.find(' '));
        string topic = line.substr(0, endOfWord);
        line.erase(0, endOfWord+1);
        endOfWord = static_cast<uint8_t>(line.find(' '));
        line.erase(0, endOfWord+1);
        if (topic == "inventory") {
            s->clearInventory();
            while (!line.empty()) {
                endOfWord = static_cast<uint8_t>(line.find(' '));
                string obj;
                obj = line.substr(0, endOfWord);
                if (getObject(obj) == nullptr) return false;
                s->addInv(getObject(obj));
                line.erase(0, endOfWord+1);
            }
        } else {
            Room *r = getRoom(topic);
            if (r == nullptr) return false;
            r->clearRoom();
            while(!line.empty()) {
                endOfWord = static_cast<uint8_t>(line.find(' '));
                string obj;
                obj = line.substr(0, endOfWord);
                if (getObject(obj) == nullptr) return false;
                r->addToRoom(getObject(obj));
                line.erase(0, endOfWord+1);
            }
        }
        fin >> ws;
    }
    wrapOut(&loadComp);
    wrapEndPara();
    s->goTo(getRoom(roomLoc));
    fin.close();
    return true;
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
        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));
        /* checks if user inputted a direction */
        uint8_t direction = 4;
        if ((commandBuffer.compare(0,endOfVerb,"north") == 0) || (commandBuffer.compare(0,endOfVerb,"n") == 0)) {
            direction = 0;
        } else if ((commandBuffer.compare(0,endOfVerb,"east") == 0) || (commandBuffer.compare(0,endOfVerb,"e") == 0)) {
            direction = 1;
        } else if ((commandBuffer.compare(0,endOfVerb,"south") == 0) || (commandBuffer.compare(0,endOfVerb,"s") == 0)) {
            direction = 2;
        } else if ((commandBuffer.compare(0,endOfVerb,"west") == 0) || (commandBuffer.compare(0,endOfVerb,"w") == 0)) {
            direction = 3;
        }

        if (direction < 4) { /* true if valid direction input was inputted */
            commandOk = true; /* confirms valid command was inputted */
            useExit(direction); /* tries to update position */
        }

        /* retrieves the second word of the users input */
        string secWord;


        if (commandBuffer.compare(0,endOfVerb,"get") == 0) {
            commandOk = true;
            secWord = commandBuffer.substr(endOfVerb + 1, commandBuffer.length());
            GameObject *obj = getObjectRoom(secWord); /* searches for object in room */
            if (obj == nullptr) {
                wrapOut(&badObject); /* prints "This object is not in the room." */
                wrapEndPara();
            } else {
                currentState->addInv(obj); /* adds object to inventory list */
                currentState->getCurrentRoom()->removeFromRoom(obj); /* removes object from room list */
                std::cout << "You picked up the " << obj->getName() << "." << std::endl;
            }
        }

        if (commandBuffer.compare(0,endOfVerb,"drop") == 0) {
            commandOk = true;
            secWord = commandBuffer.substr(endOfVerb + 1, commandBuffer.length());
            GameObject *obj = getObjectInv(secWord); /* finds inputted object in user inventory or returns nullptr */
            if (obj == nullptr) {
                wrapOut(&badInv); /* prints "This object is not currently in your inventory." */
                wrapEndPara();
            } else {
                currentState->getCurrentRoom()->addToRoom(obj); /* adds object to room list */
                currentState->removeInv(obj); /* removes object from inventory list */
                std::cout << "You dropped the " << obj->getName() <<"." << std::endl;
            }
        }

        if (commandBuffer.compare(0,endOfVerb,"inventory") == 0) {
            commandOk = true;
            if (!currentState->getInv().empty()) {
                std::cout << "Your Inventory is:" << std::endl;
                for (auto iter : currentState->getInv()) {
                    std::cout << " " << iter->getName() << std::endl;
                }
            } else {
                wrapOut(&emptyInv);
                wrapEndPara();
            }
        }

        if (commandBuffer.compare(0,endOfVerb,"examine") == 0) {
            commandOk = true;
            secWord = commandBuffer.substr(endOfVerb + 1, commandBuffer.length());
            GameObject *obj = getObjectRoom(secWord);
            if (obj == nullptr) {
                obj = getObjectInv((secWord));
                if (obj == nullptr) {
                    wrapOut(&badObject);
                    wrapEndPara();
                } else {
                    std::cout << obj->getDesc() << std::endl;
                }
            } else {
                std::cout << obj->getDesc() << std::endl;
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"save") == 0)) {
            commandOk = true;
            string s;
            cout << "Please enter a filename: ";
            inputCommand(&s);
            s.append(".txt");
            bool saveOk = save(s, currentState);
            if(saveOk) {
                wrapOut(&saveComp);
                wrapEndPara();
            } else {
                wrapOut(&saveFail);
                wrapEndPara();
            }
        }

        if ((commandBuffer.compare(0, endOfVerb,"load") == 0)) {
            commandOk = true;
            string s;
            cout << "Please enter a filename: ";
            inputCommand(&s);
            s.append(".txt");
            bool loadOk = load(s, currentState);
            if (!loadOk) {
                wrapOut(&loadFail);
                wrapEndPara();
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