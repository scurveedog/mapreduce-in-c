/*
 * reducer.c
 *
 * File takes sorted input from mapper program 'readFromStdin' and outputs
 * a chr/string(key) field followed by a tab followed by a int/count(value)
 * field. The output should be a tab delimited list of key/value on seperate
 * lines. The value should indicate the total of each unique key found in 
 * the input data. 
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
 *		$> cat token-out.txt|./readFromStdin|sort -k1,1|./reducer
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAYSZ(x) (sizeof x/sizeof x[0])

int main(void){
	char *token, *linePtr;
	/* Arrays to hold returns from strtok. */
	char word[120] = {0};
	char currentWord[120] = {0};
	/* delimiters used by strtok. */
	const char delim[] = "\n\t ";
	/* Assumes max word length <= 120 chars. */
	long unsigned int space = 120;
	int currentCount = 1, i = 0;

	linePtr = (char *)malloc(space);
	do {
		 	getline(&linePtr, &space, stdin);
			/* Get token1 (word) key */
			token = strtok(linePtr, delim);
			memcpy(word, token, strlen(token));
			
			/* Compare arrays for equality.  If == 0, Means we
			 * have more than one instance of 'word' in input. */
			if(strcmp(word, currentWord) == 0) {
				currentCount += 1;
			}
			else {
				if(currentWord[0] != 0)
					/* prn stats for prev. word. */
					printf("\n%s\t%d", currentWord, currentCount);
				
				/* Reset currentWord array. */
				memset(currentWord, 0, ARRAYSZ(currentWord));
				
				memcpy(currentWord, word, strlen(word));
				currentCount = 1;
			}
			memset(word, 0, ARRAYSZ(word));
			
			/* Get token2 (value). If no more lines exit. */
			token = strtok(NULL, delim);
			
		} while(token);
		
		/* Prints last data before prog end */
		printf("\n%s\t%d", currentWord, currentCount);
		
	return(0);
}
