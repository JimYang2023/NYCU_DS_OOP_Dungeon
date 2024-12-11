#ifndef Skill_h
#define Skill_h

#include"Object.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Skill : public Object {
public:
	Skill();
	Skill(string name,int cost,int damage,int CD);
	bool trigger_event(Object*) override;
	void CD_decrease(int);
	//getter & setter
	int get_cost();
	int get_damage();
	int get_CD();
	int get_cur_CD();
	void set_cost(int);
	void set_damage(int);
	void set_CD(int);
	void set_cur_CD(int);
private:
	int cost;    //consume mp
	int damage;  //cause damage
	int CD;      //Cooling Down Time
	int cur_CD;
};




#endif