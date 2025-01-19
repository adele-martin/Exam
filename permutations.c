/*
expected files: *.c *.h
function allowed: puts, malloc, calloc, realloc, free, write

write a program that will print all the permutations of a string given as an argument
solutions must be given in an alphabetical order

we will not try your program with duplicates. example: "abccd"

./permutations a
a

./permutations ab
ab
ba

./permutations abc
abc
acb
bac
bca
cab
cba
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to swap characters in a string
void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Recursive function to generate permutations
void permute(char *str, int start, int end) {
    if (start == end) {
        puts(str);
        return;
    }

    for (int i = start; i <= end; i++) {
        // Swap the current character with the start
        swap(&str[start], &str[i]);

        // Recur for the next character
        permute(str, start + 1, end);

        // Backtrack by swapping back
        swap(&str[start], &str[i]);
    }
}

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return *(const char *)a - *(const char *)b;
}

void sort_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (str[i] > str[j]) {
                swap(&str[i], &str[j]);
            }
        }
    }
}


int main(int argc, char **argv) {
    if (argc != 2) {
        write(2, "Usage: ./permutations <string>\n", 34);
        return 1;
    }

    char *input = argv[1];
    int len = strlen(input);

    // Copy the input string to avoid modifying the original
    char *str = malloc((len + 1) * sizeof(char));
    if (!str) {
        write(2, "Memory allocation error\n", 25);
        return 1;
    }
    strcpy(str, input);

    // Sort the string to ensure permutations are generated in order
    qsort(str, len, sizeof(char), compare);

    // Generate permutations
    permute(str, 0, len - 1);

    // Free allocated memory
    free(str);

    return 0;
}