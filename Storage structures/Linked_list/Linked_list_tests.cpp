/*
	tests for new linked list class
	compile using:
		g++ Linked_list_tests.cpp -o llt -Wall -ggdb
	Adam Harries
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include "linkedlist.h"

class test_obj
{
	public:
	test_obj()
	{
	}
	test_obj(int x, char y, long z)
	{
		a = x;b = y;c=z;
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
	linkedlist<test_obj*> test_list;
	llnode<test_obj*> *second, *first, *third;
	test_obj *f_o, *s_o, *t_o;
	f_o = new test_obj(1,(char)42, 1);
	s_o = new test_obj(2, (char) 43, 4);
	t_o = new test_obj(3, (char) 44, 9);
	first = test_list.add_node(f_o);
	second = test_list.add_node(s_o);
	third = test_list.add_node(t_o);
	test_list.remove_node(second);
	std::cout<<first->next_ptr->payload->a<<"\n";
	std::cout<<third->prev_ptr->payload->a<<"\n";
	delete f_o;
	delete s_o;
	delete t_o;	
	return 0;
}