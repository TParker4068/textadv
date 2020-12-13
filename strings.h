//
// Created by DrMark on 10/4/2017.
//

#ifndef TEXTADV_STRINGS_H
#define TEXTADV_STRINGS_H


#include <string>

const std::string r1name = "Room 1";
const std::string r1desc = "You are in room 1. It's really quite boring, but then, it's just for testing really. There's a passage to the north.";
const std::string r1key = "room1";
const std::string r2name = "Blue Room";
const std::string r2desc = "You are in the blue room. You know because it's blue. That's about all though. There's a passage to the south that is illuminated orange and a dark and mysterious passage to the east";
const std::string r2key = "blue";
const std::string r3name = "Dungeon";
const std::string r3desc = "You have arrived at a murky dungeon, spiders scale the walls in high volumes and the only sound you can hear is that of water dripping down into a large puddle that fills the floor. You spot a glimmering light of a torch illuminating a doorway to the east and a weird blue light to the west.";
const std::string r3key = "dungeon";
const std::string r4name = "Collapsed Stairwell";
const std::string r4desc = "You have arrived at a collapsed stairwell, it appears there is no way up. Your only is choice is to return west.";
const std::string r4key = "stairwell";

const std::string badExit = "You can't go that way.";
const std::string badCommand = "I don't understand that.";
const std::string badObject = "This object is not in the room.";
const std::string badInv = "This object is not currently in your inventory.";
const std::string emptyInv = "Your inventory is empty.";
const std::string saveComp = "Save complete!";
const std::string saveFail = "An error has occurred, save incomplete :(";
const std::string loadComp = "Load Complete!";
const std::string loadFail = "An error has occurred, save incomplete :(";
const std::string noFile = "Sorry that file does not exist.";
const std::string badFormat = "Sorry the file format is incorrect.";



const std::string swordName = "Rusted Sword";
const std::string swordDesc = "A steel sword rusted by the sands of time, it may still be of some use.";
const std::string swordKey = "sword";
const std::string torchName = "Torch";
const std::string torchDesc = "A useful tool for handling fire, may it light the way and keep you warm in the darkness.";
const std::string torchKey = "torch";
const std::string ropeName = "Rope";
const std::string ropeDesc = "An ever versatile tool, use it to climb, descend or pull";
const std::string ropeKey = "rope";
const std::string shieldName = "Wooden Shield";
const std::string shieldDesc = "A tool of protection, though perhaps keep it away from fire.";
const std::string shieldKey = "shield";



#endif //TEXTADV_STRINGS_H
