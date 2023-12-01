#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../utils/utils.c"

int char_to_int(char c) {
    return c - '0';
}

int slice_to_int(char* slice) {
    const char numbers[9][6] = {
            "one", "two", "three", "four",
            "five", "six", "seven", "eight", "nine"
    };
    for (int i = 0; i < 9; i++) {
        const char* number = numbers[i];
        // Check if slice starts with number
        if (strncmp(slice, number, strlen(number)) == 0) {
            return i + 1;
        }
    }
    return -1;
}

int solve(char* input, int part_two) {
    int length = strlen(input);
    int sum = 0;
    int first = -1;
    int last = -1;
    for (int i = 0; i < length; i++) {
        char c = input[i];
        // Reset
        if (c == '\n') {
            sum += first * 10 + last;
            first = -1;
            last = -1;
            continue;
        }
        int n = char_to_int(c);
        if (n > 0 && n < 10) {
            if (first == -1) {
                first = n;
            }
            last = n;
            continue;
        }
        if (part_two) {
            char* slice = (char*)(input + i);
            int number = slice_to_int(slice);
            if (number == -1) {
                continue;
            }
            if (first == -1) {
                first = number;
            }
            last = number;
        }
    }
    return sum;
}

int main() {
    char* input = read_file("input.txt");
    printf("Part 1: %d\n", solve(input, 0));
    printf("Part 2: %d\n", solve(input, 1));
    return 0;
}
