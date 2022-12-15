#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    FILE* input;
    input = fopen("input.txt", "r");
    char buff[255];
    int x = 1;
    int cycle = 0;
    int part1 = 0;
    char part2[42 * 6];
    int sprite[3] = { 0, 1, 2 };
    while (fgets(buff, 255, input) != NULL) {
        int cpu_cycles;
        int addx = 0;
        if (strcmp(buff, "noop\n") == 0) {
            cpu_cycles = 1;
        }
        else {
            cpu_cycles = 2;
            addx = atoi(buff + 5);
        }

        for (int i = 0; i < cpu_cycles; i++) {
            int index = cycle % 40;
            bool is_sprite = false;
            for (int j = 0; j < 3; j++) {
                if (index == sprite[j]) {
                    is_sprite = true;
                }
            }
            if (is_sprite) {
                strcat(part2, "#");
            }
            else {
                strcat(part2, ".");
            }

            cycle++;

            if (cycle % 40 == 20) {
                part1 += cycle * x;
            }
            else if (cycle % 40 == 0) {
                strcat(part2, "\n");
            }

            if (i == 0) {
                continue;
            }
            x += addx;
            for (int j = 0; j < 3; j++) {
                sprite[j] += addx;
            }
        }
    }
    printf("Part 1: %d\n", part1);
    printf("Part 2:\n%s", part2);
    fclose(input);
    return 0;
}