#ifndef Dungeon_h
#define Dungeon_h

#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<map>
#include"Setting_Function.h"
#include"Area.h"
using namespace std;

class Dungeon {
public:
	//Constructor
	Dungeon();
	//�C������l�]�w(create_player , create_map , �s�ɳ]�w , ���׿��)
	Player* start_game();
	//�Ыب���(¾�~��ܡB�W�r��J)
	Player* create_player();
	//�Ыئa��(�H���ͦ�)
	void create_map(Player*);
	//�B�zplayer���ʥ\��
	void handle_movement(Player*);
	//�B�zMonster Event
	void handle_event(Player*);
	// �B�z�M�h�\�� 1:�M�h 0:�~��԰�
	bool handle_retreat(Player* player);
	// Having monster : return 1 
	bool check_monster_room(Room*);
	//return 1:move to new room
	bool choose_action(Player*, vector<Object*>);
	//�˴��C���O�_����(player ���\��F�X�f)
	bool check_game_logic(Player*);
	//����C��
	void run_dungeon();
	//�B�z�߰_���~�\��
	bool take_up_object(Player*);

private:
	//��ܹC�����D
	void show_logo();
	//�C�����\�q��
	void show_game_end();
	//Player ���`
	void show_game_over();
	//�C������
	void game_introduction();
	//����
	int mode;
	//�ƶq Dictionary ( ²�� , ���� , �x�� )  
	int businessman_number[3] = { 3 , 2 , 1 };
	int teacher_number[3] = { 2 , 1 , 1 };
	int monster_number[3] = { 2 , 4 , 6 };
	int room_number[3] = { 10 , 12 , 14 };
};



#endif