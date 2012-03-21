#include <stdio.h>
int f(int n)
{
	if(n == 1 || n == 0)
	{
		return 1;
	}else{
		return f(n-1)+f(n-2);
	}
}
int main(){
	int i = 0;
	for(i = 0;i<20;i++)
	{
		printf("number %i = %i\n",i,fib(i));
	}
	return 0;
}
