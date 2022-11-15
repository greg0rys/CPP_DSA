#pragma once
#include <iostream>
#include <string>
#include "person.h"

using namespace std;

class table{
	public:
		table();
		table(const table &);
		~table();

		bool add(const person &);
		bool print();
		const table& operator=(const table&);

	private:
		struct node{
			person * data;
			node * next;
			
			node(){
				this->data = nullptr;
				this->next = nullptr;
			}

			node(const person &aCopy){
				this->data = new person(aCopy);
				this->next = nullptr;
			}

			~node(){
				if(data)
					delete data;
				data = nullptr;
				next = nullptr;
			}
		};

		node ** hashTable;
		int size;
		static const int INIT_SIZE = 10;
		int current_capacity;

		void print_r(node *);
		void destroy(); // destroy the array that holds the lists
		void destroyTableChain(node *&); // destroy a linked list
		void copyChain(node *, node *&); // the second needs to be a ptr ref because we will edit it by copying data in
		int hashIndex(const string &);
};
