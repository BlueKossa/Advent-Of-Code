#include <stdlib.h>
#include <stdio.h>

int part_one(FILE* input);
int part_two(FILE* input);

void main() {
    FILE* input;
    input = fopen("input.txt", "r");
    int one_result = part_one(input);
    rewind(input);
    int two_result = part_two(input);
    printf("Day one: %d\nDay Two: %d\n", one_result, two_result);
    fclose(input);
}

int part_one(FILE* input) {
    char buff[255];
    int max = 0;
    int elf = 0;
    while (fgets(buff, 255, input) != NULL) {
        int food = atoi(buff);
        if (food == 0) {
            if (max <= elf) {
                max = elf;
            }
            elf = 0;
        }
        else {
            elf += food;
        }
    }
    return max;
}

int part_two(FILE* input) {
    char buff[255];
    int top[3] = { -1, -1, -1 };
    int elf = 0;
    int i, j;
    while (fgets(buff, 255, input) != NULL) {
        int food = atoi(buff);
        if (food == 0) {
            for (i = 0; i < 3; i++) {
                if (top[i] < elf) {
                    for (j = 1; i <= j; j--) {
                        top[j + 1] = top[j];
                    }
                    top[i] = elf;
                    break;
                }
            }

            elf = 0;
        }
        else {
            elf += food;
        }
    }
    int sum = 0;
    for (i = 0; i < 3; i++) {
        sum += top[i];
        printf("%d %d\n", i, top[i]);
    }
    return sum;
}