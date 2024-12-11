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
	cout << "�{�b�a�� : Desert" << endl << endl;
	if (type==1) {
		//oasis
		//��X��w��T
		cout << "�b�ж�������w�C" << endl;
		cout << "�O�_���κ�w�u��(�^�_Thrist��):" << endl;
		cout << "1. �O" << endl;
		cout << "2. �_" << endl;
		//Player ���
		cin >> choice;
		if (choice == 1) {
			player->set_cur_thirst(player->get_max_thirst());
			cout << "���άu���^�_ Thirst �̤ܳj��" << endl;
		}
		else { cout << "���}��w" << endl; }
		cout << endl;
		system("pause");
		cout << endl;
	}
	else if(type == 0 && !get_event_happen()){
		//sandstorms
		cout << "�D�J�F�мɡA���j�ȻP�����j�q��֡C(��ֳ̤j�Ȫ�1/3)" << endl;
		//�����P���j�ȴ��1/3
		player->set_cur_thirst(player->get_cur_thirst() - player->get_max_thirst() / 3);
		player->set_cur_hunger(player->get_cur_hunger() - player->get_max_hunger() / 3);
		//�ˬd Hunger & Thirst �O�_�p�� 0
		if (player->get_cur_hunger() < 0) {
			player->set_cur_hunger(0);
		}
		if (player->get_cur_thirst() < 0) {
			player->set_cur_thirst(0);
		}
		//
		cout << " Thirst : " << player->get_cur_thirst() << " / " << player->get_max_thirst() << endl;
		cout << " Hunger : " << player->get_cur_hunger() << " / " << player->get_max_hunger() << endl;
		//�e����z
		cout << endl;
		system("pause");
		cout << endl;
		//�]�w�ƥ�w�o��
		set_event_happen(1);
	}
	else if (type == 2 && !get_event_happen()) {
		cout << endl << endl;
		cout << "�b�F�z���o�{�P�H�x" << endl;
		Food* temp =new Food("�P�H�x", 2);
		player->add_item(temp);
		//�]�w�ƥ�w�o��
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
	cout << "�{�b�a�� : Forest" << endl << endl;
	if (type == 0) {
		cout << "�b�ж�������y�C" << endl;
		cout << "�O�_���δ��(�^�_Thrist��):" << endl;
		cout << "1. �O" << endl;
		cout << "2. �_" << endl;
		cin >> choice;
		if (choice == 1) {
			player->set_cur_thirst(player->get_max_thirst());
			cout << "���δ���^�_ Thirst �̤ܳj��" << endl;
		}
		else {
			cout << "���}����" << endl;
		}
		cout << endl;
		system("pause");
		cout << endl;
	}
	else if (type == 1 && !get_event_happen()) {
		Food* temp=new Food("�Ѭr��", 1);
		cout << "�b�˪L�����Ѭr��" << endl;
		player->add_item(temp);
		set_event_happen(1);
		cout << endl;
		system("pause");
		cout << endl;
	}
	else if (type == 2 && !get_event_happen()) {
		Food* temp=new Food("ī�G", 2);
		cout << "�b��W�o�{�o�{ī�G" << endl;
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
	cout << "�{�b�a�� : Swamp" << endl << endl;
	if (type == 0 && !get_event_happen()) {
		cout << "Ĳ�I�즳�r�Ӫ��A���a���r" << endl;
		player->set_poison(1);
		set_event_happen(1);
		cout << endl;
		system("pause");
		cout << endl;
	}
	else if(type == 1 && !get_event_happen()) {
		cout << "�ж��ƥ�" << endl;
		cout << "�D����������A�l����q" << endl;
		player->cause_damage(player->get_max_hp()/5 + player->get_def());  //�l�� 1/5 �̤j�Ȧ�q
		set_event_happen(1);
		cout << endl;
		system("pause");
		cout << endl;
	}
	else if (type == 2) {
		int choice;
		cout << "�b�ж��������b�����C" << endl;
		cout << "�O�_���Τ���(�^�_Thrist��):" << endl;
		cout << "1. �O" << endl;
		cout << "2. �_" << endl;
		cin >> choice;
		if (choice == 1) {
			player->set_cur_thirst(player->get_max_thirst());
			cout << "���Τ����^�_ Thirst �̤ܳj��" << endl;
		}
		else {
			cout << "���}����" << endl;
		}
		cout << endl;
		system("pause");
		cout << endl;
	}
	else if (type == 3) {
		cout << "�o�{�}�¤p��" << endl;
		cout << "�i�h������A�o�{�Z��" << endl;
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