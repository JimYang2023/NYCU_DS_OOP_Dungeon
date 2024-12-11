#ifndef Object_h
#define Object_h

#include<iostream>
#include<string>
using namespace std;

class Object {
public:
	virtual bool trigger_event(Object*) = 0;
	Object();
	Object(string , string);
	//setter
	void set_name(string );
	void set_tag(string );
	//getter
	string get_name();
	string get_tag();
private:
	string name;
	string tag;
};

#endif