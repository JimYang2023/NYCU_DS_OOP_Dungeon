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
				cout << i + 1 << ". " << "���O: �Z�� \t" << get_commodity()[i]->get_name()  << "\t / HP: " << get_commodity()[i]->get_health() << " / ATK: " << get_commodity()[i]->get_attack() << " / DEF: " << get_commodity()[i]->get_defense() << endl;
			}
			else if (get_commodity()[i]->get_tag() == "Recorver") {
				cout << i + 1 << ". " << "���O: �Ĥ� \t" << get_commodity()[i]->get_name()  << "\t\t / ��_�ƭ�: " << get_commodity()[i]->get_value() << endl;
			}
			else if (get_commodity()[i]->get_tag() == "Food") {
				cout << i + 1 << ". " << "���O: ����\t" << get_commodity()[i]->get_name()   << "\t\t / ��_�ƭ�: " << get_commodity()[i]->get_value() << endl;
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
Businessman::Businessman(vector<Item*> goods,vector<int> cost): NPC("�ӤH","NPC",goods)  {
	this->cost = cost;
	set_script("�w��Ө�ڪ��ө�");
}
bool Businessman::trigger_event(Object* object) {
	Player* player = dynamic_cast<Player*>(object);
	//player shop
	int choice;
	while (1) {
		show_goods();
		cout << "���� : " << player->get_money() << endl;
		cout << "�п�J�Q�ʶR�����~(-1��^):";
		cin >> choice;
		if (choice == -1) { break; }
		else if (choice <= 0 || choice > get_commodity().size()) {
			cout << "��J���~�A�Э��s��J�C" << endl;
		}
		else {
			if (player->get_money() < cost[choice - 1]) {
				cout << "���������A������� " << endl << endl;
			}
			else {
				player->add_item(get_commodity()[choice - 1]);
				player->set_money(player->get_money() - cost[choice - 1]);
				cout << "������\�A��O " << cost[choice - 1] << " ���A�Ѿl " << player->get_money()<<" ���C" << endl;
				if (get_commodity()[choice - 1]->get_tag() == "Weapon") {
					erase_item(choice - 1);
					cost.erase(cost.begin() + choice - 1);
				}
				cout << "" << endl;
			}
		}
	}
	cout << "���´f�U�A�w��A�����{�C" << endl;
	return 1;
}

void Businessman::show_goods() {
	//Debug
	if (cost.size() != get_commodity().size()) { cout << "Error(show_goods) " << endl; exit(1); }
	//
	cout << get_name() << ":"<< get_script() << endl;
	//�i�ܰӫ~	
	for (int i = 0; i < get_commodity().size(); i++) {
		if (get_commodity()[i]->get_tag() == "Weapon") {
			cout << i + 1 << ". " << "���O: �Z�� \t" << get_commodity()[i]->get_name() << "\t\t / ��O: " << cost[i] << "\t / HP: " << get_commodity()[i]->get_health() << " / ATK: " << get_commodity()[i]->get_attack() << " / DEF: " << get_commodity()[i]->get_defense() << endl;
		}
		else if (get_commodity()[i]->get_tag() == "Recorver") {
			cout << i + 1 << ". " << "���O: �Ĥ� \t" << get_commodity()[i]->get_name() << "\t / ��O: " << cost[i] << "\t / ��_�ƭ�: " << get_commodity()[i]->get_value()<< endl;
		}
		else if (get_commodity()[i]->get_tag()=="Food") {
			cout << i + 1 << ". " << "���O: ����\t" << get_commodity()[i]->get_name() << "\t\t / ��O: " << cost[i] << "\t / ��_�ƭ�: " << get_commodity()[i]->get_value() << endl;
		}
		else {
			cout << i + 1 << ". " << "���O: �L\t" << get_commodity()[i]->get_name() << endl;
		}
	}
}

//setter
void Businessman::set_cost(vector<int> cost) { this->cost = cost; }
//getter
vector<int> Businessman::get_cost() { return cost; }

//Leader
Leader::Leader() : NPC() {
	set_script("�_�I�̪�!\n�{�b�ڤ�W���@�ӱ����a�c�����ȡA�o�ӥ��ȴN�浹�A�B�z�F�C���a�@���A�A�S���ڵ����v�Q�C\n�[�o�a!�_�I�̸ѩ�a�c�����ȴN�浹�A�F�C\n�o�O�ڵ��A���@�Ǹ�U�A�[�o! (-_-)\n");
	set_name("����");
	//�]�w��¦�Z��
	vector<Item*> items;
	//initial weapon setting
	Weapon* temp1;
	temp1 = new Weapon("�j�C", 0, 30, 10);
	items.push_back(temp1);
	temp1 = new Weapon("�Z�h�M", 0, 30, 10);
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
		cout << "�[�o�a!�i��!�ڬ۫H�A�ॴ�Ѱg�c������! (>_<)" << endl;
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
			cout << "�A�w��o��l�Z���A�}�l�A���a���_�I�a!" << endl;
			break;
		}
		list_commodity();
		cout << "�п�ܪ�l�Z��(�u���ܤ@��)" << endl;
		cin >> choice;
		if (choice<=0 || choice>get_commodity().size()) {
			cout << "��J���~�A�Э��s��J�C" << endl;
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
	set_name("�v��");
	set_script("");  //�]�w��l�x��
	this->skills = skills;
	this->learn_skill = 0;
}

bool Teacher::trigger_event(Object* object) {
	//�ഫ object �� gamecharacter
	GameCharacter* player = dynamic_cast<GameCharacter*>(object);
	
	//��X�򥻸�T
	cout << get_name() << ": " << endl << get_script() << endl;
	
	//�������a�O�_�ǲ߹L Skill
	if (learn_skill == 1) {
		cout << "�A�w�g�ǲ߹L�ޯ�C" << endl;
		return 0; 
	}
	//��X�i�H�ǲߪ��ۦ�
	cout << "�ۦ��W�� / ����MP / �ˮ` / CD " << endl;
	for(int i=0;i<skills.size();i++){
		cout << i + 1 << ". " << skills[i]->get_name() << " / " << skills[i]->get_cost() << " / " << skills[i]->get_damage() << " / " << skills[i]->get_CD() << endl;
	}

	//���a��ܾǲߧޯ�
	int choice;
	while (1) {
		cout << "�п�J�Q�ǲߪ��ۦ�(��J-1��^): ";
		cin >> choice;
		if (choice == -1) { break; }
		else if (choice <= 0 || choice > skills.size()) {
			cout << "��J���~�A�Э��s��J�C" << endl;
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