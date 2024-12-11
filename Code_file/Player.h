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
	//添加物品(撿起:物品加入inventory 未撿起:物品放入current_room)
	void add_item(Item*);
	//添加物品(單純加入物品)
	void add_item_normal(Item*);
	//增加狀態(穿上裝備)
	void increase_status(int, int, int);
	//變換房間
	void change_room(Room*);
	//
	bool trigger_event(Object*) override;
	//顯示角色狀態
	void show_status();
	//顯示背包物品(一般狀態)
	void show_bag();
	//顯示背包物品(戰鬥中)
	int show_bag_fight();
	//顯示地圖
	void show_map();
	//使用物品
	void use_item(int);
	//增加金錢
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
	int cur_thirst; //當歸零時，造成戰鬥中無法使用技能
	int max_hunger;
	int cur_hunger; //當小於一半時，使戰鬥中自然回復MP減半s
	int max_power;  
	int cur_power;  //小於 1/2 * max_power : 攻擊力下降 ; 等於 0 : 無法移動 
	int poison;  // 0: no poison 1: cause by swamp 2: cause by monster
	
	int money;

	string profession;
	Room* current_room;
	Room* previous_room;
	vector<Item*> inventory;
	Map* map;
};

#endif