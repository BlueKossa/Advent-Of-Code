#include <stdio.h>
#include "../../utils/utils.c"

struct Number {
    int span_start;
    int span_end;
    int line;
};

struct Gear {
    int x;
    int y;
};

int in_span(struct Number* number, int line, int column) {
    int same_row = number->line == line;
    int same_column = number->span_start <= column && number->span_end >= column;
    return same_row && same_column;
}

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

int is_symbol(char c) {
    return c != '.' && c != '\n' && c != '\0';
}

int get_line_length(char* input) {
    int length = 0;
    while (1) {
        char c = input[length];
        if (c == '\n') {
            // Compensate for newline characters
            return length + 1;
        }
        length++;
    }
}

int* solve(char* input) {
    int line = 0;
    int span_start = -1;
    int span_end = -1;

    int line_length = get_line_length(input);
    int length = strlen(input);
    int line_height = length / line_length;

    Vec* numbers = vec_new(sizeof(struct Number));
    Vec* gears = vec_new(sizeof(struct Gear));

    for (int i = 0; i < length; i++) {
        char c = input[i];
        if (is_digit(c)) {
            if (span_start == -1) {
                span_start = i;
            }
            span_end = i;
        } else {
            if (span_start != -1) {
                struct Number number = {span_start % line_length, span_end % line_length, line};
                vec_push(numbers, &number);
                span_start = -1;
                span_end = -1;
            }
            if (c == '\n') {
                line++;
            }
            if (c == '*') {
                struct Gear gear = {i % line_length, line};
                vec_push(gears, &gear);
            }
        }
    }
    if (span_start != -1) {
        struct Number number = {span_start % line_length, span_end % line_length, line};
        vec_push(numbers, &number);
    }
    int sum = 0;
    for (int i = 0; i < numbers->length; i++) {
        int valid = 0;
        struct Number number;
        vec_get(numbers, i, &number);
        int line = number.line;
        int span_start = number.span_start;
        int span_end = number.span_end;
        for (int j = span_start; j <= span_end; j++) {
            if (valid) {
                break;
            }
            for (int x_offset = -1; x_offset <= 1; x_offset++) {
                if (valid) {
                    break;
                }
                int x = j + x_offset;
                if (x < 0 || x >= line_length) {
                    continue;
                }
                for (int y_offset = -1; y_offset <= 1; y_offset++) {
                    if (y_offset == 0 && x_offset == 0) {
                        continue;
                    }
                    int y = line + y_offset;
                    if (y < 0 || y >= line_height || in_span(&number, y, x)) {
                        continue;
                    }
                    char c = input[y * line_length + x];
                    if (is_symbol(c)) {
                        char* line_start = input + line * line_length + span_start;
                        int number = atoi(line_start);
                        sum += number;
                        valid = 1;
                        break;
                    }
                }
            }
        }
    }
    // Part two
    int gear_sum = 0;
    for (int i = 0; i < gears->length; i++) {
        struct Gear gear;
        vec_get(gears, i, &gear);
        int x = gear.x;
        int y = gear.y;
        int nearby_numbers = 0;
        int number_sum = 1;
        for (int j = 0; j < numbers->length; j++) {
            int touches = 0;
            struct Number number;
            vec_get(numbers, j, &number);
            for (int x_offset = -1; x_offset <= 1; x_offset++) {
                if (touches) {
                    break;
                }
                int x2 = x + x_offset;
                if (x2 < 0 || x2 >= line_length) {
                    continue;
                }
                for (int y_offset = -1; y_offset <= 1; y_offset++) {
                    int y2 = y + y_offset;
                    if (y2 < 0 || y2 >= line_height) {
                        continue;
                    }
                    if (in_span(&number, y2, x2)) {
                        nearby_numbers++;
                        char* line_start = input + number.line * line_length + number.span_start;
                        int number = atoi(line_start);
                        touches = 1;
                        number_sum *= number;
                    }
                }
            }
        }
        if (nearby_numbers == 2) {
            gear_sum += number_sum;
        }

    }
    vec_free(numbers);
    vec_free(gears);
    int* result = malloc(sizeof(int) * 2);
    result[0] = sum;
    result[1] = gear_sum;
    return result;
}

int main() {
    char* input = read_file("input.txt");
    int* result = solve(input);
    printf("Part 1: %d\n", result[0]);
    printf("Part 2: %d\n", result[1]);
    return 0;
}
