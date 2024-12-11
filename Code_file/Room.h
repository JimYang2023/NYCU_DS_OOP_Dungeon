#ifndef Room_h
#define Room_h

#include<cstdlib>
#include<ctime>
#include<iostream>
#include<vector>
#include"Object.h"
#include"GameCharacter.h"
#include"Item.h"
using namespace std;

class Room:public Object{
public:
	//Constructor
	Room();
	Room(string,bool, int, vector<Object*>);
	//virtual function
	virtual bool trigger_event(Object*) override;
	virtual int get_type();
	//檢測房間的通道 (模式: 0:up 1:down 2:right 3:left)
	//return 1:有通道 0:無通道
	bool test_path(int);
	//隨機生成房間
	int randomly_set_room(Room*, Room*, vector<int>);
	//尋找房間關系
	//return ( U:在上方  D:在下方  L:在左方  R:在右方  N:無  )
	char find_relation(Room*);
	//在房間中加入物件
	void add_object(Object*);
	//顯示房間中的所有物件
	int show_objects();
	//getter & setter
	int get_go_through();
	int get_index();
	bool get_is_exit();
	bool get_event_happen();
	Room* get_up_room();
	Room* get_down_room();
	Room* get_right_room();
	Room* get_left_room();
	vector<Object*>& get_objects();
	void set_go_throough(int);
	void set_is_exit(bool);
	void set_index(int);
	void set_event_happen(bool);
	void set_up_room(Room*);
	void set_down_room(Room*);
	void set_right_room(Room*);
	void set_left_room(Room*);
	void set_objects(vector<Object*>);

private:
	int go_through;
	Room* up_room;
	Room* down_room;
	Room* right_room;
	Room* left_room;
	bool is_exit;  //出口
	int index;     //房間編號
	//Gamecharacter : monster 可能有很多個  NPC 只會有一個
	//Item :　打倒Monster 
	vector<Object*> objects;

	//紀錄事件是否發生
	bool event_happen;
};

#endif

/*  
1個房間 1個 NPC or Monster

*/