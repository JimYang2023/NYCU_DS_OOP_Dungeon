#include"NPC.h"

NPC::NPC(){ set_tag("NPC"); }
NPC::NPC(string name, string script, vector<Item*>objects) :GameCharacter(name, 0, 0, 0) {
	//Todo
	this->commodity = objects;
	set_tag("NPC");
}
void NPC::list_commodity(){
	if (commodity.size() != 0) {
		for (int i = 0; i < commodity.size(); i++) {
			if (get_commodity()[i]->get_tag() == "Weapon") {
				cout << i + 1 << ". " << "類別: 武器 \t" << get_commodity()[i]->get_name()  << "\t / HP: " << get_commodity()[i]->get_health() << " / ATK: " << get_commodity()[i]->get_attack() << " / DEF: " << get_commodity()[i]->get_defense() << endl;
			}
			else if (get_commodity()[i]->get_tag() == "Recorver") {
				cout << i + 1 << ". " << "類別: 藥水 \t" << get_commodity()[i]->get_name()  << "\t\t / 恢復數值: " << get_commodity()[i]->get_value() << endl;
			}
			else if (get_commodity()[i]->get_tag() == "Food") {
				cout << i + 1 << ". " << "類別: 食物\t" << get_commodity()[i]->get_name()   << "\t\t / 恢復數值: " << get_commodity()[i]->get_value() << endl;
			}
		}
	}
	else {
		cout << "No commodity." << endl;
	}
}
bool NPC::trigger_event(Object*) {
	cout << get_name() << ":" << endl << script << endl;
	return 1;
}
//setter
void NPC::set_script(string new_script) { script = new_script; }
void NPC::set_commodity(vector<Item*> commodity) {
	this->commodity = commodity;
}
//getter
string NPC::get_script() { return script; }
vector<Item*> NPC::get_commodity() { return commodity; }
//erase item
void NPC::erase_item(int pos) {
	//debug
	if (commodity.size() == 0) {
		cout << "commodity size error(erase_item)" << endl;
		exit(1);
	}
	else if (pos >= commodity.size()) {
		cout << "pos error(erase_item)" << endl;
		exit(1);
	}
	//
	commodity.erase(commodity.begin() + pos);
}



//Business
Businessman::Businessman(){}
Businessman::Businessman(vector<Item*> goods,vector<int> cost): NPC("商人","NPC",goods)  {
	this->cost = cost;
	set_script("歡迎來到我的商店");
}
bool Businessman::trigger_event(Object* object) {
	Player* player = dynamic_cast<Player*>(object);
	//player shop
	int choice;
	while (1) {
		show_goods();
		cout << "金錢 : " << player->get_money() << endl;
		cout << "請輸入想購買的物品(-1返回):";
		cin >> choice;
		if (choice == -1) { break; }
		else if (choice <= 0 || choice > get_commodity().size()) {
			cout << "輸入錯誤，請重新輸入。" << endl;
		}
		else {
			if (player->get_money() < cost[choice - 1]) {
				cout << "金錢不足，交易失敗 " << endl << endl;
			}
			else {
				player->add_item(get_commodity()[choice - 1]);
				player->set_money(player->get_money() - cost[choice - 1]);
				cout << "交易成功，花費 " << cost[choice - 1] << " 元，剩餘 " << player->get_money()<<" 元。" << endl;
				if (get_commodity()[choice - 1]->get_tag() == "Weapon") {
					erase_item(choice - 1);
					cost.erase(cost.begin() + choice - 1);
				}
				cout << "" << endl;
			}
		}
	}
	cout << "謝謝惠顧，歡迎再次光臨。" << endl;
	return 1;
}

void Businessman::show_goods() {
	//Debug
	if (cost.size() != get_commodity().size()) { cout << "Error(show_goods) " << endl; exit(1); }
	//
	cout << get_name() << ":"<< get_script() << endl;
	//展示商品	
	for (int i = 0; i < get_commodity().size(); i++) {
		if (get_commodity()[i]->get_tag() == "Weapon") {
			cout << i + 1 << ". " << "類別: 武器 \t" << get_commodity()[i]->get_name() << "\t\t / 花費: " << cost[i] << "\t / HP: " << get_commodity()[i]->get_health() << " / ATK: " << get_commodity()[i]->get_attack() << " / DEF: " << get_commodity()[i]->get_defense() << endl;
		}
		else if (get_commodity()[i]->get_tag() == "Recorver") {
			cout << i + 1 << ". " << "類別: 藥水 \t" << get_commodity()[i]->get_name() << "\t / 花費: " << cost[i] << "\t / 恢復數值: " << get_commodity()[i]->get_value()<< endl;
		}
		else if (get_commodity()[i]->get_tag()=="Food") {
			cout << i + 1 << ". " << "類別: 食物\t" << get_commodity()[i]->get_name() << "\t\t / 花費: " << cost[i] << "\t / 恢復數值: " << get_commodity()[i]->get_value() << endl;
		}
		else {
			cout << i + 1 << ". " << "類別: 無\t" << get_commodity()[i]->get_name() << endl;
		}
	}
}

//setter
void Businessman::set_cost(vector<int> cost) { this->cost = cost; }
//getter
vector<int> Businessman::get_cost() { return cost; }

//Leader
Leader::Leader() : NPC() {
	set_script("冒險者阿!\n現在我手上有一個探索地牢的任務，這個任務就交給你處理了。順帶一提，你沒有拒絕的權利。\n加油吧!冒險者解放地牢的任務就交給你了。\n這是我給你的一些資助，加油! (-_-)\n");
	set_name("村長");
	//設定基礎武器
	vector<Item*> items;
	//initial weapon setting
	Weapon* temp1;
	temp1 = new Weapon("大劍", 0, 30, 10);
	items.push_back(temp1);
	temp1 = new Weapon("武士刀", 0, 30, 10);
	items.push_back(temp1);
	temp1 = new Weapon("Excalibur", 0, 30, 10);
	items.push_back(temp1);
	//initial recorver setting
	
	//initial food setting
	
	set_commodity(items);
	get_weapon = 0;
}

bool Leader::trigger_event(Object* object) {
	//
	if (get_weapon) {
		cout << "加油吧!勇者!我相信你能打敗迷宮之王的! (>_<)" << endl;
		return 1;
	}
	//
	Player* player = dynamic_cast<Player*>(object);
	cout << get_name() << ":" << endl;
	cout << get_script() << endl;
	
	//give money to player
	player->set_money(100);  //initial money setting

	int choice;
	while (1) {
		if (get_weapon) {
			cout << "你已獲得初始武器，開始你的地城冒險吧!" << endl;
			break;
		}
		list_commodity();
		cout << "請選擇初始武器(只能選擇一次)" << endl;
		cin >> choice;
		if (choice<=0 || choice>get_commodity().size()) {
			cout << "輸入錯誤，請重新輸入。" << endl;
		}
		else {
			player->add_item(get_commodity()[choice - 1]);
			get_weapon = 1;
		}
	}
	system("Pause");
	system("cls");
	return 1;
}

void Leader::set_get_weapon(bool get_weapon) { this->get_weapon = get_weapon; }
bool Leader::get_get_weapon() { return get_weapon; }


//Teacher
Teacher::Teacher(){}

Teacher::Teacher(vector<Skill* > skills){
	set_name("師傅");
	set_script("");  //設定初始台詞
	this->skills = skills;
	this->learn_skill = 0;
}

bool Teacher::trigger_event(Object* object) {
	//轉換 object 到 gamecharacter
	GameCharacter* player = dynamic_cast<GameCharacter*>(object);
	
	//輸出基本資訊
	cout << get_name() << ": " << endl << get_script() << endl;
	
	//偵測玩家是否學習過 Skill
	if (learn_skill == 1) {
		cout << "你已經學習過技能。" << endl;
		return 0; 
	}
	//輸出可以學習的招式
	cout << "招式名稱 / 消耗MP / 傷害 / CD " << endl;
	for(int i=0;i<skills.size();i++){
		cout << i + 1 << ". " << skills[i]->get_name() << " / " << skills[i]->get_cost() << " / " << skills[i]->get_damage() << " / " << skills[i]->get_CD() << endl;
	}

	//玩家選擇學習技能
	int choice;
	while (1) {
		cout << "請輸入想學習的招式(輸入-1返回): ";
		cin >> choice;
		if (choice == -1) { break; }
		else if (choice <= 0 || choice > skills.size()) {
			cout << "輸入錯誤，請重新輸入。" << endl;
		}
		else {
			player->learn_skill(skills[choice - 1]);
			skills.erase(skills.begin() + choice - 1);
			learn_skill = 1;
			break;
		}
	}
	return 1;
}

void Teacher::set_skills(vector<Skill*> skills) { this->skills = skills; }

vector<Skill*>& Teacher::get_skills() { return skills; }