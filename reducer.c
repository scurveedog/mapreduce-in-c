/*
 * reducer.c
 *
 * File reads lines from  system stream stdin.  Test for use in c language map,
 * reduce file for hadoop jobs. Possibly  use this as logic for a c mapper pro-
 * gram. Uses getline() to read lines from file, then strtok  gets tokens based
 * on delimiters listed in delim[] array.
 *
 * Input:
 *		Read data stream from stdin.
 *
 * Output:
 *		Ea. word from stdin on it's own line.  Output sorted  with $> sort is
 *		ready to pass to a hadoop reduce file.
 *
 * Invocation:
 * 	Pipe some data to exec
 *		$> cat token-out.txt | ./readLine | sort -k1,1
 */

#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#define ARRAYSZ(x) (sizeof x/sizeof x[0])

int main(void){

	char *token, *linePtr;
	char count[] = "1";
	/* Arrays to hold returns from strtok. */
	char word[120] = {0};
	char currentWord[120] = {0};
	/* delimiters used by strtok. */
	const char delim[] = "\t";
	/* Assumes word length < 40 chars. */
	long unsigned int space = 120;
	int currentCount = 1, i = 0;
	/* Used to verify result of getline() call. */
	int lineBytes = 0;
	
	linePtr = (char *)malloc(space);

	do{
			(lineBytes = getline(&linePtr, &space, stdin)) != -1;
			/* Get token1 (word) key */
			token = strtok(linePtr, delim);
			memcpy(word, token, strlen(token));
			
			/* Compare arrays for equality.  If == 0, Means we 
			 * have more than one instance of 'word' in input. */
			if(strcmp(word, currentWord) == 0){
				currentCount += 1;
			}
			else{
				if(currentWord[0] != 0)
				   /* print stats for prev. word */
					printf("\n%s\t%d", currentWord, currentCount);
					
				/* Reset currentWord array. */
				memset(currentWord, 0, ARRAYSZ(currentWord));

				memcpy(currentWord, word, strlen(word));
				currentCount = atoi(count);
			}
			/* Get token2 (value). If no more lines exit! */
			if((token = strtok(NULL, delim)) == NULL)
				continue;

			memset(word, 0, ARRAYSZ(word));

		}while(token);
		
		/* prints last data before prog end */
		printf("\n%s\t%d", currentWord, currentCount);

	return(0);
}
