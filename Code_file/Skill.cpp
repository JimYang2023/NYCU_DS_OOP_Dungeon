#include"Skill.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

Skill::Skill() {
	this->cost = 0;
	this->damage = 0;
	this->CD = 0;
	this->cur_CD = 0;
}

Skill::Skill(string name, int cost,int damage,int CD):Object(name, "Skill") {
	this->cost = cost;
	this->damage = damage;
	this->CD = CD;
	this->cur_CD = 0;
}

bool Skill::trigger_event(Object* object) {
	return 0;
}

void Skill::CD_decrease(int n) {
	cur_CD -= n;
	if (cur_CD <= 0) { 
		cur_CD = 0; 
		cout << "技能 : " << get_name() << " 準備完成" << endl;
	}
	else {
		cout << "技能 : " << get_name() << "\tCD : 剩餘 " << cur_CD << " 回合 " << endl;
	}
}

//getter & setter
int Skill::get_cost() { return cost; }
int Skill::get_damage() { return damage; }
int Skill::get_CD() { return CD; }
int Skill::get_cur_CD() { return cur_CD; }
void Skill::set_cost(int cost) { this->cost = cost; }
void Skill::set_damage(int damage) { this->damage = damage; }
void Skill::set_CD(int CD) { this->CD = CD; }
void Skill::set_cur_CD(int cur_CD) { this->cur_CD = cur_CD; }