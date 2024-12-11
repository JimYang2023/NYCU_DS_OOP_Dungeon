#ifndef Setting_Function_h
#define Setting_Function_h

#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<ctime>
#include"NPC.h"
#include"Monster.h"
#include"Area.h"
using namespace std;

//NPC setting

// 0~2
Businessman* Businessman_setting(int type);

// 0~2
Teacher* Teacher_setting(int type);

//helping function
void push_back(vector<Skill*>& skills, Skill* skill);
void push_back(vector<Item*>& items, Item* item, vector<int>& costs, int cost);

//Item setting
//Food setting (0~6) 
Food* Food_setting(int type);

Weapon* Weapon_setting(int type);

Skill* Skill_setting(int type);

//GameCharaacter setting
Player* Player_setting(int type);

//Monster setting (0~5)
Monster* Monster_setting(int type);

//Room setting
// area 0 : Desert (0~3)
// area 1 : Forest (0~4)
// area 2 : Swamp  (0~4)
Room* Room_setting(int area, int type, int index);

#endif