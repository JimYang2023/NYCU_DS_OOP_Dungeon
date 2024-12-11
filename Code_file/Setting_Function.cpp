#include"Setting_Function.h"

//Businessman setting (type: )
Businessman* Businessman_setting(int type) {
	Businessman* temp = NULL;
	vector<Item*> good;
	vector<int> cost;
	Food* food_item;
	Recorver* recorver_item;
	Weapon* weapon_item;
	switch (type) {
	case 0:
		food_item = Food_setting(4);
		push_back(good, food_item, cost, 30);
		food_item = Food_setting(3);
		push_back(good, food_item, cost, 20);
		food_item = Food_setting(1);
		push_back(good, food_item, cost, 10);
		recorver_item = new Recorver(20, 1);
		push_back(good, recorver_item, cost, 30);
		recorver_item = new Recorver(20, 2);
		push_back(good, recorver_item, cost, 40);
		temp = new Businessman(good, cost);
		weapon_item = new Weapon("逐暗者", 30, 40, 50);
		push_back(good, weapon_item, cost, 150);
		break;
	case 1:
		food_item = Food_setting(4);
		push_back(good, food_item, cost, 30);
		food_item = Food_setting(3);
		push_back(good, food_item, cost, 20);
		food_item = Food_setting(2);
		push_back(good, food_item, cost, 10);
		recorver_item = new Recorver(20, 1);
		push_back(good, recorver_item, cost, 30);
		recorver_item = new Recorver(20, 2);
		push_back(good, recorver_item, cost, 40);
		weapon_item = new Weapon("釋闇者", 30, 40, 50);
		push_back(good, weapon_item, cost, 150);
		temp = new Businessman(good, cost);
		break;
	case 2:
		food_item = Food_setting(4);
		push_back(good, food_item, cost, 30);
		food_item = Food_setting(3);
		push_back(good, food_item, cost, 20);
		food_item = Food_setting(1);
		good.push_back(food_item);
		cost.push_back(10);
		recorver_item = new Recorver(20, 1);
		good.push_back(recorver_item);
		cost.push_back(30);
		recorver_item = new Recorver(20, 2);
		good.push_back(recorver_item);
		cost.push_back(40);
		weapon_item = new Weapon("釋闇者", 30, 40, 50);
		good.push_back(weapon_item);
		cost.push_back(150);
		temp = new Businessman(good, cost);
		break;
	default:
		cout << "Type : " << type << endl;
		cout << "type error(Businessman_setting)" << endl;
		exit(1);
	}
	if (temp == NULL) { cout << "temp error" << endl; exit(1); }
	return temp;
}
//A function which help businessman setting
void push_back(vector<Item*>& items, Item* item, vector<int>& costs, int cost) {
	items.push_back(item);
	costs.push_back(cost);
}

Teacher* Teacher_setting(int type) {
	Teacher* temp = NULL;
	Skill* skill;
	vector<Skill*> skills;
	switch (type) {
	case 0:
		skill = Skill_setting(0);
		push_back(skills, skill);
		skill = Skill_setting(1);
		push_back(skills, skill);
		break;
	case 1:
		skill = Skill_setting(1);
		push_back(skills, skill);
		skill = Skill_setting(2);
		push_back(skills, skill);
		break;
	case 2:
		skill = Skill_setting(2);
		push_back(skills, skill);
		skill = Skill_setting(3);
		push_back(skills, skill);
		break;
	default:
		cout << "Type Error(Teacher_setting)" << endl;
		exit(1);
	}
	temp =new Teacher(skills);
	return temp;
}

void push_back(vector<Skill*>& skills, Skill* skill) {
	//Debug
	if (skill == NULL) { cout << "Error(push_back skill)" << endl; exit(1); }
	//
	skills.push_back(skill);
}

//Weapon setting  (type: 0~4)
Weapon* Weapon_setting(int type) {
	Weapon* temp=NULL;
	switch (type) {
	case 0:
		temp = new Weapon("大劍", 0, 30, 10);
		break;
	case 1:
		temp = new Weapon("武士刀", 0, 30, 10);
		break;
	case 2:
		temp = new Weapon("Excalibur", 0, 30, 10);
		break;
	case 3:
		temp = new Weapon("釋闇者", 30, 40, 50);
	case 4:
		temp=new Weapon("逐暗者", 30, 40, 50);
	default:
		//Debug
		cout << "Type Error(Weapon_setting)" << type << endl;
		exit(1);
	}
	//Debug
	if (temp == NULL) { cout << "Error(Weapon_setting)" << endl; exit(1); }
	//
	return temp;
}

//Food setting (type: 0~6)
Food* Food_setting(int type) {
	Food* temp=NULL;
	switch (type) {
	// 食物名稱 , 回復數值
	case 0:
		temp = new Food("蘋果", 2);
		break;
	case 1:
		temp = new Food("香蕉", 2);
		break;
	case 2:
		temp = new Food("雞腿", 4);
		break;
	case 3:
		temp = new Food("水", 4);
		break;
	case 4:
		temp = new Food("牛奶", 1);
		break;
	case 5:
		temp = new Food("豬肉", 4);
		break;
	case 6:  // 可以同時回復 thirst 和 hunger
		temp = new Food("仙人掌", 2);
		break;
	case 7:
		temp = new Food("解毒草", 1);
		break;
	default:
		//Debug
		cout << "Type Error(Food_setting)" << type << endl;
		exit(1);
	}
	//Debug
	if (temp == NULL) { cout << "Error(Food_setting)" << endl; exit(1); }
	//
	return temp;
}

//Player setting
Player* Player_setting(int type) {
	Player* temp=NULL;
	switch (type) {
	case 0:
		temp = new Player("", 70, 15, 20 , 15);
		temp->set_profession("戰士");
		temp->learn_skill(Skill_setting(4));
		break;
	case 1:
		temp = new Player("", 60, 20, 10, 20);
		temp->set_profession("遊俠");
		temp->learn_skill(Skill_setting(5));
		break;
	case 2:
		temp = new Player("", 55, 25, 10,35);
		temp->set_profession("法師");
		temp->learn_skill(Skill_setting(6));
		temp->set_skill_number(3);
		break;
	default:
		//Debug
		cout << "Type Error(Player_setting)" << type << endl;
		exit(1);
	}
	return temp;
}

//Monster setting ( type : 0 ~ 5 )
Monster* Monster_setting(int type) {
	Monster* temp = NULL;
	switch (type) {
	case 0:  //野狼
		temp = new Monster("野狼", 20, 10 , 5);
		break; 
	case 1:  //老虎
		temp = new Monster("老虎", 40, 15, 5);
		break;
	case 2:  //黑熊
		temp = new Monster("黑熊", 40, 15, 10);
		break;
	case 3:  //獅子
		temp = new Monster("獅子", 50, 20, 10);
		break;
	case 4:  //蜘蛛
		temp = new Monster("蜘蛛", 30, 10, 5);
		break;
	case 5:  //野豬
		temp = new Monster("野豬", 40, 15, 10);
		break;
	default:
		//Debug
		cout << "Type Error(Monster_setting)" << type << endl;
		exit(1);
	}
	if (temp == NULL) {
		cout << "temp error(Monster_setting)" << endl;
	}
	return temp;
}

//Skill settinig ( type : 0 ~ 3)
Skill* Skill_setting(int type) {
	Skill* temp=NULL;
	switch (type) {
	case 0:
		temp = new Skill("西瓜榴槤擊",10,30,3);
		break;
	case 1:
		temp = new Skill("The World!!!",15,40,4);
		break;
	case 2:
		temp = new Skill("昇龍拳",7,15,2);
		break;
	case 3:
		temp = new Skill("發炎拳", 7, 12,2);
		break;
	case 4:  //戰士預設技能
		temp = new Skill("斬擊",6,5,2);
		break;
	case 5:  //遊俠預設計能
		temp = new Skill("突刺", 12, 10, 2);
		break;
	case 6:  //法師預設技能
		temp = new Skill("豪火球之術", 20, 35 , 4);
		break;
	default:
		cout << "Type Error(Skill_setting)" << endl;
		exit(1);
	}
	return temp;
}

//Room setting
// area 0 : Desert 
		// tyep 0: oasis
		// type 1: sandstroms
		// type 2: 仙人掌
// area 1 : Forest
		// type 0 : Lake
		// type 1 : 解毒草
		// type 2 : 水果
		// type 3 : 蜘蛛
// area 2 : Swamp
		// type 0 : poison
		// type 1 : Attack
		// type 2 : water
		// type 3 : 發現武器
Room* Room_setting(int area, int type,int index) {
	Room* temp = NULL;
	switch (area) {
	case 0:
		temp = new Desert(type);
		break;
	case 1:
		temp = new Forest(type);
		if(type==3){
			temp->add_object(Monster_setting(4));
		}
		break;
	case 2:
		temp = new Swamp(type);
		break;
	default:
		cout << "area error(Room_setting)" << endl;
		exit(1);
	}
	temp->set_index(index);
	return temp;
}
