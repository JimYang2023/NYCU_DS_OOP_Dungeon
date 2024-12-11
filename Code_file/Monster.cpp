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
	//歸零CD時間
	for (int i = 0; i < player->get_skills().size(); i++) {
		player->get_skills()[i]->set_cur_CD(0);
	}
	//戰鬥開始
	cout << "進入戰鬥" << endl;
	while (1) {
		//顯示戰鬥基礎資訊(Player status and Monster status)
		player->show_status();
		show_status();
		cout << "Round " << round << " :" << endl;
		//Player choose action
		choice = 0;
		while (choice <= 0 || choice > 3) {
			cout << "1. 攻擊" << endl;
			cout << "2. 使用技能" << endl;
			cout << "3. 使用道具" << endl;
			cout << "請選擇這回合的動作: ";
			cin >> choice;
			switch (choice) {
			case 1:  //攻擊
				cout << player->get_name() << " 發動攻擊" << endl;
				if (player->get_cur_power() < player->get_max_power() / 2) {
					cause_damage(player->get_atk() * 2 / 3);  // 活力值少於 1/2 攻擊力會下降 1/3
				}
				else {
					cause_damage(player->get_atk());   //活力值正常 
				}
				break;
			case 2:  //使用技能
				player->show_skill();
				while (1) {
					//偵測是否為虛弱狀態
					if (player->get_cur_thirst() <= 3) { cout << "虛弱狀態中，無法使用技能" << endl;  choice = 0; break; }
					//玩家輸入
					cout << "請選擇想使用的技能(輸入-1返回): ";
					cin >> choice1;
					//處理輸入-1離開的功能
					if (choice1 == -1) {
						choice = 0;
						break;
					}
					//檢測玩家輸入為有效數值
					else if (choice1 < 1 || choice1 > player->get_skills().size()) {
						cout << "輸入錯誤，請重新輸入" << endl;
					}
					//CD 時間限制玩家使用技能
					else if (player->get_skills()[choice1 - 1]->get_cur_CD() != 0) {
						cout << player->get_skills()[choice1 - 1]->get_name() << " :　技能CD中，無法使用" << endl << endl;
					}
					//檢測MP充足
					else if (player->get_cur_mp() < player->get_skills()[choice1 - 1]->get_cost()) {
						cout << "MP不足，無法使用技能" << endl;
					}
					else {
						if (player->get_cur_power() < player->get_max_power() / 2) {
							cause_damage(player->use_skill(choice1 - 1) * 2 / 3);  // 活力值少於 1/2 攻擊力會下降 1/3
						}
						else {
							cause_damage(player->use_skill(choice1 - 1));   //活力值正常 
						}
						break;
					}
				}
				break;
			case 3:  //使用道具 
				count = player->show_bag_fight();
				while (1) {
					cout << "請選擇想使用的道具(輸入-1返回): ";
					cin >> choice1;
					if (choice1 == -1) {
						choice = 0;
						break;
					}
					else {
						if (choice1 < 1 || choice1 > count) {
							cout << "輸入錯誤，請重新輸入" << endl;
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
				cout << "輸入錯誤，請重新輸入。" << endl;
			}
		}
		//check monster die
		if (!check_die()) {
			cout << "Monster die." << endl;
			break;
		}
		//畫面整理
		cout << endl << endl;
		//遊俠閃避攻擊
		if (player->get_profession() == "遊俠" && rand()%3 == 0) {
			cout << "成功閃避攻擊" << endl;
			round++;
			continue;
		}
		//Monster attack
		cout << get_name() << "發動攻擊" << endl;
		player->cause_damage(get_atk());
		//設定蜘蛛中毒
		if (get_name() == "蜘蛛") {
			player->set_poison(2);
			cout << "受到蜘蛛攻擊，角色中毒" << endl;
		}
		//check  player die
		if (!player->check_die()) {
			cout << "Yor die." << endl;
			break;
		}
		//MP 回復
		int recorver_value;
		if (player->get_cur_hunger() < player->get_max_hunger() / 2) {
			recorver_value = player->get_max_mp() / 10;
			cout << "飢餓中 ";
		}
		else {
			recorver_value = player->get_max_mp() / 5;
		}

		//回合結束
		cout << "回合結束 :　" << endl;
		round++;
		//檢測HP增加後是否超過最大值
		if ((player->get_cur_mp() + recorver_value) >= player->get_max_mp()) {
			cout << "自然回復 " << player->get_max_mp() - player->get_cur_mp() << "點 MP" << endl;
			player->set_cur_mp(player->get_max_mp());
		}
		else {
			cout << "自然回復 " << recorver_value << "點 MP" << endl;
			player->set_cur_mp(player->get_cur_mp() + recorver_value);
		}
		//CD 時間減少
		for (int i = 0; i < player->get_skills().size(); i++) {
			if (player->get_skills()[i]->get_cur_CD() != 0) {
				player->get_skills()[i]->CD_decrease(1);
			}
		}
		//畫面整理
		cout << endl;
		system("pause");
		system("cls");
		cout << endl;
	}
	cout << "戰鬥結束" << endl;
	//玩家獲得金錢
	int random_number = rand() % 30 + 10;
	player->add_money(random_number);
	//野豬設定(打倒野豬獲得豬肉)
	Food* temp;
	if (get_name() == "野豬") {
		temp = new Food("豬肉", 4);
		player->add_item(temp);
	}
	//畫面整理
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
	//狀態

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