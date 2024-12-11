#include"Player.h"


Player::Player() {
	previous_room = NULL;
	current_room = NULL;
	max_thirst = 0;
	max_hunger = 0;
	cur_thirst = max_thirst;
	cur_hunger = max_hunger;
	map=new Map(0, 0);
}

Player::Player(string name, int max_hp, int attack, int defense,int mp):GameCharacter(name,max_hp,attack,defense,mp) {
	max_thirst = 10;  //�ƭȽվ�
	max_hunger = 10;  //�ƭȽվ�
	max_power = 10;
	cur_thirst = max_thirst;
	cur_hunger = max_hunger;
	cur_power = max_power;
	poison = 0;
	set_current_room(NULL);
	//show_status();
	set_tag("Player");
	map = new Map(3,3);
}


void Player::add_item(Item* new_item) {
	int choice=0;
	Item* new_item_ptr=NULL;
	while (1) {
		cout << "�O�_�߰_���~:" << endl;
		cout << "1: �O" << endl;
		cout << "2: �_" << endl;
		cin >> choice;
		if (choice > 0 || choice < 3) {
			if (new_item->get_tag() == "Weapon") {
				new_item_ptr = new_item;
			}
			else if (new_item->get_tag() == "Recorver") {
				Recorver* temp = dynamic_cast<Recorver*>(new_item);
				new_item_ptr = new Recorver(new_item->get_value(), temp->get_type());
			}
			else if (new_item->get_tag() == "Food") {
				new_item_ptr = new Food(new_item->get_name(), new_item->get_value());
			}
			else { 
				cout << "Error(add_ittem)" << endl; 
				exit(1);
			}
			if (choice == 1) {
				//Debug
				//cout << "Adding item success" << endl;
				//
				inventory.push_back(new_item_ptr);
			}
			else{
				//Debug
				//cout << "Adding item success(Room)" << endl;
				//
				current_room->add_object(new_item_ptr);
			}
			break;
		}
		else {
			cout << " ��J���~�Э��s��J " << endl;
		}
	}
}

void Player::add_item_normal(Item* item) {
	inventory.push_back(item);
}

void Player::increase_status(int add_hp, int add_atk, int add_def) {
	set_max_hp(add_hp + get_max_hp());
	set_atk(add_atk + get_atk());
	set_def(add_def + get_def());
}

void Player::change_room(Room* room) {
	previous_room = current_room;
	current_room = room;
	current_room->set_go_throough(2);
	if (previous_room != NULL) { previous_room->set_go_throough(1); }
	map->update_map(current_room, previous_room);
}

bool Player::trigger_event(Object*) {
	return 1;
}

void Player::show_status() {
	cout << "----------------------" << endl;
	cout << "����W��: " << get_name() << endl;
	cout << "¾�~: " << profession <<endl;
	cout << "HP: " << get_cur_hp() << "/" << get_max_hp() << endl;
	cout << "ATK: " << get_atk() << endl;
	cout << "DEF: " << get_def() << endl;
	cout << "MP: " << get_cur_mp() << "/" << get_max_mp() << endl;
	cout << "Thirst(�f����): " << cur_thirst << "/" << max_thirst << endl;
	cout << "Hunger(���j��): " << cur_hunger << "/" << max_hunger << endl;
	cout << "Power(���O��): " << cur_power << "/" << max_power << endl;
	cout << "Poison(���r���A): " << poison;
	switch (poison) {
	case 0:
		cout << " (�����r)" << endl;
		break;
	case 1:
		cout << " (�Ӫ����r)" << endl;
		break;
	case 2:
		cout << " (�Ǫ����r)" << endl;
		break;
	}
	cout << "Money: " << money << endl;
	cout << endl;

	//bag
	show_bag();
	
	//status
	int count = 1;
	cout << endl << "���⪬�A:" << endl;
	if(cur_hunger<max_hunger/2){
		cout << count++ << ". ���j(�۵M�^�_MP��b)" << endl;
	}
	if (cur_thirst <= 3) {
		cout << count++ << ". ��z(�L�k�ϥΧޯ�)" << endl;
	}
	if (poison != 0) {
		cout << count++ << ". ���r(�H�۲��ʷl��)" << endl;
	}
	if (cur_power < max_power / 2) {
		cout << count++ << ". �h��(�����O��b)" << endl;
	}
	if (cur_power == 0) {
		cout << count++ << ". �L�O(�L�k����)" << endl;
	}
	//
	cout << endl << "----------------------" << endl;
}

void Player::show_bag() {
	int count;
	cout << "Item:" << endl;
	if (inventory.size() == 0) {
		cout << "No Item." << endl;
	}
	else {
		count = 1;
		for (int i = 0; i < inventory.size(); i++) {
			if (inventory[i]->get_tag() == "Weapon") {
				if (inventory[i]->get_value() == 1) {
					cout << i + 1 << ". " << "�Z�� " << inventory[i]->get_name() << "\t\t�w�˳�" << "\t/ HP : "<<inventory[i]->get_health()<< "\t/ ATK : "<< inventory[i]->get_attack() << "\t/ Def : "<< inventory[i]->get_defense() << endl;
				}
				else {
					cout << i + 1 << ". " << "�Z�� " << inventory[i]->get_name() << "\t\t���˳�" << "\t/ HP : " << inventory[i]->get_health() << "\t/ ATK : " << inventory[i]->get_attack() << "\t/ Def : " << inventory[i]->get_defense() << endl;
				}
			}
			else if(inventory[i]->get_tag()=="Recorver") {
				cout << i + 1 << ". " << "�Ĥ� " << inventory[i]->get_name() << "\t�^�_�ƭ�: "<< inventory[i]->get_value() << endl;
			}
			else if (inventory[i]->get_tag() == "Food") {
				cout << i + 1 << ". " << "���� " << inventory[i]->get_name() << "\t\t�^�_�ƭ�: " << inventory[i]->get_value() << endl;
			}
		}
	}
}

void Player::show_map() {
	cout << "�{�b�a�� : " << current_room->get_name() << endl;
	map->show_map();
}

//setter
void Player::set_current_room(Room* current_room) { this->current_room = current_room; }
void Player::set_previous_room(Room* previous_room) { this->previous_room = previous_room; }
void Player::set_cur_hunger(int cur_hunger) { this->cur_hunger = cur_hunger; }
void Player::set_cur_thirst(int cur_thirst) { this->cur_thirst = cur_thirst; }
void Player::set_money(int money) { this->money = money; }
void Player::set_profession(string name) { this->profession = name; }
void Player::set_max_power(int max_power) { this->max_power = max_power; }
void Player::set_cur_power(int cur_power) { this->cur_power = cur_power; }
void Player::set_poison(int poison) { this->poison = poison; }
void Player::set_all_map(Map* map) { this->map = map; }
//getter
int Player::get_max_thirst() { return max_thirst; }
int Player::get_cur_thirst() { return cur_thirst; }
int Player::get_max_hunger() { return max_hunger; }
int Player::get_cur_hunger() { return cur_hunger; }
int Player::get_money() { return money; }
int Player::get_max_power() { return max_power; }
int Player::get_cur_power(){ return cur_power; }
int Player::get_poison() { return poison; }
string Player::get_profession() { return profession; }
Room* Player::get_current_room() { return current_room; }
Room* Player::get_previous_room() { return previous_room; }
vector<Item*> Player::get_inventory() { return inventory; }
Map* Player::get_map() { return map; }


int Player::show_bag_fight() {
	int count = 1;
	cout << "Item:" << endl;
	if (inventory.size() == 0) {
		cout << "No Item." << endl;
	}
	else {
		for (int i = 0; i < inventory.size(); i++) {
			if (inventory[i]->get_tag() == "Recorver") {
				cout << count++ << ". " << inventory[i]->get_name() << endl;
			}
		}
	}
	return count - 1;
}

void Player::use_item(int pos) {
	//�Ĥ���
	if (inventory[pos]->get_name() == "HP�^�_�Ĥ�") {
		set_cur_hp(get_cur_hp() + inventory[pos]->get_value());
		cout << get_name() << " �ϥ� " << inventory[pos]->get_name() << " �^�_ " << inventory[pos]->get_value() << "�I HP" << endl;
		inventory.erase(inventory.begin() + pos);
	}
	else if (inventory[pos]->get_name() == "MP�^�_�Ĥ�") {
		if (get_cur_mp() + inventory[pos]->get_value() > get_max_mp()) {
			set_cur_mp(get_max_mp());
		}
		else {
			set_cur_mp(get_cur_mp() + inventory[pos]->get_value());
		}
		cout << get_name() << " �ϥ� " << inventory[pos]->get_name() << " �^�_ " << inventory[pos]->get_value() << "�I MP" << endl;
		inventory.erase(inventory.begin() + pos);
	}
	//�Ѭr��
	else if (inventory[pos]->get_name() == "����" || inventory[pos]->get_name() == "�Ѭr��") {
		poison = 0;
		cout << " �ϥ� " << inventory[pos]->get_name() << endl;
		cout << "���\�Ѭr" << endl;
		inventory.erase(inventory.begin() + pos);
	}
	//�^�_ thirst
	else if (inventory[pos]->get_name() == "��") {
		cur_thirst += inventory[pos]->get_value();
		if (cur_thirst > max_thirst) { cur_thirst = max_thirst; }
		inventory.erase(inventory.begin() + pos);
	}
	else if (inventory[pos]->get_name() == "�P�H�x") {
		cur_thirst += inventory[pos]->get_value();
		cur_hunger += inventory[pos]->get_value();
		inventory.erase(inventory.begin() + pos);
	}
	//�^�_ hunger
	else if (inventory[pos]->get_tag() == "Food") {
		cur_hunger += inventory[pos]->get_value();
		if (cur_hunger > max_hunger) { cur_hunger = max_hunger; }
		inventory.erase(inventory.begin() + pos);
	}
	//�Z����
	else if (inventory[pos]->get_tag() == "Weapon") {
		Weapon* temp = dynamic_cast<Weapon*>(inventory[pos]);
		if (temp->get_equipment() == 1) {
			temp->set_equipment(0);
			increase_status(-1*temp->get_health(), -1*temp->get_attack(), -1*temp->get_defense());
			cout << "��U�˳�" << endl;
		}
		else {
			temp->set_equipment(1);
			increase_status(temp->get_health(), temp->get_attack(), temp->get_defense());
			cout << "��W�˳�" << endl;
		}
	}
	//�קK�W�L�ƭȤW��
	if (get_cur_hp() > get_max_hp()) { set_cur_hp(get_max_hp()); }
	if (get_cur_thirst() > get_max_thirst()) { set_cur_thirst(get_max_thirst()); }
	if (get_cur_hunger() > get_max_hunger()) { set_cur_hunger(get_max_hunger()); }
}

bool Player::check_thirst() {
	if (cur_thirst == 0) {
		cout << "���b�f��" << endl;
		set_cur_hp(get_cur_hp() - 1);
		return check_die();
	}
	else {
		if (current_room->get_name() == "Desert") {
			cur_thirst -= 2;
			cout << "Thirst(�f����) ��� 2 �I" << endl;
			if (cur_thirst < 0) { cur_thirst = 0; }
		}
		else {
			cur_thirst--;
			cout << "Thirst(�f����) ��� 1 �I" << endl;
		}
		return 1;
	}
}

bool Player::check_hunger() {
	if (cur_hunger == 0) {
		cout << "���b���j" << endl;
		set_cur_hp(get_cur_hp() - 1);
		return check_die();
	}
	else {
		if (current_room->get_name() == "Forest") {
			cur_hunger -= 2;
			cout << "Hunger(���j��) ��� 2 �I" << endl;
		}
		else {
			cur_hunger--;
			cout << "Hunger(���j��) ��� 1 �I" << endl;
		}
		if (cur_hunger < 0) { cur_hunger = 0; }
		return 1;
	}
}


bool Player::check_power() {
	if (cur_power == 0) {
		cout << "�P��h��" << endl;
		set_cur_hp(get_cur_hp() - 1);
		return check_die();
	}
	else {
		if (current_room->get_name() == "Swamp") {
			set_cur_power(get_cur_power() - 2);
			cout << "Power(���O��) ��� 2 �I" << endl;
		}
		else {
			set_cur_power(get_cur_power() - 1);
			cout << "Power(���O��) ��� 1 �I" << endl;
		}
	}
	if (get_cur_power() < 0) {
		set_cur_power(0);
	}
	return 1;
}

bool Player::thrist_hunger_system() {
	bool flag1 = check_hunger();
	bool flag2 = check_thirst();
	bool flag3 = check_power();
	return (flag1 || flag2 || flag3);
}

bool Player::poison_system() {
	switch (poison)
	{
	case 0:  //no poison
		break;
	case 1:  
		set_cur_hp(get_cur_hp() - get_max_hp() /10);  // ��1/10 ���̤j��q
		cout << "���r�l�� " << get_max_hp() / 10 <<"�I HP" << endl;
		return check_die();
		break;
	case 2:
		set_cur_hp(get_cur_hp() - get_max_hp() / 5);  // �� 1/5 ���̤j��q
		cout << "���r�l�� " << get_max_hp() / 5 << "�I HP" << endl;
		return check_die();
		break;
	default:
		cout << "poison_system error. poison:" << poison << endl;
		exit(1);
		break;
	}
	return 1;
}

void Player::take_break() {
	check_hunger();
	check_thirst();
	poison_system();
	if (cur_power < max_power / 2) {
		cur_power += 2;
		cout << "�^�_ 2 �I���O" << endl;
	}
	else {
		cur_power += 1;
		cout << "�^�_ 1 �I���O" << endl;
	}
	if (cur_power > max_power) {
		cur_power = max_power;
	}
}

void Player::add_money(int n) {
	money += n;
	cout << get_name() << " ��o " << n << " �� " << endl;
}


