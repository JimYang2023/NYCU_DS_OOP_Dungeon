#include"Room.h"

Room::Room() {
	go_through = 0;
	is_exit = 0;
	index = 0;
	event_happen = 0;
	up_room = NULL;
	right_room = NULL;
	left_room = NULL;
	down_room = NULL;
}

Room::Room(string name,bool is_exit, int index, vector<Object*> objects):Object(name, "Room") {
	this->is_exit = is_exit;
	this->index = index;
	this->objects = objects;
	go_through = 0;
	up_room = NULL;
	right_room = NULL;
	left_room = NULL;
	down_room = NULL;
}			
//getter
int Room::get_go_through() { return go_through; }
Room* Room::get_up_room() { return up_room; }
Room* Room::get_down_room() { return down_room; }
Room* Room::get_right_room() { return right_room; }
Room* Room::get_left_room() { return left_room; }
bool Room::get_is_exit() { return is_exit; }
int Room::get_index() { return index; }
bool Room::get_event_happen() { return event_happen; }
vector<Object*>& Room::get_objects() { return objects; }


//setter
void Room::set_go_throough(int go_through) { this->go_through = go_through; }
void Room::set_up_room(Room* up_room) { this->up_room = up_room; }
void Room::set_down_room(Room* down_room) { this->down_room = down_room; }
void Room::set_right_room(Room* right_room) { this->right_room = right_room; }
void Room::set_left_room(Room*  left_room) { this->left_room = left_room; }
void Room::set_is_exit(bool is_exit) { this->is_exit = is_exit; }
void Room::set_index(int index) { this->index = index; }
void Room::set_objects(vector<Object*> objects) { this->objects = objects; }
void Room::set_event_happen(bool event_happen) { this->event_happen = event_happen; }

//virtual function
bool Room::trigger_event(Object* player) { return 0; }

int Room::get_type() { return 0; }

//test path 找房間的通道
bool Room::test_path(int n) {
	//0:up 1:down 2:right 3:left
	switch (n) {
	case 0:
		if (up_room) { return 1; }
		else { return 0; }
		break;
	case 1:
		if (down_room) { return 1; }
		else { return 0; }
		break;
	case 2:
		if (right_room) { return 1; }
		else { return 0; }
		break;
	case 3:
		if (left_room) { return 1; }
		else { return 0; }
		break;
	default:
		return 0;
	}
}

// randomly set room
int Room::randomly_set_room(Room* new_room,Room* this_room,vector<int> restriction) {
	vector<int>nums;
	int rand_number = -1;
	bool flag;
	for (int i = 0; i < 4; i++) {
		if (!test_path(i)) {
			nums.push_back(i);
		}
	}
	if (nums.size() != 0) {
		srand(time(NULL));
		while (1) {
			if (restriction.size() == 4) {
				rand_number = -1;
				break;
			}
			flag = 1;
			rand_number = rand() % nums.size();
			for (int i = 0; i < restriction.size(); i++) {
				if (nums[rand_number] == restriction[i]) {
					flag = 0;
					break;
				}
			}
			if (flag) { break; }
		}
		if (rand_number == -1) { return 0; }
		switch(nums[rand_number]){
		case 0:
			up_room = new_room;
			new_room->set_down_room(this_room);
			break;
		case 1:
			down_room = new_room;
			new_room->set_up_room(this_room);
			break;
		case 2:
			right_room = new_room;
			new_room->set_left_room(this_room);
			break;
		case 3:
			left_room = new_room;
			new_room->set_right_room(this_room);
			break;
		}
		return 1;
	}
	else {
		//there is no NULL path.
		return 0;
	}
}

char Room::find_relation(Room* room) {
	if (up_room == room) {
		return 'U';
	}
	else if(down_room==room){
		return 'D';
	}
	else if (right_room == room) {
		return 'R';
	}
	else if (left_room == room) {
		return 'L';
	}
	else {
		return 'N';
	}
}

void Room::add_object(Object* object) {
	objects.push_back(object);
}

int Room::show_objects() {
	Item* temp;
	int count = 1;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->get_tag() == "NPC" || objects[i]->get_tag() == "Monster") { continue; }
		temp = dynamic_cast<Item*>(objects[i]);
		if (objects[i]->get_tag() == "Weapon") {
			cout << count++ << ". " << "類別: 武器 \t" << objects[i]->get_name() << "\t / HP: " << temp->get_health() << " / ATK: " << temp->get_attack() << " / DEF: " << temp->get_defense() << endl;
		}
		else if (objects[i]->get_tag() == "Recorver") {
			cout << count++ << ". " << "類別: 藥水 \t" << objects[i]->get_name() <<  "\t / 恢復數值: " << temp->get_value() << endl;
		}
		else if (objects[i]->get_tag() == "Food") {
			cout << count++ << ". " << "類別: 食物\t" << objects[i]->get_name()  << "\t / 恢復數值: " << temp->get_value() << endl;
		}
		else {
			cout << count++ << ". " << "類別: 無\t" << objects[i]->get_name() << endl;
		}
	}
	return count - 1;
}