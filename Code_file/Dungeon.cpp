#include"Dungeon.h"

//public function
Dungeon::Dungeon() {}

Player* Dungeon::start_game() {
	//variable
	int choice;
	Player* player = new Player();

	//
	show_logo();
	cout << "�O�_�[�ݹC������:" << endl;
	cout << "1. �O" << endl;
	cout << "2. �_" << endl;
	cin >> choice;
	if (choice == 1) { game_introduction(); }
	system("pause");
	system("cls");
	cout << "---------���׿��---------" << endl;
	cout << "1. ²�� : �ӤH�h �Ǫ��� �ж��ƶq��" << endl;
	cout << "2. ���� : �ӤH�h �Ǫ��h �ж��ƶq��" << endl;
	cout << "3. �x�� : �ӤH�� �Ǫ��h �ж��ƶq�h" << endl;
	while (1) {
		cin >> choice;
		if (choice >= 1 && choice <= 3) { break; }
		else { cout << "��J���~" << endl; }
	}
	switch (choice) {
	case 1:
		cout << "���׳]�w²��" << endl;
		break;
	case 2:
		cout << "���׳]�w����" << endl;
		break;
	case 3:
		cout << "���׳]�w�x��" << endl;
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
	cout << "---------�C���}�l---------" << endl;
	return player;
}

Player* Dungeon::create_player() {
	//variable
	string name;
	int choice;
	Player* player;
	//��J
	cout << "�}�l�Ыب���" << endl;
	cout << "�п�J�A������W��: " << endl;
	cin >> name;
	while (1) {
		cout << "---------¾�~���---------" << endl;
		cout << "   ¾�~ : ����S��" << endl;
		cout << "1. �Ԥh : ����q ���m�� �����O�C " << endl;
		cout << "2. �C�L : ��q�C ���m�C �����߰� �����|�{�ק���" << endl;
		cout << "3. �k�v : ��q�C ���m�C �����O�̰� MP�h" << endl;
		cout << "�п��¾�~: " << endl;
		cin >> choice;
		if (choice <= 3 && choice > 0) {
			break;
		}
		else {
			cout << "��J���~�A�Э��s��J�C" << endl;
		}
	}
	//�]�w
	player= Player_setting(choice - 1);
	player->set_name(name);
	system("cls");
	cout << "�Ыب��⦨�\�C" << endl;
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
		//�H����ܤ@�ӥH�ͦ����ж�
		random_number = rand() % rooms.size();
		if (times == room_count - 1) {
			//final room setting
			room = new Final_room(room_count - 1);
			//�קK final_room �X�{�b start_room ��
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
			if (rooms[random_number]->get_objects().size() == 0 || (rooms[random_number]->get_objects().size()==1 && rooms[random_number]->get_objects()[0]->get_name()=="�j��")) {
				break;
			}
		}
		rooms[random_number]->get_objects().push_back(temp);
	}
}

//�B�zplayer���ʥ\��
void Dungeon::handle_movement(Player* player) {
	//variable
	int choice = 1;
	vector<Room*> rooms;
	int your_choice;

	//��ܥi�樫���u
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
	cout << "�п�ܲ��ʤ�V(��J-1��^): ";

	//���a��J�ﶵ
	while (1) {
		cin >> your_choice;
		if (your_choice <= rooms.size() && your_choice > 0) { break; }
		else if (your_choice == -1) { break; }
		cout << "��J���~�A�бq�s��J: ";
	}
	
	//���� hunger & thirst & power & poison sysstem �ýT�{ player �O�_���`
	if (!player->thrist_hunger_system() || !player->poison_system()) {
		show_game_over();
	}
	
	//player ����
	if (your_choice != -1) {
		player->change_room(rooms[your_choice - 1]);
		cout << "���ʨ�s�ж�" << endl;
	}
}

//�B�zMonster Event
void Dungeon::handle_event(Player* player) {
	int check_retreat = 1;
	//�����O�_��Monster Room
	while (1) {
		if (check_monster_room(player->get_current_room())) {
			//�k�]
			check_retreat = handle_retreat(player);
		}
		else {
			//�S��Monster
			break;
		}
		if (!check_retreat) {
			system("cls");
			//�԰�
			if (player->get_current_room()->get_objects()[0]->trigger_event(player)) {
				//Monster ���`
				player->get_current_room()->get_objects().erase(player->get_current_room()->get_objects().begin());
			}
			else {
				//Player ���`
				if (!player->check_die()) {
					show_game_over();
				}
				break;
			}
		}
		else { break; }  //�w�k�]
	}
}

// �B�z�M�h�\�� 1:�M�h 0:�~��԰�
bool Dungeon::handle_retreat(Player* player) { 
	char input;
	Room* temp;
	while (1) {
		Monster* monster = dynamic_cast<Monster*>(player->get_current_room()->get_objects()[0]);
		monster->show_status();
		cout << "�п�J�O�_�M�h:" << endl << "1. �O" << endl << "2. �_" << endl;
		cin >> input;
		switch (input) {
		case '1':
			cout << "���\�k�]" << endl;
			player->change_room(player->get_previous_room());
			return 1;
			break;
		case '2':
			cout << "�~��԰�" << endl;
			return 0;
			break;
		default:
			cout << "��J���~�A�Э��s��J�C" << endl;
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

//�B�z�߰_���~�\��
bool Dungeon::take_up_object(Player* player) {
	int choice,count,num;
	Item* temp=NULL;
	if (player->get_current_room()->get_objects().size() == 0) { cout << "�ж����ŵL�@��" << endl; return 1; }
	while (1) {
		num=player->get_current_room()->show_objects();
		cout << "�п�ܭn�߰_�����~(��J-1��^):" << endl;
		cin >> choice;
		if (choice == -1) { break; }
		else if (choice <= 0 || choice > num) {
			cout << "��J���~�A�Э��s��J�C" << endl;
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
			cout << "���\�߰_���~" << endl;
			break;
		}
	}
	return 1;
}

//return 1:move to new room
bool Dungeon::choose_action(Player* player,vector<Object*> objects) {
	int choice, input = 0, count=1;
	cout << count++ <<". ��ܨ��⪬�A" << endl;
	cout << count++ <<". ���}�I�](�ϥΪ��~)" << endl;
	cout << count++ <<". �e���U�@�өж�" << endl;
	cout << count++ << ". ��(�^�_���O�A�|���� Hunger �M Thirst):" << endl;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->get_tag() == "NPC") {
			cout << count++ << ". �P NPC ��� ("<< objects[i]->get_name() <<")" << endl;
			break;
		}
	}
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->get_tag() == "Weapon" || objects[i]->get_tag() == "Food" || objects[i]->get_tag() == "Recorver") {
			cout << 6 << ". �߰_���~" << endl;
			break;
		}
	}
	cout << "�п�ܰʧ@:" << endl;
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
			cout << "�п�J�Q�ϥΪ����~(��J-1��^):" << endl;
			cin >> choice;
			if (choice == -1) { break; }
			if (choice<0 || choice >player->get_inventory().size()) {
				cout << "��J���~�A�Э��s��J�C" << endl;
			}
			else {
				player->use_item(choice-1);
				break;
			}
		}
		break;
	case 3:  //���Ⲿ��
		if (player->get_cur_power() == 0) {
			cout << "���O�����A�L�k����" << endl;
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
		//�PNPC����
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
			cout << "�п�ܬO�_���}: \n1: �O\n2: �_" << endl;
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
	cout << "�C���G��:" << endl << endl;
	cout << "�b�j���W�A��M�X�{�\�h�a�U���A�S���H���D�a�U���O�p��ͦ����C\n�u�o�{�|���]���q�̭���X�ӡA�A�_�I�̤��б��ɫ�A�o�{�b�a�U���`�B�|���@���]���C\n";
	cout << "�a�U���]���]�����]�O�v�T�A���ͯS�O�����c�C\n�ж������W�S���ͺA�A�B�۾F���ж��i��X�{���ݤ��P���ͺA�C\n";
	cout << "���F�קK�]����X�A�u������]���A�ѩ�a�U��\n" << endl << endl;
	system("pause");
	cout << endl << "�C������:" << endl << endl;
	cout << "�z�L���ʦb�a�U�������I�C\n���ɷ|�J��ӤH�A�i�H�P�����Z���B�������Ĥ��C\n���ɷ|�J��Ǫ������P��԰�\n";
	cout << "���F�`�N�԰��~�A�ޱ��n�ۤv����ƭȷ~�O���n���@��" << endl<<endl;
	cout << "Hunger(���j��) : ��p��@�b�ɡA�Ͼ԰����۵M�^�_MP��b" << endl;
	cout << "Thirst(�f����) : ���k�s�ɡA�y���԰����L�k�ϥΧޯ�C" << endl;
	cout << "Poison(���r���A) : �|�b��ʮɳy���l��" << endl;
	cout << "Power(���O��) : ��p�@�b�ɡA�|�������U��1/3 �A���k�s�ɡA�N�L�k���ʡC" << endl;
	cout << endl << endl;
}