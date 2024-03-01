#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//TODO
void letter_counts(char a[], int n, int counts[26])
{
    for(int i=0; i < 26; i++){
        counts[i] = 0;
    }
    // loop through each character in a[i] - iterates through entire list using the first letter as target
    for(int i=0; i < n; i++){
        // iterates through entire list -
        for(int j = 0; j < n; j++){
            if(counts[i] == 0){
                if(a[i] == a[j]){
                    counts[i]++;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: %s n\n", argv[0]);
        return -1;
    }
    int n = atoi(argv[1]);
    printf("n=%d\n", n);
    assert(n >= 1 && n <= 10000);

    char a[n];
    int sum = 0;
    for(int i=0; i<n; i++)
    {
        sum += 2*i +1;
        a[i] = sum % 26 + 97;
    }

    int counts[26];
    letter_counts(a, n, counts);
    //TODO
    for(int i=0; i < n; i++){
        if (a[i] >= 1){
            printf("%c %d\n", a[i], counts[i]);
        }
    }

    return 0;
}