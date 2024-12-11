#include"GameCharacter.h"

//class person
//constructor 
GameCharacter::GameCharacter() {
	this->max_hp = 0;
	this->atk = 0;
	this->def = 0;
	cur_hp = 0;
}

GameCharacter::GameCharacter(string name, int hp, int atk, int def) : Object(name,"GameCharacter") {
	this->max_hp = hp;
	this->atk = atk;
	this->def = def;
	cur_hp = max_hp;
};

GameCharacter::GameCharacter(string name, int hp, int atk, int def ,int mp) : Object(name, "GameCharacter") {
	this->max_hp = hp;
	this->atk = atk;
	this->def = def;
	this->max_mp = mp;
	cur_mp = max_mp;
	cur_hp = max_hp;
};

//setter & getter
void GameCharacter::set_max_hp(int max_hp) { this->max_hp = max_hp; }
void GameCharacter::set_cur_hp(int cur_hp) { 
	if (cur_hp > max_hp) {
		this->cur_hp = max_hp;
	}
	else {
		this->cur_hp = cur_hp;
	} 
}
void GameCharacter::set_atk(int atk) { this->atk = atk; }
void GameCharacter::set_def(int def) { this->def = def; }
void GameCharacter::set_skills(vector<Skill*> skills) { this->skills = skills; }
void GameCharacter::set_skill_number(int skill_number) { this->skill_number = skill_number; }
void GameCharacter::set_max_mp(int mp) { this->max_mp = mp; }
void GameCharacter::set_cur_mp(int mp) { this->cur_mp = mp; }
int GameCharacter::get_max_hp() { return max_hp; }
int GameCharacter::get_cur_hp() { return cur_hp; }
int GameCharacter::get_atk() { return atk; }
int GameCharacter::get_def() { return def; }
vector<Skill*>& GameCharacter::get_skills() { return skills; }
int GameCharacter::get_skill_number() { return skill_number; }
int GameCharacter::get_max_mp() { return max_mp; }
int GameCharacter::get_cur_mp() { return cur_mp; }

//damage
void GameCharacter::cause_damage(int damage_value) {
	if (damage_value>def) {
		cur_hp -= (damage_value-def);
		cout << get_name() << " 受到" << damage_value-def << " 點傷害" << endl;
	}
	else {
		cur_hp -= 1;
		cout << get_name() << " 受到" << 1 << " 點傷害" << endl;
	}
}

//recorver
void GameCharacter::recorver(int recorver_value) {
	if (cur_hp + recorver_value > max_hp) {
		cur_hp = max_hp;
	}
	else {
		cur_hp += recorver_value;
	}
}

//checking die
//life: 1 die: 0
bool GameCharacter::check_die() {
	if (cur_hp > 0) {
		return 1;
	}
	return 0;
}

//virtual function to show status
void GameCharacter::show_status() {
	cout << "Error" << endl;
}

bool GameCharacter::trigger_event(Object* object) {
	
	return 1;
}

void GameCharacter::show_skill() {
	cout << "技能 / 花費MP / 傷害 / CD / 現在CD:" << endl;
	for (int i = 0; i < skills.size(); i++) {
		cout << i + 1 << ". " << skills[i]->get_name() << " / "<< skills[i]->get_cost() << " / "<< skills[i]->get_damage()<<" / "<< skills[i]->get_CD() << " / "<<skills[i]->get_cur_CD() << endl;
	}
}

//learn skill
bool GameCharacter::learn_skill(Skill* new_skill) {
	if (skills.size() == skill_number) {
		cout << "請選擇要丟棄的技能:" << endl;
		int choice=-1;
		show_skill();
		while (1) {
			cin >> choice;
			if (choice <= 0 || choice > skills.size()) {
				cout << "輸入錯誤，請重新輸入。" << endl;
			}
			else {
				break;
			}
		}
		skills.erase(skills.begin() + choice-1);
		skills.push_back(new_skill);
	}
	else {
		skills.push_back(new_skill);
	}
	cout << "Learn Skill Success" << endl;
	show_skill();
	return 1;
}


int GameCharacter::use_skill(int num) {
	if (num < 0 || num >= skills.size()) {
		cout << "輸入數字錯誤(use_skill)" << endl;
		exit(1);
	}
	cur_mp -= (skills[num]->get_cost());
	cout << get_name() <<" 使用 " << skills[num]->get_name() << endl;
	skills[num]->set_cur_CD(skills[num]->get_CD());
	return skills[num]->get_damage() + atk;
}