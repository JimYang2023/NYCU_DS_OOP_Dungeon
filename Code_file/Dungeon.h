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
	//遊戲的初始設定(create_player , create_map , 存檔設定 , 難度選擇)
	Player* start_game();
	//創建角色(職業選擇、名字輸入)
	Player* create_player();
	//創建地圖(隨機生成)
	void create_map(Player*);
	//處理player移動功能
	void handle_movement(Player*);
	//處理Monster Event
	void handle_event(Player*);
	// 處理撤退功能 1:撤退 0:繼續戰鬥
	bool handle_retreat(Player* player);
	// Having monster : return 1 
	bool check_monster_room(Room*);
	//return 1:move to new room
	bool choose_action(Player*, vector<Object*>);
	//檢測遊戲是否結束(player 成功抵達出口)
	bool check_game_logic(Player*);
	//執行遊戲
	void run_dungeon();
	//處理撿起物品功能
	bool take_up_object(Player*);

private:
	//顯示遊戲標題
	void show_logo();
	//遊戲成功通關
	void show_game_end();
	//Player 死亡
	void show_game_over();
	//遊戲介紹
	void game_introduction();
	//難度
	int mode;
	//數量 Dictionary ( 簡單 , 中等 , 困難 )  
	int businessman_number[3] = { 3 , 2 , 1 };
	int teacher_number[3] = { 2 , 1 , 1 };
	int monster_number[3] = { 2 , 4 , 6 };
	int room_number[3] = { 10 , 12 , 14 };
};



#endif