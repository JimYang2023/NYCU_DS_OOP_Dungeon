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
1. oasis 補充水源  (type = 1)
2. sandstrooms hunger & thirst 快速減少  (type = 0)
3. thirst 消耗加倍
4. 獲得仙人掌 (type = 2)
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
1. Hunger 消耗加倍
2. Lake 提供水源 (type = 0)
3. Monster
4. 解毒草 (type = 1)
5. 水果 (type = 2)
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
區域設定:
1. hunger & thirst 消耗加倍
2. 遭受水蛭攻擊，機率性扣血 (type = 1 )
3. 觸碰到有毒植物，中毒 (type = 0 )
4. 乾淨水源 (type = 2)
5. 發現武器 (type = 3 )
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