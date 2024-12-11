#ifndef Map_h
#define Map_h 

#include<iostream>
#include<vector>
#include"Room.h"
using namespace std;

//�t�d�Хܦ�m
class Pos {
public:
	Pos(); //
	Pos(int, int); //
	int x;
	int y;
};

//��Ӧ�m�ۥ[
Pos operator + (Pos a, Pos b);

//Map
class Map {
public:
	//Constructor
	Map();
	Map(int, int);
	//��l�Ʀa��
	void initial_map();
	//�b map ���M�� room
	Pos search(Room*);
	//�]�wroom �b pos ����m�W
	void set_map(Room*, Pos); 
	//��smap��T
	void update_map(Room*, Room*); 
	//�����b Map �W�P��O�_���ж�
	vector<int> check_near_room(Pos);
	//���map
	void show_map(); 
	//getter & setter
	int get_size_x();
	int get_size_y();
	vector<vector<Room*>> get_map();
	void set_size_x(int);
	void set_size_y(int);
	void set_size(int, int);
private:
	//�W�[ map ���j�p
	void increase_map_size(int,char);
	//�a�Ϧb x ��V���j�p
	int map_size_x;
	//�a�Ϧb y ��V���j�p
	int map_size_y;
	vector<vector<Room*>> map;
};

#endif

