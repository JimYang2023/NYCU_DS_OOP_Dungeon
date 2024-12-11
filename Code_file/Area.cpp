#include"Area.h"
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;

//////////////Desert/////////////////
Desert::Desert(bool is_exit, int index, vector<Object*> objects):Room("Desert",is_exit,index,objects) {
	
}
Desert::Desert(){}
Desert::Desert(int type) {
	this->type = type;
	set_name("Desert");
}

bool Desert::trigger_event(Object* object) {
	Player* player = dynamic_cast<Player*>(object);
	int choice;
	cout << "現在地區 : Desert" << endl << endl;
	if (type==1) {
		//oasis
		//輸出綠洲資訊
		cout << "在房間中有綠洲。" << endl;
		cout << "是否飲用綠洲泉水(回復Thrist值):" << endl;
		cout << "1. 是" << endl;
		cout << "2. 否" << endl;
		//Player 選擇
		cin >> choice;
		if (choice == 1) {
			player->set_cur_thirst(player->get_max_thirst());
			cout << "飲用泉水回復 Thirst 至最大值" << endl;
		}
		else { cout << "離開綠洲" << endl; }
		cout << endl;
		system("pause");
		cout << endl;
	}
	else if(type == 0 && !get_event_happen()){
		//sandstorms
		cout << "遭遇沙塵暴，飢餓值與水分大量減少。(減少最大值的1/3)" << endl;
		//水分與飢餓值減少1/3
		player->set_cur_thirst(player->get_cur_thirst() - player->get_max_thirst() / 3);
		player->set_cur_hunger(player->get_cur_hunger() - player->get_max_hunger() / 3);
		//檢查 Hunger & Thirst 是否小於 0
		if (player->get_cur_hunger() < 0) {
			player->set_cur_hunger(0);
		}
		if (player->get_cur_thirst() < 0) {
			player->set_cur_thirst(0);
		}
		//
		cout << " Thirst : " << player->get_cur_thirst() << " / " << player->get_max_thirst() << endl;
		cout << " Hunger : " << player->get_cur_hunger() << " / " << player->get_max_hunger() << endl;
		//畫面整理
		cout << endl;
		system("pause");
		cout << endl;
		//設定事件已發生
		set_event_happen(1);
	}
	else if (type == 2 && !get_event_happen()) {
		cout << endl << endl;
		cout << "在沙漠中發現仙人掌" << endl;
		Food* temp =new Food("仙人掌", 2);
		player->add_item(temp);
		//設定事件已發生
		set_event_happen(1);
	}
	return 1;
}

//getter
int Desert::get_type() { return type; }

//setter
void Desert::set_type(int type) { this->type = type; }


//////////////Forest/////////////////

Forest::Forest(bool is_exit, int index, vector<Object*>objects):Room("Forest",is_exit,index,objects) {
	
}

Forest::Forest() {}

Forest::Forest(int type) {
	this->type = type;
	set_name("Forest");
}

bool Forest::trigger_event(Object* object) {
	Player* player = dynamic_cast<Player*>(object);
	int choice;
	cout << "現在地區 : Forest" << endl << endl;
	if (type == 0) {
		cout << "在房間中有湖泊。" << endl;
		cout << "是否飲用湖水(回復Thrist值):" << endl;
		cout << "1. 是" << endl;
		cout << "2. 否" << endl;
		cin >> choice;
		if (choice == 1) {
			player->set_cur_thirst(player->get_max_thirst());
			cout << "飲用湖水回復 Thirst 至最大值" << endl;
		}
		else {
			cout << "離開湖邊" << endl;
		}
		cout << endl;
		system("pause");
		cout << endl;
	}
	else if (type == 1 && !get_event_happen()) {
		Food* temp=new Food("解毒草", 1);
		cout << "在森林中找到解毒草" << endl;
		player->add_item(temp);
		set_event_happen(1);
		cout << endl;
		system("pause");
		cout << endl;
	}
	else if (type == 2 && !get_event_happen()) {
		Food* temp=new Food("蘋果", 2);
		cout << "在樹上發現發現蘋果" << endl;
		player->add_item(temp);
		cout << endl;
		set_event_happen(1);
	}
	return 1;
}

int Forest::get_type() { return type; }


void Forest::set_type(int type) { this->type = type; }

//////////////Swamp/////////////////
Swamp::Swamp(bool is_exit, int index, vector<Object*>objects) :Room("Swamp", is_exit, index, objects) {

}

Swamp::Swamp(){}

Swamp::Swamp(int type) {
	this->type = type;
	set_name("Swamp");
}

bool Swamp::trigger_event(Object* object) {
	Player* player = dynamic_cast<Player*>(object);
	cout << "現在地區 : Swamp" << endl << endl;
	if (type == 0 && !get_event_happen()) {
		cout << "觸碰到有毒植物，玩家中毒" << endl;
		player->set_poison(1);
		set_event_happen(1);
		cout << endl;
		system("pause");
		cout << endl;
	}
	else if(type == 1 && !get_event_happen()) {
		cout << "房間事件" << endl;
		cout << "遭受水蛭攻擊，損失血量" << endl;
		player->cause_damage(player->get_max_hp()/5 + player->get_def());  //損失 1/5 最大值血量
		set_event_happen(1);
		cout << endl;
		system("pause");
		cout << endl;
	}
	else if (type == 2) {
		int choice;
		cout << "在房間中有乾淨水源。" << endl;
		cout << "是否飲用水源(回復Thrist值):" << endl;
		cout << "1. 是" << endl;
		cout << "2. 否" << endl;
		cin >> choice;
		if (choice == 1) {
			player->set_cur_thirst(player->get_max_thirst());
			cout << "飲用水源回復 Thirst 至最大值" << endl;
		}
		else {
			cout << "離開水源" << endl;
		}
		cout << endl;
		system("pause");
		cout << endl;
	}
	else if (type == 3) {
		cout << "發現破舊小屋" << endl;
		cout << "進去探索後，發現武器" << endl;
		Weapon* temp = new Weapon("Excalibur", 0, 30, 10);
		player->add_item(temp);
	}
	return player->check_die();
}

int Swamp::get_type() { return type; }

void Swamp::set_type(int type) { this->type = type; }

//////////////StartRoom/////////////////

Start_room::Start_room() {
	set_name("Start_room");
	start_room_setting();
}

void Start_room::start_room_setting() {
	set_index(0);
	Leader* leader=new Leader;
	vector<Object*> objects;
	objects.push_back(leader);

	//obects
	set_objects(objects);
}

bool Start_room::trigger_event(Object* object) {
	Player* player = dynamic_cast<Player*>(object);
	get_objects()[0]->trigger_event(player);
	return 1;
}

//////////////FinalRoom/////////////////
Final_room::Final_room(int index){
	final_room_setting();
	set_name("Final_room");
	set_index(index);
}

void Final_room::final_room_setting(){
	Boss* boss = new Boss();
	vector <Object*> objects;
	objects.push_back(boss);
	set_objects(objects);
	set_is_exit(1);
}

bool Final_room::trigger_event(Object* object) {
	Player* player = dynamic_cast<Player*>(object);
	cout << "Boss Room" << endl;
	
	return 1;
}