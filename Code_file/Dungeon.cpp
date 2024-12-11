#include"Dungeon.h"

//public function
Dungeon::Dungeon() {}

Player* Dungeon::start_game() {
	//variable
	int choice;
	Player* player = new Player();

	//
	show_logo();
	cout << "是否觀看遊戲介紹:" << endl;
	cout << "1. 是" << endl;
	cout << "2. 否" << endl;
	cin >> choice;
	if (choice == 1) { game_introduction(); }
	system("pause");
	system("cls");
	cout << "---------難度選擇---------" << endl;
	cout << "1. 簡單 : 商人多 怪物少 房間數量少" << endl;
	cout << "2. 中等 : 商人多 怪物多 房間數量中" << endl;
	cout << "3. 困難 : 商人少 怪物多 房間數量多" << endl;
	while (1) {
		cin >> choice;
		if (choice >= 1 && choice <= 3) { break; }
		else { cout << "輸入錯誤" << endl; }
	}
	switch (choice) {
	case 1:
		cout << "難度設定簡單" << endl;
		break;
	case 2:
		cout << "難度設定中等" << endl;
		break;
	case 3:
		cout << "難度設定困難" << endl;
		break;
	}
	mode = choice - 1;
	cout << "\n";
	system("pause");
	cout << "\n";
	player = create_player();		
	create_map(player);
	system("pause");
	system("cls");
	cout << "---------遊戲開始---------" << endl;
	return player;
}

Player* Dungeon::create_player() {
	//variable
	string name;
	int choice;
	Player* player;
	//輸入
	cout << "開始創建角色" << endl;
	cout << "請輸入你的角色名稱: " << endl;
	cin >> name;
	while (1) {
		cout << "---------職業選擇---------" << endl;
		cout << "   職業 : 角色特性" << endl;
		cout << "1. 戰士 : 高血量 防禦高 攻擊力低 " << endl;
		cout << "2. 遊俠 : 血量低 防禦低 攻擊立高 有機會閃避攻擊" << endl;
		cout << "3. 法師 : 血量低 防禦低 攻擊力最高 MP多" << endl;
		cout << "請選擇職業: " << endl;
		cin >> choice;
		if (choice <= 3 && choice > 0) {
			break;
		}
		else {
			cout << "輸入錯誤，請重新輸入。" << endl;
		}
	}
	//設定
	player= Player_setting(choice - 1);
	player->set_name(name);
	system("cls");
	cout << "創建角色成功。" << endl;
	player->show_status();

	return player;
}

//map setting
void Dungeon::create_map(Player* player) {
	srand(time(NULL));
	//variable setting
	int room_count = room_number[mode];
	Room* room;
	vector<Room*> rooms;
	Map setting_map(3,3);
	int create_room_pos;
	Pos pos;
	int type=0;
	int area_number[3] = { 2,3,3 };
	//start room setting
	room=new Start_room();
	player->change_room(room);
	pos = Pos(1, 1);
	player->get_map()->set_map(room, pos);
	rooms.push_back(room);
	setting_map.set_map(room, pos);
	int random_number;  //choosing which room is connected.
	int times = 1;
	//
	int i = 0;
	//
	while (times!=room_count) {
		//隨機選擇一個以生成的房間
		random_number = rand() % rooms.size();
		if (times == room_count - 1) {
			//final room setting
			room = new Final_room(room_count - 1);
			//避免 final_room 出現在 start_room 旁
			while (random_number == 0) {
				random_number = rand() % (rooms.size()-1) + 1;
			}
		}
		else {
			room = Room_setting(i,type,times);
			if (i == 2 && type == area_number[i]) {
				i = rand() % 9;
				if (i == 1 || i == 2 || i == 5) { i = 0; }
				else if (i == 0 || i == 6 || i == 7) { i = 1; }
				else { i = 2; }
				type = rand() % area_number[i];
			}
			else if (type == area_number[i]) {
				type = 0;
				i ++ ;
			}
			else {
				type++;
			}
		
		}
		room->set_index(times);
		//cout << random_number << endl;
		create_room_pos=rooms[random_number]->randomly_set_room(room, rooms[random_number], setting_map.check_near_room(setting_map.search(rooms[random_number])));
		if (create_room_pos != 0) {
			setting_map.update_map(room,rooms[random_number]);
			rooms.push_back(room);
			times++;
		}
	}
	//GameCharacter setting
	int b_number = businessman_number[mode];
	int t_number = teacher_number[mode];
	int m_number = monster_number[mode];
	int number_gamecharacter = b_number + t_number + m_number; //NPC number settiing
	GameCharacter* temp;
	//Debug
	if (number_gamecharacter > rooms.size() - 2) { cout << "number_NPC error" << endl; exit(1); }
	//
	for (int i = 0; i < number_gamecharacter; i++) {
		if (b_number) {
			random_number = rand() % 3;
			temp = Businessman_setting(random_number);
			b_number--;
		}
		else if(t_number) {
			random_number = rand() % 3;
			temp = Teacher_setting(random_number);
			t_number--;
		}
		else if (m_number) {
			random_number = rand() % 4;
			temp = Monster_setting(random_number);
		}
		else {
			cout << "Error" << endl;
			exit(1);
		}
		while (1) {
			random_number = (rand() % (rooms.size() - 2)) + 1;
			//Debug
			if (random_number < 0 || random_number >= rooms.size()) {
				cout << "Random_number : " << random_number << endl;
				exit(1);
			}
			//
			if (rooms[random_number]->get_objects().size() == 0 || (rooms[random_number]->get_objects().size()==1 && rooms[random_number]->get_objects()[0]->get_name()=="蜘蛛")) {
				break;
			}
		}
		rooms[random_number]->get_objects().push_back(temp);
	}
}

//處理player移動功能
void Dungeon::handle_movement(Player* player) {
	//variable
	int choice = 1;
	vector<Room*> rooms;
	int your_choice;

	//顯示可行走路線
	player->show_map();
	for (int i = 0; i < 4; i++) {
		if (player->get_current_room()->test_path(i)) {
			switch (i) {
			case 0:
				cout << choice << ". Go up."<<endl;
				rooms.push_back(player->get_current_room()->get_up_room());
				break;
			case 1:
				cout << choice << ". Go down." << endl;
				rooms.push_back(player->get_current_room()->get_down_room());
				break;
			case 2:
				cout << choice << ". Go right." << endl;
				rooms.push_back(player->get_current_room()->get_right_room());
				break;
			case 3:
				cout << choice << ". Go left." << endl;
				rooms.push_back(player->get_current_room()->get_left_room());
				break;
			}
			choice++;
		}
	}
	cout << "請選擇移動方向(輸入-1返回): ";

	//玩家輸入選項
	while (1) {
		cin >> your_choice;
		if (your_choice <= rooms.size() && your_choice > 0) { break; }
		else if (your_choice == -1) { break; }
		cout << "輸入錯誤，請從新輸入: ";
	}
	
	//執行 hunger & thirst & power & poison sysstem 並確認 player 是否死亡
	if (!player->thrist_hunger_system() || !player->poison_system()) {
		show_game_over();
	}
	
	//player 移動
	if (your_choice != -1) {
		player->change_room(rooms[your_choice - 1]);
		cout << "移動到新房間" << endl;
	}
}

//處理Monster Event
void Dungeon::handle_event(Player* player) {
	int check_retreat = 1;
	//偵測是否為Monster Room
	while (1) {
		if (check_monster_room(player->get_current_room())) {
			//逃跑
			check_retreat = handle_retreat(player);
		}
		else {
			//沒有Monster
			break;
		}
		if (!check_retreat) {
			system("cls");
			//戰鬥
			if (player->get_current_room()->get_objects()[0]->trigger_event(player)) {
				//Monster 死亡
				player->get_current_room()->get_objects().erase(player->get_current_room()->get_objects().begin());
			}
			else {
				//Player 死亡
				if (!player->check_die()) {
					show_game_over();
				}
				break;
			}
		}
		else { break; }  //已逃跑
	}
}

// 處理撤退功能 1:撤退 0:繼續戰鬥
bool Dungeon::handle_retreat(Player* player) { 
	char input;
	Room* temp;
	while (1) {
		Monster* monster = dynamic_cast<Monster*>(player->get_current_room()->get_objects()[0]);
		monster->show_status();
		cout << "請輸入是否撤退:" << endl << "1. 是" << endl << "2. 否" << endl;
		cin >> input;
		switch (input) {
		case '1':
			cout << "成功逃跑" << endl;
			player->change_room(player->get_previous_room());
			return 1;
			break;
		case '2':
			cout << "繼續戰鬥" << endl;
			return 0;
			break;
		default:
			cout << "輸入錯誤，請重新輸入。" << endl;
		}
	}
}

// Having monster : return 1 
bool Dungeon::check_monster_room(Room* room ) {
	for (int i = 0; i < room->get_objects().size(); i++) {
		if (room->get_objects()[i]->get_tag() == "Monster") {
			return 1;
			break;
		}
	}
	return 0;
}

//處理撿起物品功能
bool Dungeon::take_up_object(Player* player) {
	int choice,count,num;
	Item* temp=NULL;
	if (player->get_current_room()->get_objects().size() == 0) { cout << "房間內空無一物" << endl; return 1; }
	while (1) {
		num=player->get_current_room()->show_objects();
		cout << "請選擇要撿起的物品(輸入-1返回):" << endl;
		cin >> choice;
		if (choice == -1) { break; }
		else if (choice <= 0 || choice > num) {
			cout << "輸入錯誤，請重新輸入。" << endl;
		}
		else {
			for (int i = 0; i < player->get_current_room()->get_objects().size(); i++) {
				if (player->get_current_room()->get_objects()[i]->get_tag() == "NPC" || player->get_current_room()->get_objects()[i]->get_tag() == "Monster") {
					continue;
				}
				choice--;
				if (choice == 0) {
					temp = dynamic_cast<Item*>(player->get_current_room()->get_objects()[i]);
					player->get_current_room()->get_objects().erase(player->get_current_room()->get_objects().begin() + i);
					break;
				}
			}
			player->add_item_normal(temp);
			cout << "成功撿起物品" << endl;
			break;
		}
	}
	return 1;
}

//return 1:move to new room
bool Dungeon::choose_action(Player* player,vector<Object*> objects) {
	int choice, input = 0, count=1;
	cout << count++ <<". 顯示角色狀態" << endl;
	cout << count++ <<". 打開背包(使用物品)" << endl;
	cout << count++ <<". 前往下一個房間" << endl;
	cout << count++ << ". 休息(回復活力，會消耗 Hunger 和 Thirst):" << endl;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->get_tag() == "NPC") {
			cout << count++ << ". 與 NPC 對話 ("<< objects[i]->get_name() <<")" << endl;
			break;
		}
	}
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->get_tag() == "Weapon" || objects[i]->get_tag() == "Food" || objects[i]->get_tag() == "Recorver") {
			cout << 6 << ". 撿起物品" << endl;
			break;
		}
	}
	cout << "請選擇動作:" << endl;
	cin >> choice;
	switch (choice) {
	case 1:
		player->show_status();
		break;
	case 2:
		player->show_bag();
		int choice;
		while (1) {
			if (player->get_inventory().size() == 0) { break; }
			cout << "請輸入想使用的物品(輸入-1返回):" << endl;
			cin >> choice;
			if (choice == -1) { break; }
			if (choice<0 || choice >player->get_inventory().size()) {
				cout << "輸入錯誤，請重新輸入。" << endl;
			}
			else {
				player->use_item(choice-1);
				break;
			}
		}
		break;
	case 3:  //角色移動
		if (player->get_cur_power() == 0) {
			cout << "活力不足，無法移動" << endl;
		}
		else {
			cout << endl;
			handle_movement(player);
			return 1;
		}
		break;
	case 4:
		player->take_break();
		break;
	case 5:
		//Debug
		if (objects[0]->get_tag() != "NPC") {
			cout << "object tag error " << endl;
			exit(1);
		}
		//與NPC互動
		objects[0]->trigger_event(player);
		break;
	case 6:
		take_up_object(player);
		break;
	}
	return 0;
}


bool Dungeon::check_game_logic(Player* player) { 
	if (player->get_current_room()->get_is_exit()) {
		return 1;
	}
	return 0;
}


void Dungeon::run_dungeon() {
	int choice;
	int go_to_new_room=1;
	Player* player=start_game();
	while (1) {
		system("cls");
		if (!player->check_die()) {
			show_game_over();
		}
		//1. trigger_event
		handle_event(player);
		//room trigger event
		if (go_to_new_room) {
			player->get_current_room()->trigger_event(player);
			system("cls");
		}
		//2. check_game_end
		if (check_game_logic(player) && !check_monster_room(player->get_current_room())) {
			cout << "請選擇是否離開: \n1: 是\n2: 否" << endl;
			cin >> choice;
			if (choice == 1) {
				break;
				system("cls");
			}
		}
		//3. choose action
		go_to_new_room = choose_action(player, player->get_current_room()->get_objects());
		cout << endl;
		system("Pause");
	}
	show_game_end();
}


//private function
void Dungeon::show_logo() {
	cout << endl << endl << endl << endl;
	cout << "\t......     ..          ..    ....       ..          ......        ........          ....         ....       .. " << endl;
	cout << "\t.......    ..          ..    .. ..      ..       ....    ...      ........       ...    ...      .. ..      .. " << endl;
	cout << "\t..    ..   ..          ..    ..  ..     ..     ..          ..     ..           ..          ..    ..  ..     .. " << endl;
	cout << "\t..    ..   ..          ..    ..   ..    ..     ..                 ........    ..            ..   ..   ..    .. " << endl;
	cout << "\t..    ..   ..          ..    ..    ..   ..     ..      ......     ........    ..            ..   ..    ..   .. " << endl;
	cout << "\t..    ..    ..        ..     ..     ..  ..     ..      ..  ...    ..           ..          ..    ..     ..  .. " << endl;
	cout << "\t.......      ...    ...      ..      .. ..       ..       ...     ........       ...    ...      ..      .. .. " << endl;
	cout << "\t......         ......        ..       ....         ........       ........          ....         ..       .... " << endl;
	cout << endl << endl << endl << endl;
	system("pause");
	system("cls");
}

void Dungeon::show_game_end() {
	cout << "\t..         ..          ....           ..          ..         ..       ..        ..    ..........    ....       ..  " << endl;
	cout << "\t ..       ..        ...    ...        ..          ..         ..      ....       ..    ..........    .. ..      ..  " << endl;
	cout << "\t  ..    ..        ..          ..      ..          ..          ..    ..  ..     ..         ..        ..  ..     ..  " << endl;
	cout << "\t   ......        ..            ..     ..          ..          ..    ..  ..     ..         ..        ..   ..    ..  " << endl;
	cout << "\t    ....         ..            ..     ..          ..           ..  ..    ..   ..          ..        ..    ..   ..  " << endl;
	cout << "\t     ..           ..          ..       ..        ..    ...     ..  ..     ..  ..          ..        ..     ..  ..  " << endl;
	cout << "\t     ..             ...    ...          ...    ...     ...      ....       ....       ..........    ..      .. ..  " << endl;
	cout << "\t     ..                ....               ......      ..        ....       ....       .........,    ..       ....  " << endl;
}

void Dungeon::show_game_over() {
	cout << "\t..         ..          ....           ..          ..         ......         ..........      ........  " << endl;
	cout << "\t ..       ..        ...    ...        ..          ..         .......        ..........      ........  " << endl;
	cout << "\t  ..    ..        ..          ..      ..          ..         ..    ..           ..          ..        " << endl;
	cout << "\t   ......        ..            ..     ..          ..         ..    ..           ..          ........  " << endl;
	cout << "\t    ....         ..            ..     ..          ..         ..    ..           ..          ........  " << endl;
	cout << "\t     ..           ..          ..       ..        ..    ...   ..    ..           ..          ..        " << endl;
	cout << "\t     ..             ...    ...          ...    ...     ...   .......        ..........      ........  " << endl;
	cout << "\t     ..                ....               ......      ..     ......         .........,      ........  " << endl;
	exit(1);
}

void Dungeon::game_introduction() {
	cout << endl << endl;
	cout << "遊戲故事:" << endl << endl;
	cout << "在大陸上，突然出現許多地下城，沒有人知道地下城是如何生成的。\n只發現會有魔物從裡面湧出來，再冒險者反覆探勘後，發現在地下城深處會有一位魔王。\n";
	cout << "地下城因為魔王的魔力影響，產生特別的結構。\n房間內有獨特的生態，且相鄰的房間可能出現極端不同的生態。\n";
	cout << "為了避免魔物湧出，只能殺掉魔王，解放地下城\n" << endl << endl;
	system("pause");
	cout << endl << "遊戲機制:" << endl << endl;
	cout << "透過移動在地下城中探險。\n有時會遇到商人，可以與其交易武器、食物或藥水。\n有時會遇到怪物必須與其戰鬥\n";
	cout << "除了注意戰鬥外，管控好自己身體數值業是重要的一環" << endl<<endl;
	cout << "Hunger(飢餓值) : 當小於一半時，使戰鬥中自然回復MP減半" << endl;
	cout << "Thirst(口渴值) : 當歸零時，造成戰鬥中無法使用技能。" << endl;
	cout << "Poison(中毒狀態) : 會在行動時造成損血" << endl;
	cout << "Power(活力值) : 當小一半時，會讓攻擊下降1/3 ，幫歸零時，就無法移動。" << endl;
	cout << endl << endl;
}