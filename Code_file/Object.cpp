#include<iostream>
#include<string>
#include"Object.h"

using namespace std;

Object::Object() {}
Object::Object(string name, string tag){
	this->name = name;
	this->tag = tag;
}

void Object::set_name(string new_name) {
	name = new_name;
}

void Object::set_tag(string new_tag) {
	tag = new_tag;
}

string Object::get_name() {
	return name;
}

string Object::get_tag() {
	return tag;
}