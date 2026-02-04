/*
 * main.c
 * @author <your-name>
 */
#include <stdio.h>
#include <string.h>
#include "stats.h"
#include "menu.h"

#define MAX_INPUT_LEN 128	/** maximum allowed input length */

/**
 * @brief Main function
 */
int main(int argc, char *argv[]) {

	//starts with stats at 0
	wordstats_t stats = {0};
    char line[MAX_INPUT_LEN];


	//while loop runs until internally broken
    while (1) {
    input_mode:

        printf("Enter strings (# to stop):\n");
        while (1) {
            if (fgets(line, MAX_INPUT_LEN, stdin) == NULL) {
                printf("Error reading input.\n");
                return 1;
            }

            // remove trailing newline
            line[strcspn(line, "\n")] = '\0';

            if (strcmp(line, "#") == 0) break;

            updateStats(&stats, line);
        }

		//menu
        int option;
        while (1) {
            printMenu();

            if (scanf("%d", &option) != 1) {
                printf("Error: invalid input\n");
                return 1;
            }

            // clear leftover newline
            while (getchar() != '\n');

            switch(option) {
                case 1:
                    printWordStats(&stats);
                    break;
                case 2:
                    printHistogram(&stats);
                    break;
                case 3:
                    goto input_mode;  // return to string input
                case 4:
                    printf("Exiting...\n");
                    return 0;
                default:
                    printf("Error: Unknown option %d.\n", option);
                    return 1;
            }
        }
    }

	printf("Exiting...\n");
	return 0;
}
