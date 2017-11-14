# mapreduce-in-c
hadoop mapreduce programs written in c

Changes to reducer.c

Added comments to reducer.c.

Increased size of word[] and currentWord[] arrays to fix segfault.

Replaced for and while loops ( used to reset memory in arrays to 0's ) with memset().

Tested with sorted output from readFromStdin mapper prog. and reducer output appears
to be correct.