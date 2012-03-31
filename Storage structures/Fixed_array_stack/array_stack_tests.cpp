#include <iostream>
#include <cstdio>
#include "fixedarraystack.h"
using namespace std;
class stpl
{
public:
	stpl()
	{
	}
	virtual ~stpl()
	{
	}
	int x,y;
	char z;
private:
};

int main(int argc, char** argv)
{
	fixedarraystack<stpl> test_stack(10);
	for(int i = 0;i<20;i++)
	{
		stpl j;
		j.x = i;
		j.y = i*i;
		j.z = (char)i;
		test_stack.push(j);
		std::cout<<"pushed "<<i<<"\n";
	}
	
	for(int i = 0;i<9;i++)
	{
		stpl* rvalue;
		test_stack.pop(rvalue);
		if(rvalue!=NULL)
		{
			std::cout<<rvalue->x<<"\n";
		}
	}
	std::cout<<"completed...\n";
	return 0;
}