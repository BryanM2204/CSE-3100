#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>

#define MAX 10240
#define MAX_WORD_COUNT 60000                //we have less than 60000 words
#define MAX_WORD_LENGTH 80                //each word is less than 80 letters

//Using these two global variables can be justified :)
char words[MAX_WORD_COUNT][MAX_WORD_LENGTH];        //2-d array to hold all the words
int word_count = 0;                    //number of words, initilized to 0

//Note the words in the dictionary file are sorted
//This fact could be useful
void read_file_to_array(char *filename)
{
    FILE *fp;

    //open the file for reading
    fp = fopen(filename, "r");
    if(fp==NULL)
    {
        printf("Cannot open file %s.\n", filename);
        exit(-1);
    }
    //make sure when each word is saved in the array words,
    //it does not ends with a '\n'
    //see how this is done using fscanf 
    while(!feof(fp))
        fscanf(fp, "%s\n", words[word_count++]);
    fclose(fp);
}

//TODO
//Test wether a string word is in the dictionary
//Return 1 if word is in the dictionary
//Return 0 otherwise
//Be efficient in implementing this function
//Efficiency is needed to pass test cases in limited time
int in_dict(char *word)
{

    // set left and right bounds
    int l = 0;
    int r = word_count - 1;

    while (l <= r) {
        // midpoint is found
        int m = (r + l) / 2;

        // compare the words 
        int result = strcmp(words[m], word);
 
        // if the words are the same - return 1
        if (result == 0) {
            return 1;
        }
 
        // If words[m] ascii value is smaller than word - then change left bound and disgard left portion
        if (result < 0) {
            l = m + 1;
        }
 
        // if the ascii value of words[m] is greater - ignore right side
        else {
            r = m - 1;
        }
    }
 
    // if the word is not present - return 0
    return 0;
}

//TODO
//Use key and shift to decrypt the encrypted message
//len is the length of the encrypted message
//Note the encrypted message is stored as an array of integers (not chars)
//The result is in decrypted

void decryption(unsigned char key, unsigned char shift, const int *encrypted, int len, char *decrypted)
{
    // for loop to go through every integer in the array encrypted
    for(int i = 0; i < len; i++)
    {
        // the integer is raised to key and bit shifted
        // it is then converted to a char which gives a letter - added to specific index in decrypted
        decrypted[i] = (char)((encrypted[i] ^ key) >> shift);
    }
    // at the end of the decryption, add '\0' to signal end of string
    decrypted[len] = '\0';

}

//TODO
//calculate a score for a message msg
//the score is used to determine whether msg is the original message
int message_score(const char *msg)
{
    // array created with sizE of MAX to createa copy of msg in order to not modify original copy
    char temp_msg[MAX];
    strcpy(temp_msg, msg);

    // parses the string into words by specific delimiter - which is the space " " - first word is declared to the pointer words
    char *words = strtok(temp_msg, " ");
    // keep track of the number of words found in dict
    int score = 0;

    // loops until no more words to find
    while(words != NULL){
        // call in_dict to see if the word is found in the dictionary
        if (in_dict(words)){
            // incrememnt if it is found
            score++;
        }

        // looks for the next word in temp_msg
        words = strtok(NULL, " ");
    }

    // final score is returned
    return score;
}

//search using all the (key, shift) combinations
//to find the original message
//result is saved in message
void search(const int *encrypted, int len, char *message)
{
	char decrypted[MAX];

    int max_score = 0;
    strcpy(message, "");
    for(unsigned char k = 0; k < 255; k++)
    {
        for(unsigned char shift = 0; shift <= 24; shift++)
        {
            decryption(k, shift, encrypted, len, decrypted);
			int score = message_score(decrypted);
			if(score > max_score)
			{	
				max_score = score;
				strcpy(message, decrypted);
			}
        }
    }
}

//TODO
//read the encrypted message from the file to encrypted
//return number of bytes read
int read_encrypted(char *filename, int *encrypted)
{
    // open the file read only
    int fd = open(filename, O_RDONLY);
    
    // checks to see if the file was properly opened or not
	if(fd < 0)
	{
		printf("Cannot open the file\n");
        	return -1;
    } 

    // the file is read and the contents are stored in encrypted with the number of bytes being read being calculated by sizeof(int) * MAX
    size_t bytes = read(fd, encrypted, sizeof(int) *MAX);
	
    // close the file that was opened
    close(fd);

    // return the number of bytes read divided by the size of an int 
    return (bytes / sizeof(int));
}

//Do not change the main() function
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("%s encrypted-message\n", argv[0]);
		return 0;
	}

	read_file_to_array("dict.txt");

	int encrypted[MAX];
	int len = read_encrypted(argv[1], encrypted);
	
	char message[MAX];
	strcpy(message, "");
	search(encrypted, len, message);
	printf("%s\n", message);
	return 0;
}