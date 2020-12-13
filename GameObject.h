//
// Created by 16061795 on 08/11/2019.
//

#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H
#include <string>
#include <list>

using std::string;

class GameObject {
protected:
    const string description; /*description of what the object is*/
    const string keyword;/*keyword for commands*/
    const string name;/*short name of Object */
public:
    /**
     * creates GameObject object
     * @param _name name of GameObject
     * @param _description description of GameObject
     * @param _keyword keyword for commands
     */
    GameObject(const string _name, const string _description, const string _keyword);
    const string getName() const;
    const string getKey() const;
    const string getDesc() const;


    static std::list<GameObject*> gameObjects;

    static GameObject *addObject(GameObject *obj);


};


#endif //TEXTADV_GAMEOBJECT_H
