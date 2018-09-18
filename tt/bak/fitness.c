/*
 * File: pluck_n_drop.c
 * Author: William "Amos" Confer
 *
 * Description:
 * Judging program for the programming competition.  Expects a test data
 * file as a command line argument and solution commands from stdin.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define MAX_STACKS 100

int main(int argc, char *argv[]) {

    int stacks[MAX_STACKS] = {0};
    int target[MAX_STACKS] = {0};

    int pos = 0;
    long operation_count = 0;

    long score;
    int stack_count;
    bool holding = false;
    int i;
    char c;

    char str[] = "Your score is: ";

    FILE *f;

    f = fopen(argv[1], "r");
    if(!f) {
        printf("YIKES!!! opening %s. Errno %d: %s\n", argv[1], errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d", &stack_count);

    for(i = 0; i < stack_count; i++) {
        fscanf(f, "%d", &(stacks[i]));
    }

    for(i = 0; i < stack_count; i++) {
        fscanf(f, "%d", &(target[i]));
    }

    fclose(f);

    do {
        operation_count++;
        scanf("%c", &c);
        switch(c) {
        case 'L':
            if(pos > 0) {
                pos--;
            }
            break;
        case 'R':
            if(pos < (stack_count - 1)) {
                pos++;
            }
            break;
        case 'P':
            if(!holding && stacks[pos] > 0) {
                stacks[pos]--;
                holding = true;
            }
            break;
        case 'D':
            if(holding) {
                stacks[pos]++;
                holding = false;
            }
            break;
        default:
            operation_count--;
            break;
        }

    } while(c != 'X');

    score = operation_count;
    for(i = 0; i < stack_count; i++) {
        long dif = stacks[i] - target[i];
        dif = dif >= 0 ? dif : -dif;
        score += dif * dif * dif;
    }

    printf("%s%ld\n", str, score);

    return EXIT_SUCCESS;
}
