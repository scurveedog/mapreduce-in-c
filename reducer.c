/*
 * reducer.c
 *
 * File reads lines from  pre-opened stream stdin.  Test for use in c language
 * mapReduce file for hadoop  job. Possibly  use this as logic for a c reducer
 * program. Uses getline() to read lines from file & then strtok to get tokens
 * based on delimiters listed in delim[] array.
 *
 * Input:
 *		Read data stream from stdin.
 *
 * Output:
 *		Ea. word from stdin on it's own line.  Output sorted  with $> sort is
 *		ready to pass to a hadoop reduce file.
 *
 * Test invocation:
 * 	Pipe some data to exec
 *		$> cat token-out.txt | ./reducer | sort -k1,1
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

int main(void)
{
	char *token, *linePtr;
	char word[40] = {0};
	char count[11] = {0};
	const char delim[] = "\n\t";
	char currentWord[40] = {0};

	long unsigned int space = 40;
	int currentCount = 1, i = 0;

	linePtr = (char *)malloc(space);

	while(getline(&linePtr, &space, stdin) != -1)
	{
		token = strtok(linePtr, delim);
		while(token)
		{
			if(token == currentWord){
				currentCount += 1;
			}
			else{
				i = 0;
				while(currentWord[i] != 0)
					currentWord[i++] = 0;

				for(i = 0; i < strlen(token); i++){
					currentWord[i] = *(token + i);
				}
				printf("\n%s\t%d", word, currentCount);

				i = 0;
				while(word[i] != 0)
					word[i++] = 0;
			}
			token = strtok(NULL, delim);
			for(i = 0; i < 1; i++)
				count[i] = *(token + i);

			currentCount = atoi(count);
			token = strtok(NULL, delim);
		}
	}
	return(0);
}
