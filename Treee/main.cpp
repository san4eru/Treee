#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>
#include <crtdbg.h>  

#include "List.h"

int main() {
	List<int> list;
	list.push_back(3);
	list.push_back(2);
	list.push_back(1);
	list.push_back(0);
	list.push_back(10);
	list.push_back(-1);
	list.push_back(11);
	list.print();
	//list.pop();//list.sort();
	//list.print();
	//list.pop();
	//list.print();

	//List<int> list2;
	//list2 = list;
	//list.print();
	//list2.print();
	//list = list + list2;
	//list.print();
	//cout << endl;
	//List<List<int>> list3;
	//list3.push_back(list2);
	//list3.insert(list2);
	//list3.print();

	_CrtDumpMemoryLeaks();
	return 0;
}