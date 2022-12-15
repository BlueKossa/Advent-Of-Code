#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct monkey {
    int* items;
    int item_count;
    char operation[3][3];
    int test;
    int if_true;
    int if_false;
    int inspections;
};

int get_items(char line[255], int* items) {
    char* token;
    token = strtok(line + 18, ", ");
    int i = 0;
    while (token != NULL) {
        items = realloc(items, sizeof(int) * (i + 1));
        items[i] = atoi(token);
        token = strtok(NULL, ", ");
        i++;
    }
    return i;
}

void get_operation(char line[255], char operation[3][3]) {
    char* token;
    token = strtok(line + 19, " ");
    int i = 0;
    while (token != NULL) {
        strcpy(operation[i], token);
        token = strtok(NULL, " ");
        i++;
    }
}

int get_worry_level(int item, char operation[3][3], int lcm) {
    unsigned long long int values[2];
    int i = 0;
    int j = 0;
    while (i < 2) {
        if (operation[j][0] == 'o') {
            values[i] = item;
        }
        else {
            values[i] = atoi(operation[j]);
        }
        i++;
        j += 2;
    }

    switch (operation[1][0]) {
    case '+': {
        if (lcm == 0) {
            return (values[0] + values[1]) / 3;
        }
        else {
            return (values[0] + values[1]) % lcm;
        }
    }
    case '*': {
        if (lcm == 0) {
            return (values[0] * values[1]) / 3;
        }
        else {
            return (values[0] * values[1]) % lcm;
        }
    }
    }
}

unsigned long long int both_parts(struct monkey* monkeys_original, int monkeys_count, bool part_two) {
    struct monkey* monkeys = (struct monkey*)malloc(monkeys_count * sizeof(struct monkey));
    for (int i = 0; i < monkeys_count; i++) {
        monkeys[i] = monkeys_original[i];
        monkeys[i].items = (int*)malloc(monkeys[i].item_count * sizeof(int));
        for (int j = 0; j < monkeys[i].item_count; j++) {
            monkeys[i].items[j] = monkeys_original[i].items[j];
        }
    }
    int rounds;
    int lcm;
    if (part_two) {
        rounds = 10000;
        lcm = 1;
        for (int i = 0; i < monkeys_count; i++) {
            lcm *= monkeys[i].test;
        }
    }
    else {
        rounds = 20;
        lcm = 0;
    }

    for (int i = 1; i <= rounds; i++) {
        for (int monkey_index = 0; monkey_index < monkeys_count; monkey_index++) {
            struct monkey monkey = monkeys[monkey_index];
            int items_count = monkey.item_count;
            for (int item_index = 0; item_index < items_count; item_index++) {
                int item = monkey.items[item_index];
                int worry_level = get_worry_level(item, monkey.operation, lcm);
                int pass_monkey;
                if (worry_level % monkey.test == 0) {
                    pass_monkey = monkey.if_true;
                }
                else {
                    pass_monkey = monkey.if_false;
                }
                monkeys[pass_monkey].item_count += 1;
                monkeys[pass_monkey].items = realloc(monkeys[pass_monkey].items, (monkeys[pass_monkey].item_count) * sizeof(int));
                int item_index = monkeys[pass_monkey].item_count - 1;
                monkeys[pass_monkey].items[item_index] = worry_level;

                monkeys[monkey_index].inspections += 1;
            }
            monkeys[monkey_index].items = memset(monkeys[monkey_index].items, 0, 2);
            monkeys[monkey_index].item_count = 0;
        }
    }
    unsigned long long int top_two[2] = { 0, 0 };
    for (int i = 0; i < monkeys_count; i++) {
        int inspections = monkeys[i].inspections;
        if (inspections > top_two[0]) {
            top_two[1] = top_two[0];
            top_two[0] = inspections;
        }
        else if (inspections > top_two[1]) {
            top_two[1] = inspections;
        }
    }
    unsigned long long int result = top_two[0] * top_two[1];
    free(monkeys);
    return result;
}

int main() {
    FILE* input = fopen("input.txt", "r");
    char buff[255];

    struct monkey* monkeys;
    monkeys = malloc(sizeof(struct monkey));
    int line = 0;
    int monkeys_count = 0;
    while (fgets(buff, 255, input) != NULL) {
        switch (line % 7) {
        case 0: {
            monkeys = realloc(monkeys, (line / 7 + 1) * sizeof(struct monkey));
            monkeys_count++;
            monkeys[line / 7].inspections = 0;
            break;
        }
        case 1: {
            int* items;
            items = malloc(sizeof(int));
            int item_count = get_items(buff, items);
            monkeys[line / 7].items = items;
            monkeys[line / 7].item_count = item_count;
            break;
        }
        case 2: {
            char operation[3][3];
            get_operation(buff, operation);
            for (int i = 0; i < 3; i++) {
                strcpy(monkeys[line / 7].operation[i], operation[i]);
            }
            break;
        }
        case 3: {
            monkeys[line / 7].test = atoi(buff + 21);
            break;
        }
        case 4: {
            monkeys[line / 7].if_true = atoi(buff + 29);
            break;
        }
        case 5: {
            monkeys[line / 7].if_false = atoi(buff + 30);
            break;
        }
        }
        line++;
    }
    unsigned long long int part_one = both_parts(monkeys, monkeys_count, false);
    unsigned long long int part_two = both_parts(monkeys, monkeys_count, true);
    free(monkeys);
    printf("Part 1: %d\nPart 2: %llu", part_one, part_two);
    return 0;
}