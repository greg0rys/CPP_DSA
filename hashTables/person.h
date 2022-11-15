#pragma once
#include <iostream>
#include <string>

using namespace std;

class person{
	public: 
		person();
		person(const person&);
		~person();

		void setName(string name);
		void setAge(int age);
		void setSchool(string school);
		 string& getName() const;
		 void printSelf();

	private:
		void destroy();
		string * name;
		string * school;
		int age;
};
