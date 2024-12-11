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
	//�˴��ж����q�D (�Ҧ�: 0:up 1:down 2:right 3:left)
	//return 1:���q�D 0:�L�q�D
	bool test_path(int);
	//�H���ͦ��ж�
	int randomly_set_room(Room*, Room*, vector<int>);
	//�M��ж����t
	//return ( U:�b�W��  D:�b�U��  L:�b����  R:�b�k��  N:�L  )
	char find_relation(Room*);
	//�b�ж����[�J����
	void add_object(Object*);
	//��ܩж������Ҧ�����
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
	bool is_exit;  //�X�f
	int index;     //�ж��s��
	//Gamecharacter : monster �i�঳�ܦh��  NPC �u�|���@��
	//Item :�@����Monster 
	vector<Object*> objects;

	//�����ƥ�O�_�o��
	bool event_happen;
};

#endif

/*  
1�өж� 1�� NPC or Monster

*/