#ifndef LINKED_NODE_LIST_H//is node already defined, avoids cyclic defines
#define LINKED_NODE_LIST_H

#include "Node.h"

class Linked_Node_List
{
    public:
        Linked_Node_List() {/*constructor*/}
        virtual ~Linked_Node_List() {/*destructor*/}
        //Add a node to the end of the list
        void Push_node(Node* dummy)
        {
			//if the start node is nothing (ie, the linked list is empty
            if(LL_START_NODE==NULL)
            {
				//make the new node the start node and the end node
                LL_START_NODE = dummy;
                LL_END_NODE = dummy;
            }else{
				//start node not empty, add the node normally
				//set the end node to point to the new node
                LL_END_NODE->SetNext(dummy);
				//set the new node to point back to the (old) end node
                dummy->SetPrevious(LL_END_NODE);
				//set the new end node as the new node
                LL_END_NODE = dummy;
            }
        }
        //Remove a node from the end of the list, and return the result
        Node* Pop_node()
        {
            Node* dummy;
            dummy = LL_END_NODE;
			//if the end node is not nothing (ie, the list is not empty)
            if(dummy!=NULL)
            {
				//if the end node has no previous, ie, the list has only one node in it
                if(LL_END_NODE->GetPrevious()==NULL)
                {
					//set the end and start node to null
                    LL_END_NODE = NULL;
                    LL_START_NODE = NULL;
                }else{//the node has >1 nodes
					//new end node is the node before previous
                    LL_END_NODE = LL_END_NODE->GetPrevious();
					//break link to old end node
                    LL_END_NODE->SetNext(NULL);
                }
            }
			//return the last node
            return dummy;
        }
		//removes a node from the list, similar to popping, but takes a node* argument to specify a specific node
        void Remove_node(Node* dummy)
        {
			//gets the previous and next nodes to the passed node
            Node* dummy_prev;
			Node* dummy_next;
            dummy_prev = dummy->GetPrevious();
            dummy_next = dummy->GetNext();
			//checks to see if they are null
            if(dummy_prev != NULL)
				//sets the previous node to point to the next
                dummy_prev->SetNext(dummy_next);
            if(dummy_next != NULL)
				//sets the next node to point to the previous
                dummy_next->SetNext(dummy_prev);
        }
		//iterates through the node and prints information about them
        void Iterate_nodes()
        {
            std::cout<<"Iterating Nodes:"<<"\n";
            Node* dummy = LL_START_NODE;
            while(dummy!=NULL)
            {
                //print out the data from the node, or draw it or whatever.
                //std::cout<<"X:"<<dummy->GetX()<<" Y:"<<dummy->GetY()<<"UID:"<<dummy->uid<<"\n";
                std::cout<<"Node "<<dummy->s_udata<<" with v = "<<dummy->GetValency()<<"\n";
                dummy = dummy->GetNext();
            }
            std::cout<<"Done iterating\n";
        }
		//gets a specific node from the list, based upon its position in the list, with error checking to return null nodes if given a number outside the list
        Node* GetNode(int i)
		{
			Node* dummy = LL_START_NODE;
			//iterates through with a for loop
			for(int j = 0;j<i;j++)
			{
				dummy=dummy->GetNext();
				//if the node is null, return it, as the loop has gone on beyond the limits of the linked list
				if(dummy==NULL)
					return dummy;
			}
			return dummy;
		}
		//Gets a specific node based upon the userdata of the node
		Node* StringGetNode(std::string s)
		{
		    Node* dummy = LL_START_NODE;
			//iterates through
		    while(dummy!=NULL)
		    {
				//if the userdata of the iteration node matches the string s
                if(dummy->s_udata == s)
                {
					//return the node*
                    return dummy;
                }
		        dummy = dummy->GetNext();
		    }
			//node not found, return null
		    return NULL;
		}
		//clears the list of nodes, by repeatedly popping nodes from the end of the list, and deleting them
		void ClearList()
		{
		    Node* dummy = Pop_node();
		    while(dummy!=NULL)
		    {
		        delete dummy;
		        dummy = Pop_node();
		    }
		}
		//Class to iterate through the nodes in the linked list, and call a programmed defined function
		//Passes the function the iteration number, as well as the node.
		//Also (optionally, the programmer can simply pass 0) passes a void pointer to allow the programemr
		//to pass some of his own information
		void F_Iterate_nodes(void (*function_pointer)(int,Node))
		{
			//ref_iterator provides information about which iteration the function is at
		    int ref_iterator = 0;
		    Node* dummy = LL_START_NODE;
            while(dummy!=NULL)
            {
                //increment the iterator
                ref_iterator++;
				//calls the function with the iterator, and the node (by value, not as pointer)
                function_pointer(ref_iterator,*dummy);
                dummy = dummy->GetNext();
            }
		}
		//the first and last nodes of the linked list
        Node* LL_START_NODE;
        Node* LL_END_NODE;
    protected:
    private:
};

#endif // LINKED_NODE_LIST_H
