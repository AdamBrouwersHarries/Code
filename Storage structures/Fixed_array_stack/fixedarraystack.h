#ifndef FIXEDARRAYSTACK_H
#define FIXEDARRAYSTACK_H

/*
	Fixed size stack
	Uses a fixed block of memory to implement a "circular" stack
	When new values are pushed in, old values are discarded/
	overwritten from the opposite end of the stack.
	Allows for an efficent (I guess) way of holding a fixed number
	of "recent" items, for instance a set of previous locations, 
	for a set number of locations.
*/

template <class payload_data>
class fixedarraystack
{
public:
	fixedarraystack(int s)
	{
		head_pointer = 0;
		size = s;
		mem = new payload_data[s];
	}
	virtual ~fixedarraystack()
	{
		std::cout<<"cleaning up...\n";
		delete[] mem;
		std::cout<<"cleaned...\n";
	}
	void resize(int s)
	{
		head_pointer = 0;
		delete[] mem;
		size = s;
		mem = new payload_data[s];
	}
	void push(payload_data pl)
	{
		head_pointer = (head_pointer+1)%size;
		mem[head_pointer] = pl;		
	}
	void pop(payload_data *pl)
	{
		std::cout<<"hp val = "<<head_pointer<<"\n";
		*pl = mem[head_pointer];
		if(pl!=NULL)
		{
			head_pointer = ((head_pointer+size)-1)%size;
			std::cout<<"		now"<<head_pointer<<"\n";
		}
	}
private:
	int head_pointer;
	int size;
	payload_data* mem;
};

#endif //FIXEDARRAYSTACK_H