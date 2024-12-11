#include"Map.h"

Pos::Pos() {
	this->x = -1;
	this->y = -1;
}

Pos::Pos(int x, int y) {
	this->x = x;
	this->y = y;
}

//operator overloading
Pos operator + (Pos a, Pos b) {
	Pos* c= new Pos(a.x + b.x, a.y + b.y);
	return *c;
}

//constructor
Map::Map() {
	this->map_size_x = 0;
	this->map_size_y = 0;
	initial_map();
}

Map::Map(int x_size, int y_size) {
	map_size_x = x_size;
	map_size_y = y_size;
	initial_map();
}

//initial map
void Map::initial_map() {
	//map initial setting
	vector<Room*> temp_arr;
	for (int i = 0; i < map_size_y; i++) {
		for (int j = 0; j < map_size_x; j++) {
			temp_arr.push_back(NULL);
		}
		map.push_back(temp_arr);
		temp_arr.clear();
	}
}

//getter
int Map::get_size_x() { return this->map_size_x; }
int Map::get_size_y() { return this->map_size_y; }
vector<vector<Room*>> Map::get_map() { return this->map; }
//setter
void Map::set_size_x(int x) { this->map_size_x = x; }
void Map::set_size_y(int y) { this->map_size_y = y; }
void Map::set_size(int x, int y) {
	this->map_size_x = x;
	this->map_size_y = y;
}

void Map::show_map() {
	cout << "--------------------------" << endl;
	//偵測第一行上方道路
	cout << "  ";
	for (int i = 0; i < map[0].size(); i++) {
		if (map[0][i] != NULL && map[0][i]->get_up_room()!=NULL) {
			cout << "|   ";
		}
		else {
			cout << "    ";
		}
	}
	cout << endl;
	//show other map
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] != NULL) {
				//偵測左房間
				if (j > 0 && (map[i][j - 1] == NULL || map[i][j - 1]->get_right_room() == NULL)) {
					//偵測其他列
					if (map[i][j]->get_left_room() != NULL) {
						cout << "- ";
					}
					else {
						if (map[i][j - 1] == NULL) {
							cout << "  ";
						}
					}
				}
				else if (j == 0) {
					//偵測第一列
					if (map[i][j]->get_left_room() != NULL) {
						cout << "- ";
					}
					else {
						cout << "  ";
					}
				}
				//檢查房間種類
				if (map[i][j]->get_go_through() == 2) {
					cout << "C ";  //current room
				}
				else if (map[i][j]->get_name() == "Start_room") {
					cout << "S ";   //start room
				}
				else if (map[i][j]->get_name() == "Final_room") {
					cout << "E ";  //final room
				}
				else if (map[i][j]->get_objects().size()!=0 && map[i][j]->get_objects()[0]->get_tag() == "NPC") {
					cout << "N ";  //NPC room (expect start room)
				}
				else if (map[i][j]->get_objects().size() != 0 && map[i][j]->get_objects()[0]->get_tag() == "Monster") {
					cout << "M ";  //monster room (expect final room)
				}
				else if (map[i][j]->get_go_through() == 1) {
					cout << "1 ";
				}
				else {
					cout << "  ";
				}
				//偵測右房間
				if (map[i][j]->get_right_room() != NULL) {
					cout << "- ";
				}
				else {
					cout << "  ";
				}
			}
			else {
				//map 上房間為 NULL
				if (j == 0) { cout << "  "; }
				cout << "  ";
				if (j == map[i].size() - 1 || map[i][j+1] == NULL) {
					cout << "  ";
				}
			}
		}
		cout << endl;
		//偵測上下房間
		cout << "  ";
		for (int j = 0; j < map[i].size(); j++) {
			//顯示其他行
			if (i != map.size() - 1) {
				if (map[i][j] != NULL || map[i + 1][j] != NULL) {
					if (map[i][j] && map[i][j]->get_down_room() != NULL) {
						cout << "|   ";
					}
					else if (map[i + 1][j] && map[i + 1][j]->get_up_room() != NULL) {
						cout << "|   ";
					}
					else {
						cout << "    ";
					}
				}
				else {
					cout << "    ";
				}
			}
			//顯示最後一行
			else {
				if (map[i][j] != NULL) {  
					if (map[i][j] && map[i][j]->get_down_room() != NULL) {
						cout << "|   ";
					}
					else {
						cout << "    ";
					}
				}
				else {
					cout << "    ";
				}
			}
		}
		cout << endl;
	}
	cout << "C : Current Room" << endl;
	cout << "S : Start Room" << endl;
	cout << "E : End Room" << endl;
	cout << "M : Monster Room" << endl;
	cout << "N : NPC Room" << endl;
	cout << "--------------------------" << endl;
}

Pos Map::search(Room* target) {
	Pos temp;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (target == map[i][j]) {
				temp = Pos(j, i);
			}
		}
	}
	//Debug
	if (temp.x == -1) { cout << "Not find room in map.\n"; exit(1); }
	return temp;
}


void Map::set_map(Room* room, Pos pos) {
	if (pos.x < 0) {
		increase_map_size(-pos.x, 'L');
		this->map_size_x++;
		pos.x++;
	}
	else if (pos.x >= this->map_size_x) {
		increase_map_size(pos.x - this->map_size_x + 1, 'R');
		map_size_x++;
	}
	if (pos.y < 0) {
		increase_map_size(-pos.y, 'U');
		(this->map_size_y)++;
		pos.y++;
	}
	else if (pos.y >= map_size_y) {
		increase_map_size(pos.y - map_size_y + 1, 'D');
		this->map_size_y++;
	}
	//cout << "set_map pos: " << pos.x << " " << pos.y << endl;
	if (this->map[pos.y][pos.x] == NULL) {
		this->map[pos.y][pos.x] = room;
	}
	//cout << "Error" << endl;
}

void Map::update_map(Room* current_room,Room* previous_room) {
	Pos relation,final_pos;
	if (previous_room != NULL) {
		switch (previous_room->find_relation(current_room)) {
		case 'U':
			relation = Pos(0, -1);
			//cout << "U" << endl;
			break;
		case 'D':
			relation = Pos(0, 1);
			//cout << "D" << endl;
			break;
		case 'R':
			relation = Pos(1, 0);
			//cout << "R" << endl;
			break;
		case 'L':
			relation = Pos(-1, 0);
			//cout << "L" << endl;
			break;
		default:
			cout << "Error Update map." << endl;
		}
		final_pos = search(previous_room) + relation;
		set_map(current_room, final_pos  );
	}
}

void Map::increase_map_size(int size, char tpye) {
	//cout << "Increase map size start." << endl;
	vector<Room*>temp;
	switch (tpye) {
	case 'U':
		for (int i = 0; i < this->map[0].size(); i++) {
			temp.push_back(NULL);
		}
		for (int i = 0; i < size; i++) {
			map.insert(map.begin(), temp);
		}
		break;
	case 'D':
		for (int i = 0; i < map[0].size(); i++) {
			temp.push_back(NULL);
		}
		for (int i = 0; i < size; i++) {
			map.push_back(temp);
		}
		break;
	case 'R':
		for (int i = 0; i < map.size(); i++) {
			for (int j = 0; j < size; j++) {
				map[i].push_back(NULL);
			}
		}
		break;
	case 'L':
		for (int i = 0; i < map.size(); i++) {
			for (int j = 0; j < size; j++) {
				map[i].insert(map[i].begin(),NULL);
			}
		}
		break;
	}
	//cout << "Increase map size end." << endl;
}

vector<int> Map::check_near_room(Pos pos) {
	vector<int> restriction;
	//x方向
	if (pos.x == 0) {
		if (map[pos.y][pos.x + 1]!=NULL) {
			restriction.push_back(2);
		}
	}
	else if(pos.x == map[0].size()-1){
		if (map[pos.y][pos.x - 1]) {
			restriction.push_back(3);
		}
	}
	else {
		if (map[pos.y][pos.x + 1] != NULL) {
			restriction.push_back(2);
		}
		if (map[pos.y][pos.x - 1 ]) {
			restriction.push_back(3);
		}
	}
	//y方向
	if (pos.y == 0) {
		if (map[pos.y + 1 ][pos.x] != NULL) {
			restriction.push_back(1);
		}
	}
	else if (pos.y == map.size()-1) {
		if (map[pos.y - 1][pos.x]) {
			restriction.push_back(0);
		}
	}
	else {
		if (map[pos.y + 1][pos.x] != NULL) {
			restriction.push_back(1);
		}
		if (map[pos.y - 1][pos.x]) {
			restriction.push_back(0);
		}
	}
	return restriction;
}