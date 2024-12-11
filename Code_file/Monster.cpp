#include"Monster.h"

#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;

Monster::Monster() { set_tag("Monster"); }

Monster::Monster(string name, int hp, int atk, int def):GameCharacter(name,hp,atk,def) {
	set_tag("Monster");
}

bool Monster::trigger_event(Object* object) {
	fighting_system(dynamic_cast<Player*>(object));
	if (get_cur_hp() <= 0) {
		//Monster die
		return 1;
	}
	else {
		//player die
		return 0;
	}
}

//
void Monster::fighting_system(Player* player) {
	//variablle setting 
	int round = 1;
	int choice,choice1;
	int count;
	int rand_number;
	srand(time(NULL));
	//�k�sCD�ɶ�
	for (int i = 0; i < player->get_skills().size(); i++) {
		player->get_skills()[i]->set_cur_CD(0);
	}
	//�԰��}�l
	cout << "�i�J�԰�" << endl;
	while (1) {
		//��ܾ԰���¦��T(Player status and Monster status)
		player->show_status();
		show_status();
		cout << "Round " << round << " :" << endl;
		//Player choose action
		choice = 0;
		while (choice <= 0 || choice > 3) {
			cout << "1. ����" << endl;
			cout << "2. �ϥΧޯ�" << endl;
			cout << "3. �ϥιD��" << endl;
			cout << "�п�ܳo�^�X���ʧ@: ";
			cin >> choice;
			switch (choice) {
			case 1:  //����
				cout << player->get_name() << " �o�ʧ���" << endl;
				if (player->get_cur_power() < player->get_max_power() / 2) {
					cause_damage(player->get_atk() * 2 / 3);  // ���O�Ȥ֩� 1/2 �����O�|�U�� 1/3
				}
				else {
					cause_damage(player->get_atk());   //���O�ȥ��` 
				}
				break;
			case 2:  //�ϥΧޯ�
				player->show_skill();
				while (1) {
					//�����O�_����z���A
					if (player->get_cur_thirst() <= 3) { cout << "��z���A���A�L�k�ϥΧޯ�" << endl;  choice = 0; break; }
					//���a��J
					cout << "�п�ܷQ�ϥΪ��ޯ�(��J-1��^): ";
					cin >> choice1;
					//�B�z��J-1���}���\��
					if (choice1 == -1) {
						choice = 0;
						break;
					}
					//�˴����a��J�����ļƭ�
					else if (choice1 < 1 || choice1 > player->get_skills().size()) {
						cout << "��J���~�A�Э��s��J" << endl;
					}
					//CD �ɶ�����a�ϥΧޯ�
					else if (player->get_skills()[choice1 - 1]->get_cur_CD() != 0) {
						cout << player->get_skills()[choice1 - 1]->get_name() << " :�@�ޯ�CD���A�L�k�ϥ�" << endl << endl;
					}
					//�˴�MP�R��
					else if (player->get_cur_mp() < player->get_skills()[choice1 - 1]->get_cost()) {
						cout << "MP�����A�L�k�ϥΧޯ�" << endl;
					}
					else {
						if (player->get_cur_power() < player->get_max_power() / 2) {
							cause_damage(player->use_skill(choice1 - 1) * 2 / 3);  // ���O�Ȥ֩� 1/2 �����O�|�U�� 1/3
						}
						else {
							cause_damage(player->use_skill(choice1 - 1));   //���O�ȥ��` 
						}
						break;
					}
				}
				break;
			case 3:  //�ϥιD�� 
				count = player->show_bag_fight();
				while (1) {
					cout << "�п�ܷQ�ϥΪ��D��(��J-1��^): ";
					cin >> choice1;
					if (choice1 == -1) {
						choice = 0;
						break;
					}
					else {
						if (choice1 < 1 || choice1 > count) {
							cout << "��J���~�A�Э��s��J" << endl;
						}
						else {
							for (int i = 0; i < player->get_inventory().size(); i++) {
								if (player->get_inventory()[i]->get_tag() == "Recorver") {
									choice1--;
								}
								if (choice1 == 0) {
									player->use_item(i);
								}
							}
							break;
						}
					}
				}
				break;
			default:
				cout << "��J���~�A�Э��s��J�C" << endl;
			}
		}
		//check monster die
		if (!check_die()) {
			cout << "Monster die." << endl;
			break;
		}
		//�e����z
		cout << endl << endl;
		//�C�L�{�ק���
		if (player->get_profession() == "�C�L" && rand()%3 == 0) {
			cout << "���\�{�ק���" << endl;
			round++;
			continue;
		}
		//Monster attack
		cout << get_name() << "�o�ʧ���" << endl;
		player->cause_damage(get_atk());
		//�]�w�j�襤�r
		if (get_name() == "�j��") {
			player->set_poison(2);
			cout << "����j������A���⤤�r" << endl;
		}
		//check  player die
		if (!player->check_die()) {
			cout << "Yor die." << endl;
			break;
		}
		//MP �^�_
		int recorver_value;
		if (player->get_cur_hunger() < player->get_max_hunger() / 2) {
			recorver_value = player->get_max_mp() / 10;
			cout << "���j�� ";
		}
		else {
			recorver_value = player->get_max_mp() / 5;
		}

		//�^�X����
		cout << "�^�X���� :�@" << endl;
		round++;
		//�˴�HP�W�[��O�_�W�L�̤j��
		if ((player->get_cur_mp() + recorver_value) >= player->get_max_mp()) {
			cout << "�۵M�^�_ " << player->get_max_mp() - player->get_cur_mp() << "�I MP" << endl;
			player->set_cur_mp(player->get_max_mp());
		}
		else {
			cout << "�۵M�^�_ " << recorver_value << "�I MP" << endl;
			player->set_cur_mp(player->get_cur_mp() + recorver_value);
		}
		//CD �ɶ����
		for (int i = 0; i < player->get_skills().size(); i++) {
			if (player->get_skills()[i]->get_cur_CD() != 0) {
				player->get_skills()[i]->CD_decrease(1);
			}
		}
		//�e����z
		cout << endl;
		system("pause");
		system("cls");
		cout << endl;
	}
	cout << "�԰�����" << endl;
	//���a��o����
	int random_number = rand() % 30 + 10;
	player->add_money(random_number);
	//���޳]�w(���˳�����o�ަ�)
	Food* temp;
	if (get_name() == "����") {
		temp = new Food("�ަ�", 4);
		player->add_item(temp);
	}
	//�e����z
	cout << endl << endl;
	system("pause");
	system("cls");
}

void Monster::show_status() {
	cout << "--------------------------" << endl;
	cout << get_name() << endl;
	cout << "HP: " << get_cur_hp() << "/" << get_max_hp() << endl;
	cout << "ATK: " << get_atk() << endl;
	cout << "DEF: " << get_def() << endl;
	cout << "--------------------------" << endl;
	//���A

}

//Boss function

Boss::Boss():Monster("boss", 70 , 30 , 20) {
	//need to setting
	start_script = "";
	end_script = "";
}


string Boss::get_start_script() { return start_script; }
string Boss::get_end_script() {  return end_script; }

//return 1 : player win  0 : monster win
bool Boss::trigger_event(Object* player) {
	show_status();
	cout<<get_start_script()<<endl;
	fighting_system(dynamic_cast<Player*>(player));
	cout << get_end_script();
	if (check_die() == 0) {
		return 1;
	}
	return 0;
}