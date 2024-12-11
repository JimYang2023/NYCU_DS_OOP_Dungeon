#ifndef Player_h
#define Player_h

#include<iostream>
#include<vector>
#include<string>
#include"Item.h"
#include"GameCharacter.h"
#include"Map.h"
using namespace std;



class Player :public GameCharacter {
public:
	//Constructor
	Player();
	Player(string, int, int, int,int);
	//�K�[���~(�߰_:���~�[�Jinventory ���߰_:���~��Jcurrent_room)
	void add_item(Item*);
	//�K�[���~(��¥[�J���~)
	void add_item_normal(Item*);
	//�W�[���A(��W�˳�)
	void increase_status(int, int, int);
	//�ܴ��ж�
	void change_room(Room*);
	//
	bool trigger_event(Object*) override;
	//��ܨ��⪬�A
	void show_status();
	//��ܭI�]���~(�@�몬�A)
	void show_bag();
	//��ܭI�]���~(�԰���)
	int show_bag_fight();
	//��ܦa��
	void show_map();
	//�ϥΪ��~
	void use_item(int);
	//�W�[����
	void add_money(int);

	//thirst & hunger & power & poison
	// die return 0 / live return 1
	bool check_thirst();
	bool check_hunger();
	bool check_power();
	bool thrist_hunger_system();
	void take_break();
	bool poison_system();
	

	//setter & getter
	void set_current_room(Room*);
	void set_previous_room(Room*);
	void set_cur_hunger(int);
	void set_cur_thirst(int);
	void set_money(int);
	void set_profession(string);
	void set_max_power(int);
	void set_cur_power(int);
	void set_poison(int);
	void set_all_map(Map*);
	int get_max_thirst();
	int get_cur_thirst();
	int get_max_hunger();
	int get_cur_hunger();
	int get_money();
	int get_max_power();
	int get_cur_power();
	int get_poison();
	string get_profession();
	Room* get_current_room();
	Room* get_previous_room();
	vector<Item*> get_inventory();
	Map* get_map();
	
	

private:

	int max_thirst; 
	int cur_thirst; //���k�s�ɡA�y���԰����L�k�ϥΧޯ�
	int max_hunger;
	int cur_hunger; //��p��@�b�ɡA�Ͼ԰����۵M�^�_MP��bs
	int max_power;  
	int cur_power;  //�p�� 1/2 * max_power : �����O�U�� ; ���� 0 : �L�k���� 
	int poison;  // 0: no poison 1: cause by swamp 2: cause by monster
	
	int money;

	string profession;
	Room* current_room;
	Room* previous_room;
	vector<Item*> inventory;
	Map* map;
};

#endif