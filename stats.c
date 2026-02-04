/*
 * stats.c
 */

#include <stdio.h>
#include <string.h>
#include "stats.h"
#include <ctype.h>  


/**
 * Update the stats
 * @param stats	the histogram
 * @param str	the string used to update the histogram
 */
void updateStats(wordstats_t *stats, char *str) {
	// TODO - write me
	char copy[128];
	//copy the string because otherwise strtok will destroy everything and make life suck
	strcpy(copy, str);

	//This tokenizes the string based on spaces, tabs, and newlines
    char *token = strtok(copy, " \t\n");
    while (token != NULL) {
        stats->wordCount++;
        token = strtok(NULL, " \t\n");
    }

	//Go until we hit the null terminator
	//Don't use the copy because it has been destroyed by strtok
	for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower(str[i]);
		//use isalpha to check if it's a letter
        if (isalpha(c)) {
			//can use a neat little ascii trick to get index
            int index = c - 'a';
            stats->letterCounts[index]++;
			//check for vowel, if not vowel then consonant
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                stats->vowelCount++;
            } else {
                stats->consonantCount++;
            }
		}
	}
}


void printHistogram(wordstats_t *stats) {
    
	// Find the maximum letter count because we need to print top down
	int max = 0;
    for (int i = 0; i < 26; i++) {
        if (stats->letterCounts[i] > max) {
            max = stats->letterCounts[i];
        }
    }
	
	//first for loop goes down the rows
	for (int row = max; row > 0; row--) {
		//second for loop goes across the columns
        for (int i = 0; i < 26; i++) {
            if (stats->letterCounts[i] >= row) {
                printf("# ");
            } else {
                printf("  ");  
            }
        }
        printf("\n");
    }

	//print the letters at the bottom
    for (int i = 0; i < 26; i++) {
        printf("%c ", 'a' + i);
    }
    printf("\n");

	//print the counts at the bottom
    for (int i = 0; i < 26; i++) {
        printf("%d ", stats->letterCounts[i]);
    }
    printf("\n");
}

void printWordStats(wordstats_t *stats) {
    int totalLetters = stats->vowelCount + stats->consonantCount;
    double avgWordLen = stats->wordCount > 0 ? (double)totalLetters / stats->wordCount : 0.0;

    printf("\nWords = %d , Average Word Length = %.2f\n", stats->wordCount, avgWordLen);
    printf("Vowels = %d (%.2f%%), Consonants = %d (%.2f%%), Total= %d\n\n",
           stats->vowelCount, stats->wordCount > 0 ? (100.0 * stats->vowelCount / totalLetters) : 0.0,
           stats->consonantCount, stats->wordCount > 0 ? (100.0 * stats->consonantCount / totalLetters) : 0.0,
           totalLetters);
}

