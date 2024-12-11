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
	max_thirst = 10;  //數值調整
	max_hunger = 10;  //數值調整
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
		cout << "是否撿起物品:" << endl;
		cout << "1: 是" << endl;
		cout << "2: 否" << endl;
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
			cout << " 輸入錯誤請重新輸入 " << endl;
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
	cout << "角色名稱: " << get_name() << endl;
	cout << "職業: " << profession <<endl;
	cout << "HP: " << get_cur_hp() << "/" << get_max_hp() << endl;
	cout << "ATK: " << get_atk() << endl;
	cout << "DEF: " << get_def() << endl;
	cout << "MP: " << get_cur_mp() << "/" << get_max_mp() << endl;
	cout << "Thirst(口渴值): " << cur_thirst << "/" << max_thirst << endl;
	cout << "Hunger(飢餓值): " << cur_hunger << "/" << max_hunger << endl;
	cout << "Power(活力值): " << cur_power << "/" << max_power << endl;
	cout << "Poison(中毒狀態): " << poison;
	switch (poison) {
	case 0:
		cout << " (未中毒)" << endl;
		break;
	case 1:
		cout << " (植物中毒)" << endl;
		break;
	case 2:
		cout << " (怪物中毒)" << endl;
		break;
	}
	cout << "Money: " << money << endl;
	cout << endl;

	//bag
	show_bag();
	
	//status
	int count = 1;
	cout << endl << "角色狀態:" << endl;
	if(cur_hunger<max_hunger/2){
		cout << count++ << ". 飢餓(自然回復MP減半)" << endl;
	}
	if (cur_thirst <= 3) {
		cout << count++ << ". 虛弱(無法使用技能)" << endl;
	}
	if (poison != 0) {
		cout << count++ << ". 中毒(隨著移動損血)" << endl;
	}
	if (cur_power < max_power / 2) {
		cout << count++ << ". 疲勞(攻擊力減半)" << endl;
	}
	if (cur_power == 0) {
		cout << count++ << ". 無力(無法移動)" << endl;
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
					cout << i + 1 << ". " << "武器 " << inventory[i]->get_name() << "\t\t已裝備" << "\t/ HP : "<<inventory[i]->get_health()<< "\t/ ATK : "<< inventory[i]->get_attack() << "\t/ Def : "<< inventory[i]->get_defense() << endl;
				}
				else {
					cout << i + 1 << ". " << "武器 " << inventory[i]->get_name() << "\t\t未裝備" << "\t/ HP : " << inventory[i]->get_health() << "\t/ ATK : " << inventory[i]->get_attack() << "\t/ Def : " << inventory[i]->get_defense() << endl;
				}
			}
			else if(inventory[i]->get_tag()=="Recorver") {
				cout << i + 1 << ". " << "藥水 " << inventory[i]->get_name() << "\t回復數值: "<< inventory[i]->get_value() << endl;
			}
			else if (inventory[i]->get_tag() == "Food") {
				cout << i + 1 << ". " << "食物 " << inventory[i]->get_name() << "\t\t回復數值: " << inventory[i]->get_value() << endl;
			}
		}
	}
}

void Player::show_map() {
	cout << "現在地區 : " << current_room->get_name() << endl;
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
	//藥水類
	if (inventory[pos]->get_name() == "HP回復藥水") {
		set_cur_hp(get_cur_hp() + inventory[pos]->get_value());
		cout << get_name() << " 使用 " << inventory[pos]->get_name() << " 回復 " << inventory[pos]->get_value() << "點 HP" << endl;
		inventory.erase(inventory.begin() + pos);
	}
	else if (inventory[pos]->get_name() == "MP回復藥水") {
		if (get_cur_mp() + inventory[pos]->get_value() > get_max_mp()) {
			set_cur_mp(get_max_mp());
		}
		else {
			set_cur_mp(get_cur_mp() + inventory[pos]->get_value());
		}
		cout << get_name() << " 使用 " << inventory[pos]->get_name() << " 回復 " << inventory[pos]->get_value() << "點 MP" << endl;
		inventory.erase(inventory.begin() + pos);
	}
	//解毒類
	else if (inventory[pos]->get_name() == "牛奶" || inventory[pos]->get_name() == "解毒草") {
		poison = 0;
		cout << " 使用 " << inventory[pos]->get_name() << endl;
		cout << "成功解毒" << endl;
		inventory.erase(inventory.begin() + pos);
	}
	//回復 thirst
	else if (inventory[pos]->get_name() == "水") {
		cur_thirst += inventory[pos]->get_value();
		if (cur_thirst > max_thirst) { cur_thirst = max_thirst; }
		inventory.erase(inventory.begin() + pos);
	}
	else if (inventory[pos]->get_name() == "仙人掌") {
		cur_thirst += inventory[pos]->get_value();
		cur_hunger += inventory[pos]->get_value();
		inventory.erase(inventory.begin() + pos);
	}
	//回復 hunger
	else if (inventory[pos]->get_tag() == "Food") {
		cur_hunger += inventory[pos]->get_value();
		if (cur_hunger > max_hunger) { cur_hunger = max_hunger; }
		inventory.erase(inventory.begin() + pos);
	}
	//武器類
	else if (inventory[pos]->get_tag() == "Weapon") {
		Weapon* temp = dynamic_cast<Weapon*>(inventory[pos]);
		if (temp->get_equipment() == 1) {
			temp->set_equipment(0);
			increase_status(-1*temp->get_health(), -1*temp->get_attack(), -1*temp->get_defense());
			cout << "脫下裝備" << endl;
		}
		else {
			temp->set_equipment(1);
			increase_status(temp->get_health(), temp->get_attack(), temp->get_defense());
			cout << "穿上裝備" << endl;
		}
	}
	//避免超過數值上限
	if (get_cur_hp() > get_max_hp()) { set_cur_hp(get_max_hp()); }
	if (get_cur_thirst() > get_max_thirst()) { set_cur_thirst(get_max_thirst()); }
	if (get_cur_hunger() > get_max_hunger()) { set_cur_hunger(get_max_hunger()); }
}

bool Player::check_thirst() {
	if (cur_thirst == 0) {
		cout << "正在口渴" << endl;
		set_cur_hp(get_cur_hp() - 1);
		return check_die();
	}
	else {
		if (current_room->get_name() == "Desert") {
			cur_thirst -= 2;
			cout << "Thirst(口渴值) 減少 2 點" << endl;
			if (cur_thirst < 0) { cur_thirst = 0; }
		}
		else {
			cur_thirst--;
			cout << "Thirst(口渴值) 減少 1 點" << endl;
		}
		return 1;
	}
}

bool Player::check_hunger() {
	if (cur_hunger == 0) {
		cout << "正在飢餓" << endl;
		set_cur_hp(get_cur_hp() - 1);
		return check_die();
	}
	else {
		if (current_room->get_name() == "Forest") {
			cur_hunger -= 2;
			cout << "Hunger(飢餓值) 減少 2 點" << endl;
		}
		else {
			cur_hunger--;
			cout << "Hunger(飢餓值) 減少 1 點" << endl;
		}
		if (cur_hunger < 0) { cur_hunger = 0; }
		return 1;
	}
}


bool Player::check_power() {
	if (cur_power == 0) {
		cout << "感到疲勞" << endl;
		set_cur_hp(get_cur_hp() - 1);
		return check_die();
	}
	else {
		if (current_room->get_name() == "Swamp") {
			set_cur_power(get_cur_power() - 2);
			cout << "Power(活力值) 減少 2 點" << endl;
		}
		else {
			set_cur_power(get_cur_power() - 1);
			cout << "Power(活力值) 減少 1 點" << endl;
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
		set_cur_hp(get_cur_hp() - get_max_hp() /10);  // 扣1/10 的最大血量
		cout << "中毒損失 " << get_max_hp() / 10 <<"點 HP" << endl;
		return check_die();
		break;
	case 2:
		set_cur_hp(get_cur_hp() - get_max_hp() / 5);  // 扣 1/5 的最大血量
		cout << "中毒損失 " << get_max_hp() / 5 << "點 HP" << endl;
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
		cout << "回復 2 點活力" << endl;
	}
	else {
		cur_power += 1;
		cout << "回復 1 點活力" << endl;
	}
	if (cur_power > max_power) {
		cur_power = max_power;
	}
}

void Player::add_money(int n) {
	money += n;
	cout << get_name() << " 獲得 " << n << " 元 " << endl;
}


