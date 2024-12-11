#ifndef GameCharacter_h
#define GameCharacter_h
#include<string>
#include<iostream>
#include<vector>
#include"Object.h"
#include"Skill.h"
using namespace std;

class GameCharacter : public Object{
public:
	//constructor
	GameCharacter();
	GameCharacter(string, int , int , int );
	GameCharacter(string name, int hp, int atk, int def, int mp);
	//setter
	void set_max_hp(int);
	void set_cur_hp(int);
	void set_atk(int);
	void set_def(int);
	void set_skills(vector<Skill*>);
	void set_skill_number(int);
	void set_max_mp(int);
	void set_cur_mp(int);
	//getter
	int get_max_hp();	
	int get_cur_hp();
	int get_atk();
	int get_def();
	vector<Skill*>& get_skills();
	int get_skill_number();
	int get_max_mp();
	int get_cur_mp();
	//damage
	void cause_damage(int );
	//recover
	void recorver(int );
	//checking die
	bool check_die();
	virtual bool trigger_event(Object*) override;
	virtual void show_status();

	//show skill
	void show_skill();

	//learm skill
	bool learn_skill(Skill*);
	int use_skill(int);

private:
	int max_hp;
	int cur_hp;
	int atk;
	int def;
	int cur_mp;
	int max_mp;
	int skill_number = 2;
	vector<Skill*> skills;
};

#endif

