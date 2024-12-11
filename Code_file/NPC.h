#ifndef NPC_h
#define NPC_h

#include<iostream>
#include<vector>
#include<cstdlib>
#include"GameCharacter.h"
#include"Item.h"
#include"Player.h"
using namespace std;

// Base Class
class NPC : public GameCharacter {
public:
	NPC();
	NPC(string, string, vector<Item*>);
	void list_commodity();
	virtual bool trigger_event(Object*) override;
	//setter
	void set_script(string);
	void set_commodity(vector<Item*>);
	//getter
	string get_script();
	vector<Item*> get_commodity();
	//erase item
	void erase_item(int);
private:
	string script;
	vector<Item*> commodity;
};


//玩家遭遇進行交易
class Businessman : public NPC {
public:
	Businessman();
	Businessman(vector<Item*>,vector<int>);
	bool trigger_event(Object*) override;
	void show_goods();
	//setter
	void set_cost(vector<int>);
	//getter
	vector<int> get_cost();
private:
	vector<int> cost;
};


//設定出現在 Start Room 給予玩家基本物資
class Leader :public NPC {
public:
	Leader();
	bool trigger_event(Object*) override;
	void set_get_weapon(bool);
	bool get_get_weapon();
private:
	bool get_weapon;
};


//玩家遭遇可以學習一項 skill
class Teacher :public NPC {
public:
	Teacher();
	Teacher(vector<Skill*>) ;
	bool trigger_event(Object* ) override;
	void set_skills(vector<Skill*>);
	vector<Skill*>& get_skills();
private:
	vector<Skill*>skills;
	bool learn_skill;
};
#endif