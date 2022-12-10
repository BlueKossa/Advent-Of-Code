#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100000000

typedef struct {
    int x;
    int y;
} coordinate;

int rope(FILE* input, int len);
int signum(int x);
unsigned int hash(coordinate* c);
void init_hash_set();
bool insert(coordinate* c);

coordinate* hash_set[HASH_SIZE];

int visited = 0;

unsigned int hash(coordinate* c)
{
    unsigned int result = 0;
    unsigned int a = 63689;
    unsigned int b = 378551;
    result = result * a + c->x;
    a = a * b;
    result = result * a + c->y;
    unsigned int hash = result % HASH_SIZE;
    return hash;
}

void init_hash_set()
{
    visited = 0;
    for (int i = 0; i < HASH_SIZE; i++)
    {
        hash_set[i] = NULL;
    }
}

bool insert(coordinate* c) {
    if (c == NULL) return false;
    unsigned int h = hash(c);
    if (hash_set[h] != NULL) {
        return false;
    }
    visited += 1;
    hash_set[h] = c;
    return true;
}

int rope(FILE* input, int len) {
    char buffer[100];
    init_hash_set();
    coordinate* rope;
    rope = malloc(sizeof(coordinate) * len);
    for (int i = 0; i < len; i++)
    {
        rope[i] = (coordinate){ 0, 0 };
    }
    while (fgets(buffer, 100, input) != NULL)
    {
        char* token = strtok(buffer, "");
        char direction = token[0];
        int distance = atoi(token + 1);
        insert(&rope[len - 1]);
        for (int i = 0; i < distance; i++)
        {
            switch (direction)
            {
            case 'R':
                rope[0].x += 1;
                break;
            case 'L':
                rope[0].x -= 1;
                break;
            case 'U':
                rope[0].y += 1;
                break;
            case 'D':
                rope[0].y -= 1;
                break;
            }
            for (int i = 1; i < len; i++)
            {
                coordinate distance_from = (coordinate){ rope[i - 1].x - rope[i].x, rope[i - 1].y - rope[i].y };
                if (!(abs(distance_from.x) > 1 || abs(distance_from.y) > 1))
                {
                    break;
                }
                rope[i].x += signum(distance_from.x);
                rope[i].y += signum(distance_from.y);
                if (i == len - 1)
                {
                    insert(&rope[i]);
                }
            }
        }
    }
    free(rope);
    int result = visited;
    return result;
}

int signum(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

int main(int argc, char* argv[])
{
    FILE* input;
    input = fopen("input.txt", "r");
    int part_one = rope(input, 2);
    rewind(input);
    int part_two = rope(input, 10);
    printf("Part 1: %d\nPart 2: %d", part_one, part_two);
}

