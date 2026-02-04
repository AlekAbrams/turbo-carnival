/*
 * stats.h
 */

#ifndef STATS_H_
#define STATS_H_

// TODO word stats constants
#define NUM_LETTERS 26
// TODO word stats struct
typedef struct {
    int wordCount;
    int vowelCount;
    int consonantCount;
    int letterCounts[NUM_LETTERS];
} wordstats_t;

// TODO functions declarations
void updateStats(wordstats_t *stats, char *str);
void printWordStats(wordstats_t *stats);
void printHistogram(wordstats_t *stats);

#endif /* STATS_H_ */
