#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//There will be m players in an array
typedef struct Player 
{
	int id;
	int loc;
	long balance;
} TPlayer;

//There will be n properties in an array
typedef struct Property
{
	int id;
	int owner_id;
	int rent;
} TProperty;


//TODO
//Implement the following function
//The player p1 needs to pay the player p2 'amount' of dollars
//If p1 has enough balance, the transaction will be successful
//Otherwise, p1 will pay all of their balance to p2, and the transaction
//is not successful 
//return 1 if the transaction is successful
//Otherwise, return 0
int transaction(TPlayer *p1, TPlayer *p2, int amount)
{
	// if statement - checks to see if player 1 has enough money in their bank to pay off rent
	if(p1->balance >= amount){
		// player 2 recieves amount - deducted from player 1's balance 
		p2->balance += amount;
		p1->balance -= amount;
		// returns 1 (success)
		return 1;
	} else {
		// else statement occurs when player 1 does not have enough money
		// pays player 2 entire balance - player 1's balance goes to 0
		p2->balance += p1->balance;
		p1->balance = 0;
		// returns 0 (fail)
		return 0;
	}

}

//TODO
//Finish the following function
//If one player cannot pay rent to another player, this function should return 0. 
//The rest of the players will not get chances to play when this happens 

int one_round(int m, int n, TPlayer p[], TProperty prop[])
{
	for(int i = 0; i < m; i++)
	{
		int steps = rand() % 6 + 1 + rand() % 6 + 1;
		//fill in the code below

		// updates the player's location with the randomized dice roll
		p[i].loc += steps;

		// initialize results depending on success of transaction
		int result = 0;

		// if statement - check to see if the location of player is in the bounds
		if(p[i].loc < n){
			// checks to see if property that player is on is owned or not
			if (prop[p[i].loc].owner_id == -1) {
				// accesses prop structure and updates owner_id of property that player lands on - claim it
				prop[p[i].loc].owner_id = i;

			} else {
				// else block runs if property is owned
				// create pointer to TPlayer - obtains the player that owns the property
				TPlayer *owner = &p[prop[p[i].loc].owner_id];
				
				// transaction is passed between current player and owner with the property's rent cost
				result = transaction(&p[i], owner, prop[p[i].loc].rent);

				// checks value of result - if 0 then it terminates game
				if (result == 0)
                {
                    return 0;
                }
			}

		// this else statement runs if player's location goes over the bound n
		} else {
			// loops back to beginning - thus the location is subtracted by the limit n
			p[i].loc -= n;

			// player is awarded with n currency for looping back to beginning
			p[i].balance += n;

			// checks to see if player landed on owned property 
			if (prop[p[i].loc].owner_id == -1) {
				// player claims property if it has not been claimed
				prop[p[i].loc].owner_id = i;

			} else {
				// pointer created to owner of property
				TPlayer *owner = &p[prop[p[i].loc].owner_id];
				
				// transaction occurs between player and owner with rent amount
				result = transaction(&p[i], owner, prop[p[i].loc].rent);

				// checks value of result - if 0 then it terminates game
				if (result == 0)
                {
                    return 0;
                }
			}
		}
	}
	return 1;
}

//used for printing out results
void print_result(int m, TPlayer p[])
{
	printf("      id    balance\n");
	for(int i = 0; i < m; i++)
	{
		printf("%8d %8ld\n", p[i].id, p[i].balance);
	}
	long sum = 0;
	long max = 0;
	for(int i = 0; i < m; i++)
	{
		sum += p[i].balance;
		if(p[i].balance > max) max = p[i].balance;
	}
	printf("average: %f max: %ld, max/average = %lf\n", (double)sum/m, max, (double)max*m/sum); 
}

//max_rounds is needed because the game may never finish
void monopoly(int m, int n, TPlayer p[], TProperty prop[], int max_rounds)
{
	srand(12345);
	int rounds = 1;
	while(one_round(m, n, p, prop) && rounds < max_rounds)
	{
        rounds ++;
	}

	print_result(m, p);
	printf("after %d rounds\n", rounds);
}

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		printf("Usage: %s m n rounds\n", argv[0]);
		return -1;
	}
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int rounds = atoi(argv[3]);
	assert(n >= 13);
	assert(m >= 1);
	assert(rounds >= 1);

	
	TPlayer p[m];
	TProperty prop[n];

	for(int i = 0; i < n; i++)
	{
		prop[i].id = i;
		prop[i].owner_id = -1;
		prop[i].rent = i + 1;
	}

	for(int j = 0; j < m; j++)
	{
		p[j].id = j;
		p[j].loc = 0;
		p[j].balance = n;
	}
	monopoly(m, n, p, prop, rounds);
	return 0;	
}