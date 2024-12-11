#ifndef Monster_h
#define Monster_h

#include<iostream>
#include<string>
using namespace std;

#include"Player.h"


class Monster :public GameCharacter {
public:
	Monster();
	Monster(string, int, int, int);
	virtual bool trigger_event(Object*);
	void show_status();
	void fighting_system(Player* );
};

//Some monsters
class Boss :public Monster {
public:
	Boss();
	string get_start_script();
	string get_end_script();
	bool trigger_event(Object*) override;

private:
	string start_script;
	string end_script;
};

#endif