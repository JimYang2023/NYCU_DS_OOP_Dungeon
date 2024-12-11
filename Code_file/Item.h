#ifndef Item_h
#define Item_h

#include<iostream>
#include<string>
#include"Object.h"

using namespace std;

class Item :public Object {
public:
	//constructor
	Item();
	Item(string, int, int, int);

	//
	bool trigger_event(Object*);

	//setter & getter
	void set_health(int);
	void set_attack(int);
	void set_defense(int);
	int get_health();
	int get_attack();
	int get_defense();

	//virtual
	virtual int get_value();

private:
	int health;
	int attack;
	int defense;
};


// Item's category



class Weapon : public Item{
public:
	Weapon();
	Weapon(string, int, int, int);
	void set_equipment(bool);
	bool get_equipment();
	int get_value() override;
private:
	bool equipment;
};

class Recorver : public Item {
public:
	Recorver();
	Recorver(int ,int );
	void set_recorver_value(int);
	void set_type(int);
	int get_recorver_value();
	int get_type();
	int get_value() override;
private:
	int recorver_value;
	int type;  // 1: hp 2: mp
};

class Food : public Item{
public:
	Food();
	Food(string,int);
	int get_value() override;
private:
	int food_value;
};
#endif