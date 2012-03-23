/*
	tests for new linked list class
	compile using:
		g++ Linked_list_tests.cpp -o llt -Wall -ggdb
	Adam Harries
*/

#include <iostream>
#include <cstdio>
#include "linkedlist.h"

class test_obj
{
	public:
	test_obj()
	{
	}
	virtual ~test_obj()
	{
	}
	int a;
	char b;
	long c;
};
int main(int argc, char** argv)
{
	//tests to be written
	linkedlist<test_obj> test_list;
	for(int i = 0;i<100;i++)
	{
		test_obj a;
		a.a = i;
		a.b = (char)i;
		a.c = i*i;
		std::cout<<a.a<<","<<a.b<<","<<a.c<<"\n";
		test_list.add_node(a);
	}
	if(test_list.is_empty() == false)
	{
		if(test_list.get_first()!=NULL)
		{
			if(test_list.get_first()->next_ptr == NULL)
			{
				std::cout<<"null\n";
			}else{
				std::cout<<"not null\n";
			}
		}
	}else{
		std::cout<<"list is empty...\n";
	}
	return 0;
}