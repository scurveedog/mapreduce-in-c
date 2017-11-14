/*
 * readFromStdin.c
 *
 * Program reads lines from  system stream, stdin.  Test for use in c language
 * mapReduce file for hadoop jobs.  Possibly  use this as logic for a c mapper
 * program. Uses getline() to read lines from file & then strtok to get tokens
 * based on delimiters listed in delim[] array.
 *
 * Input:
 *		Read data stream from stdin.
 *
 * Output:
 *		Each word from input sources on a line as a key delimited with a tab '\t'
 *		then a hardcoded value of '1'. For example:
 *			"the"		"1"
 *
 * Invocation:
 * 	Pipe some data to exec
 *		$> cat token-out.txt | ./readFromStdin | sort -k1,1
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

int main(void)
{
	unsigned long int nbytes = 81;
	char *token, *linePtr;
	const char delim[] = "\n ";

	linePtr = (char *)malloc(nbytes);

	// &linePtr == **linePtr
	while(getline(&linePtr, &nbytes, stdin) != -1)
	{
		/* gets 1st field (key) into token */
		token = strtok(linePtr, delim);
		while(token)
		{
			printf("%s\t1\n", token);
			/* gets 2nd field (value) into token */
			token = strtok(NULL, delim);
		}
	}
	return 0;
}
