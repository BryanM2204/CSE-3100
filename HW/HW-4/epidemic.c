#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum TYPE {S, I, R};

//TODO: Implement idx
//idx returns an integer to be used for hashing
//this integer should be unique for every x, y pair in your grid
int idx(int x, int y, int k)
{
	// create an index that is unique for the specific x, y
	int location = (x + k) + (2 * k + 1) * (y + k);
	return location;
}

typedef struct Host
{
	int id;
	int x, y;
	int t;
	enum TYPE type;
} THost;


typedef struct node_tag {
   THost host;				
   struct node_tag * next;
} node;

//create a node whose value is a specific host
//return a pointer to the created node
node * create_node(THost host) 
{	
	// allocate memory to node *p
	node *p = malloc(sizeof(node));

	// initialize the host and next values
	p->host = host;
	p->next = NULL;

	// returns the pointer to the node created
	return p;
}

//add_first() should add to the beginning of a linked list
//note the type: 'node **head'
//note that it does not return a value 
void add_first(node **head, node *newnode)
{
	// updates the next node that newnode points at to the old head
	newnode->next = *head;
	// update the head to the newnode
	*head = newnode;
}


//remove the first node from the list
//note the type: 'node **head'
//return a pointer to the removed content
node * remove_first(node **head) 
{
	// make sure that that the head is not NULL
	if(*head != NULL){
		node *current = *head;
		// update the head to point to the node next to the current first node
		*head = current->next;

		// free the current first node
		free(current);

		// returns pointer to the old head
		return current;
	} else {
		// returns NULL if head was equal to NULL
		return NULL;
	}
}

//remove all the nodes in the list
//and free all the allocated memory
void remove_all(node **head)
{
	// while loop to go through every node in the list until head equals NULL
	while (*head != NULL) {
		// create a new node p that is initialized to the node next to the current head node
		node *p = (*head)->next;
		// free the current head node
		free(*head);
		// update the empty head to the next node p
		*head = p;
  	}
}

//location_match checks whether a linked list contains
//one or more hosts in the same location as 'host'
//return 1 if there is a match, 0 if not
int location_match(node *head, THost host)
{

	node *current = head;

	// while current node is not NULL - loops through every node
	while(current != NULL){
		// checks to see if the host at the current node is at the same location as the host that was passed into the function
		if(current->host.x == host.x && current->host.y == host.y){
			// return 1 if they are occupying the same location
			return 1;
		} else {
			// if the current node host is at a different location - loop into the next node
			current = current->next;
		}
	}

	// return 0 if there are no matches
	return 0;
	
}


//hash function included for your convenience :)
unsigned hash(unsigned a)
{
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}
//summary prints out the proportions of different host types.
//It returns 1 if the number of infected hosts is not 0. 
int summary(THost hosts[], int m)
{   
    int S_n, I_n, R_n;
    
    S_n = I_n = R_n = 0;
    for(int i = 0; i < m; i++)
    {   
        S_n += (hosts[i].type == S);
        I_n += (hosts[i].type == I);
        R_n += (hosts[i].type == R);
    }
	if(I_n == 0)
	{
		printf("    S        I        R\n");
    	printf("%lf %lf %lf\n", (double)S_n/(S_n + I_n + R_n), 
		(double)I_n/(S_n + I_n + R_n), (double)R_n/(S_n + I_n + R_n));
	}
	return I_n > 0;
}

// one_round 
int one_round(THost *hosts, int m, node *p_arr[], int n_arr, int k, int T)
{
    //S -> I and I -> R
    for(int i = 0; i < m; i++)
    {
        if(hosts[i].type == S) //Note the use of enumerator S
        {
			//finish the following line of code
            int index = hash(idx(hosts[i].x, hosts[i].y, k)) % n_arr;
            if(location_match(p_arr[index], hosts[i]))
            {
            	//TODO: fill in what should happen here (not long)
				// if the status of the host at that current index is I
				if(p_arr[index]->host.type == I){
					// then the current host is infected 
					hosts[i].type = I;
				}

			}
        }
		else if(hosts[i].type == I)
        {
           	//TODO: fill in what should happen here (not long)

			// must find the location of the host
			int index = hash(idx(hosts[i].x, hosts[i].y, k)) % n_arr;
            if(location_match(p_arr[index], hosts[i])){
				// if the host at the current location is S
				if(p_arr[index]->host.type == S){
					// then the currrent host infects the host at that location - updates the status to I
					p_arr[index]->host.type = I;
				}
			}
			// update the time t for the infected host
			hosts[i].t += 1;
			// if the infected host has reached the required time T
			if(hosts[i].t == T){
				// host recovers - update status to R
				hosts[i].type = R;
			}
        }
    }

	//TODO: fill in code below
    //reset all linked lists

	// loop through entire array - clear out nodes
	for(int i=0; i < n_arr; i++){
		remove_all(&p_arr[i]);
	}


	for(int i = 0; i < m; i++)
	{
		int r = rand() % 4;
		//finish the follow code
		//0: up, 1: right, 2: down, 3: left
		//TODO: update locations for all hosts
		switch(r)
		{
			// for each case - corresponds to a movement - if the movement goes over the bound k
			// then it loops the corresponding x or y value to be the opposite k
			case 0: 
				hosts[i].y += 1;
				if(hosts[i].y > k){
					hosts[i].y = -k;
				}
				break;

			case 1: 
				hosts[i].x += 1;
				if(hosts[i].x > k){
					hosts[i].x = -k;
				}
				break;

			case 2: 
				hosts[i].y -= 1;
				if(hosts[i].y < -k){
					hosts[i].y = k;
				}
				break;

			case 3: 
				hosts[i].x -= 1;
				if(hosts[i].x < -k){
					hosts[i].x = k;
				}
				break;
		}

		//buid linked list for I hosts
		if(hosts[i].type == I)
		{
			node *r = create_node(hosts[i]);
			int index = hash(idx(hosts[i].x, hosts[i].y, k)) % n_arr;
			add_first(&(p_arr[index]), r);
		}
	}

	return summary(hosts, m);
}

int main(int argc, char *argv[])
{

	if(argc != 5)
	{
		printf("Usage: %s k m T N\n", argv[0]);
		return 0;
	}

	int k = atoi(argv[1]);
	int m = atoi(argv[2]);
	int T = atoi(argv[3]);
	int N = atoi(argv[4]);

	assert(k >= 0 && k <= 1000);
	assert(m >= 1 && m <= 100000);
	assert(T >= 1);
	assert(N > 0 && N <= 100000);
	srand(12345);

	//initialize hosts
	THost hosts[m];

	hosts[0].id = 0;
	hosts[0].x = 0;
	hosts[0].y = 0;
	hosts[0].t = 0;
	hosts[0].type = I;

	for(int i = 1; i < m; i ++)
	{
		hosts[i].id = i;
		hosts[i].x = rand() % (2*k + 1) - k;
		hosts[i].y = rand() % (2*k + 1) - k;
		hosts[i].t = 0;
		hosts[i].type = S;		
	}

	//initialize linked lists
	node *p_arr[N];

	for(int i = 0; i < N; i++)
	{
		p_arr[i] = NULL;
	}
	node *r = create_node(hosts[0]);
	int index = hash(idx(hosts[0].x, hosts[0].y, k)) % N;
	add_first(&(p_arr[index]), r);

	//simulation
	while(one_round(hosts, m, p_arr, N, k, T));

	return 0;
}