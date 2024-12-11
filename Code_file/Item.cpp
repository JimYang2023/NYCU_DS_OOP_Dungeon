#include"Item.h"


Item::Item():Object() {
	this->health = 0;
	this->attack = 0;
	this->defense = 0;
}

Item::Item(string name, int health, int attack, int defense) : Object(name,"Item") {
	this->health = health;
	this->attack = attack;
	this->defense = defense;
}

bool Item::trigger_event(Object*) {
	//Todo
	return 1;
}

int Item::get_health() {
	return health;
}

int Item::get_attack() {
	return attack;
}

int Item::get_defense() {
	return defense;
}

void Item::set_health(int health) {
	this->health = health;
}

void Item::set_attack(int attack) {
	this->attack = attack;
}

void Item::set_defense(int defense) {
	this->defense = defense;
}

//virtuL
int Item::get_value() { return 0; }

// Item's category

//Weapon
Weapon::Weapon() {
	set_tag("weapon");
	set_name("Empty Weapon");
	equipment = 0;
}
Weapon::Weapon(string name, int hp, int atk, int def):Item(name,hp,atk,def) {
	set_tag("Weapon");
	equipment = 0;
}

int Weapon::get_value() { return equipment; }

void Weapon::set_equipment(bool equipment) { this->equipment = equipment; }
bool Weapon::get_equipment() { return equipment; }

//Recorver

Recorver::Recorver() {
	recorver_value = 0;
	type = 0;
	set_tag("Recorver");
}

Recorver::Recorver(int recorver_value, int type) {
	this->recorver_value = recorver_value;
	this->type = type;
	set_tag("Recorver");
	if (type == 1) {
		set_name("HP¦^´_ÃÄ¤ô");
	}
	else if(type == 2) {
		set_name("MP¦^´_ÃÄ¤ô");
	}
	else {
		cout << "Type Error(Recorver)" << endl;
		exit(1);
	}
}

void Recorver::set_recorver_value(int value) { this->recorver_value = value; }
void Recorver::set_type(int type) { this->type = type; }
int Recorver::get_recorver_value() { return recorver_value; }
int Recorver::get_type() { return type; }
int Recorver::get_value() { return recorver_value; }

Food::Food() {
	set_tag("Food");
	set_name("Empty Food");
	food_value = 0;
}

Food::Food(string name,int food_value):Item(name,0,0,0) {
	set_tag("Food");
	this->food_value = food_value;
}

int Food::get_value() { return food_value; }
