#include "person.h"

person::person()
{
	name = nullptr;
	school = nullptr;
	age = 0;
};


person::~person()
{
	destroy();
}


void person::destroy()
{
	if(name)
		delete name;
	if(school)
		delete school;

	name = nullptr;
	school = nullptr;
	age = 0;
}

void person::setName(string name)
{
	if(this->name)
		delete this-> name;
	this->name = new string(name);
}


void person::setAge(int age)
{
	this->age = age;
}


void person::setSchool(string school)
{
	if(this->school)
		delete this-> school;
	this->school = new string(school);

}

string& person::getName() const
{
	return *this->name;
}


void person::printSelf()
{
	string tempName = "";

	if(!name)
		setName(tempName);
	if(!school)
		setSchool(tempName);

	cout << name << " " << school << " " << age << endl;
}
