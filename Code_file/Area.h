#ifndef Area_h
#define Area_h

#include<iostream>
#include<string>
#include"Room.h"
#include"Player.h"
#include"NPC.h"
#include"Monster.h"

//////////////Desert/////////////////
/*
1. oasis �ɥR����  (type = 1)
2. sandstrooms hunger & thirst �ֳt���  (type = 0)
3. thirst ���ӥ[��
4. ��o�P�H�x (type = 2)
*/
class Desert :public Room {
public:
	Desert(bool, int, vector<Object*>);
	Desert();
	Desert(int);
	bool trigger_event(Object*) override;

	//getter & setter
	int get_type();
	void set_type(int);

private:
	int type;
};


//////////////Forest/////////////////
/*
1. Hunger ���ӥ[��
2. Lake ���Ѥ��� (type = 0)
3. Monster
4. �Ѭr�� (type = 1)
5. ���G (type = 2)
*/
class Forest :public Room {
public:
	Forest(bool, int, vector<Object*>);
	Forest();
	Forest(int);
	bool trigger_event(Object*) override;
	//getter & setter
	int get_type();
	void set_type(int);
private:
	int type;
};



//////////////Swamp/////////////////
/*
�ϰ�]�w:
1. hunger & thirst ���ӥ[��
2. �D����������A���v�ʦ��� (type = 1 )
3. Ĳ�I�즳�r�Ӫ��A���r (type = 0 )
4. ���b���� (type = 2)
5. �o�{�Z�� (type = 3 )
*/
class Swamp :public Room {
public:
	Swamp(bool, int, vector<Object*>);
	Swamp();
	Swamp(int);
	bool trigger_event(Object*) override;
	//getter & setter
	int get_type();
	void set_type(int);
private:
	int type;
};

//////////////StartRoom/////////////////

class Start_room : public Room {
public:
	Start_room();
	void start_room_setting();
	bool trigger_event(Object*) override;
private:

};

//////////////FinalRoom/////////////////

class Final_room :public Room {
public:
	Final_room(int);
	void final_room_setting();
	bool trigger_event(Object*) override;
private:

};
#endif