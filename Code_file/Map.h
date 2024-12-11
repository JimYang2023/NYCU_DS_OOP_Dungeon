#ifndef Map_h
#define Map_h 

#include<iostream>
#include<vector>
#include"Room.h"
using namespace std;

//負責標示位置
class Pos {
public:
	Pos(); //
	Pos(int, int); //
	int x;
	int y;
};

//兩個位置相加
Pos operator + (Pos a, Pos b);

//Map
class Map {
public:
	//Constructor
	Map();
	Map(int, int);
	//初始化地圖
	void initial_map();
	//在 map 中尋找 room
	Pos search(Room*);
	//設定room 在 pos 的位置上
	void set_map(Room*, Pos); 
	//更新map資訊
	void update_map(Room*, Room*); 
	//偵測在 Map 上周圍是否有房間
	vector<int> check_near_room(Pos);
	//顯示map
	void show_map(); 
	//getter & setter
	int get_size_x();
	int get_size_y();
	vector<vector<Room*>> get_map();
	void set_size_x(int);
	void set_size_y(int);
	void set_size(int, int);
private:
	//增加 map 的大小
	void increase_map_size(int,char);
	//地圖在 x 方向的大小
	int map_size_x;
	//地圖在 y 方向的大小
	int map_size_y;
	vector<vector<Room*>> map;
};

#endif

