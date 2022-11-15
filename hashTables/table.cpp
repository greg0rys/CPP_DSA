#include "table.h"

// default constructor for the class, set all fields to nullptr
// and all sizes to 0
table::table()
{
	this->hashTable = new node*[INIT_SIZE];
	this->current_capacity = INIT_SIZE;
	this->size = 0;

	for(auto i = 0; i < INIT_SIZE; i++)
		hashTable[i] = nullptr;
}


// copy constructor for the class; makes use of overloaded assignment
table::table(const table &aTable): hashTable(nullptr), size(0), current_capacity(0)
{
	*this = aTable;
}


// class destructor see private method below
table::~table()
{
	destroy();
}


/**
 * destroy all of the linked lists and the pointer to the table array itself at
 * destruction
 */
void table::destroy()
{
	for(auto i = 0; i < current_capacity; i++){
		destroyTableChain(hashTable[i]);
	}

	if(hashTable)
		delete []hashTable;
}


/**
 * Since this is a hash table implemented as an array of linked list
 * we must destroy all the pointers in each list at class destruction
 * @param head a pointer ref to the head of the list being deleted
 */
void table::destroyTableChain(node *& head)
{
	if(!head)
		return;
	if(head)
	{
		destroyTableChain(head->next);
		delete head->data;
		delete head;
		head = nullptr;
		size--;
	}
}


/**
 * copy a linked list chain from the source table in copy assignment
 * @param sourceHead a pointer to the head of the linked list in the source
 * table
 * @param destinationHead a pointer ref to the head of the linked list in the
 * new table
 */
void table::copyChain(node * sourceHead, node *& destinationHead)
{
	// recursive copy
	if(!sourceHead)
		return;
	if(sourceHead)
	{
		destinationHead = new node(*(sourceHead->data));
		copyChain(sourceHead->next, destinationHead->next);
	}
}


/**
 * Overloaded assignment operator. Copy each chain from inside the src
 * table
 * @param aTable a reference to the table object we are copying
 */
const table& table::operator=(const table &aTable)
{
	if(this == &aTable)
		return *this;
	if(this->hashTable)
		destroy();
	size = aTable.size;
	current_capacity = aTable.current_capacity;
	hashTable = new node*[current_capacity];

	for(auto i = 0; i < current_capacity; i++)
	{
		hashTable[i] = nullptr; // first set the index to nullptr;
		copyChain(aTable.hashTable[i], this->hashTable[i]); // then copy the linked list into the index we just set = nullptr;
	}

	return *this;
}


/**
 * add a new person to one of the chains in the table
 * @param person a reference to a person object
 * @return true if we added, false if the list is at cap
 */
bool table::add(const person &aPerson)
{
	if(size == current_capacity)
		return false;
	int calculated_index = hashIndex(aPerson.getName());
	node * newNode = new node(aPerson);
	newNode->next = hashTable[calculated_index];
	hashTable[calculated_index] = newNode;
	size++;

	return true;
}

/**
 * print each chain in the table by looping through each index in the table
 * and calling the recursive print function on the list at that index
 * @return true if we printed the list false if the size is 0 indicating an 
 * empty list.
 */
bool table::print()
{
	if(size == 0)
		return false;
	
	for(auto i = 0; i < current_capacity; i++){
		static int table_nr = 1;
		printf("Table number: %d\n",table_nr);
		print_r(hashTable[i]);
		cout << endl;
	}

	return true;
}


/**
 * Print each chain in the hash table recursively
 * @param tableHead a pointer to the head of the linked list at the tables
 * index
 * @return void
 */
void table::print_r(node * tableHead)
{
	if(!tableHead)
		return;
	if(tableHead)
	{
		cout << tableHead->data->getName() << endl;
	}
}


/**
 * hash each items key to get its index in the table
 */
int table::hashIndex(const string &key)
{
	int hashingValue = 0;

	for(size_t i = 0; i < key.length(); i++)
		hashingValue += key.at(0);

	return hashingValue % current_capacity;
}


