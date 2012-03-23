#ifndef NODE_H//is node already defined, avoids cyclic defines
#define NODE_H

#include <string>

class Node
{
    public:
        Node()
        {
			//initialise the nodes information
            LINKCOUNT = 0;
            searchID = -1;
            f_score = 0;
            g_score = 0;
            h_score = 0;
            NEXT = NULL;
            PREVIOUS = NULL;
            parent = NULL;
            s_udata = "";
			//loop through the connections setting them to null
            for(int i = 0;i<128;i++)
            {
                CONNECTIONS[i] = NULL;
                FLAGS[i] = 0;
            }
        }
        virtual ~Node()
        {
			//destructor
            db<<"destructor called of node "<<s_udata<<"\n";
        }
        //Set the location of the node in the map
        void SetCoord(float x_n, float y_n)
        {x=x_n;y=y_n;}
        //Get the x coordinate
        float GetX(){return x;}
        //Get the y coordinate
        float GetY(){return y;}
        //Get the next node in the linked list
        Node* GetNext(){return NEXT;}
        //Get the previous node in the linked list
        Node* GetPrevious(){return PREVIOUS;}
        //Sets the next node in the linked list
        void SetNext(Node* dummy){NEXT = dummy;}
        //Sets the previous node in the linked list;
        void SetPrevious(Node* dummy){PREVIOUS = dummy;}
        //Adds a new node to the network (actually just gives a pointer to a neighbour of this node
        //128 is the maximum neighbours for the node, and should really be set as a constant in defines.h
        int AddNode(Node* dummy, int flag)
        {
			//checks to ensure that not trying to add a null pointer
            if(dummy!=NULL)
            {
				//checks that the linkcount is not exceeded
                if(LINKCOUNT<128)
                {
					//checks to see if the node is alreay linked
                    bool resident = false;
                    for(int i = 0;i<LINKCOUNT;i++)
                    {
                        if(CONNECTIONS[i]->uid == dummy->uid)
                        {
                            db<<"the node is resident, not adding\n";
                            resident = true;
                        }
                    }
                    if(resident == true)
                    {
						//connection already there.
                        return -3;
                    }else{
						//Add the connection before incrementing, to ensure correct position
                        CONNECTIONS[LINKCOUNT] = dummy;
                        FLAGS[LINKCOUNT] = flag;
						//increment the linkcount
                        LINKCOUNT++;
						//return the resultant valency
                        return LINKCOUNT;
                    }
                }else{
					//too many connections
                    return -2;
                }
           }else{
				//null pointer
				return -1;
           }
        }
        //Gets the number of connected nodes (the valency)
        int GetValency(){return LINKCOUNT;}
        //Gets the adjacent node specified by i
        Node* GetConnection(int i){return CONNECTIONS[i];}
		//Gets the flags of the connection i
        int GetFlag(int i){return FLAGS[i];};
		//the unique id of the node
        int uid;
		//The userdata of the node, as a string
        std::string s_udata;

        //PATHFINDING INFORMATION
		//Parent node in the path
        Node* parent;
		//The id of the most recent search performed on the node
        int searchID;
		//the f_score of the node, sum of g and h scores
        double f_score;
		//the g_score of the node, the distance from the start node (traced along the path)
        double g_score;
		//the heuristic distance to the final node (euclidian)
        double h_score;
    protected:
    private:
		//x/y location of the node
        float x,y;
		//number of current links
        int LINKCOUNT;
		//previous node in the linked list
        Node* PREVIOUS;
		//next node in the linked list
        Node* NEXT;
		//array of connections, limited to 128
        Node* CONNECTIONS[128];
		//flags for connections
        int FLAGS[128];
};
#endif // NODE_H
