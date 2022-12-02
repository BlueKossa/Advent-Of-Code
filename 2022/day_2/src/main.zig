const std = @import("std");
const data = @embedFile("./input.txt");

pub fn main() !void {
    var lines = tokenize(u8, data, "\n");
    var part_one_result = part_one(&lines);
    lines.reset();
    var part_two_result = part_two(&lines);
    print("Part one: {}\nPart two: {}\n", .{part_one_result, part_two_result});
}

pub fn part_one(lines: *std.mem.TokenIterator(u8)) i32 {
    var score: i32 = 0;
    while(lines.next()) |line| {
        var choices = split(u8, line, " ");
        var enemy_hand = hand(choices.next().?[0]);
        var my_hand = hand(choices.next().?[0]);

        var result: i8 = switch (abs(enemy_hand - my_hand)) {
            0 => 3,
            1 => if (my_hand > enemy_hand) 6 else 0,
            2 => if (my_hand > enemy_hand) 0 else 6,
            else => unreachable,
        };
        score += result + my_hand;
    }
    return score;
}

pub fn part_two(lines: *std.mem.TokenIterator(u8)) i32 {
    var score: i32 = 0;
    while(lines.next()) |line| {
        var choices = split(u8, line, " ");
        var enemy_hand = hand(choices.next().?[0]);
        var forced_result = get_result(choices.next().?[0]);

        var my_hand = pick_hand(enemy_hand, forced_result);

        score += forced_result + my_hand;
    }
    return score;
}

pub fn hand(choice: u8) i8 {
    return switch (choice) {
        'A', 'X' => 1,
        'B', 'Y' => 2,
        'C', 'Z' => 3,
        else => unreachable,
    };
}

pub fn get_result(choice: u8) i8 {
    return switch (choice) {
        'X' => 0,
        'Y' => 3,
        'Z' => 6,
        else => unreachable,
    };
}

pub fn pick_hand(enemy_hand: i8, forced_result: i8) i8 {
    return switch (forced_result) {
        0 => if (enemy_hand == 1) 3 else enemy_hand - 1,
        3 => enemy_hand,
        6 => if (enemy_hand == 3) 1 else enemy_hand + 1,
        else => unreachable,
    };
}

const print = std.debug.print;
const split = std.mem.split;
const max = std.math.max;
const abs = std.math.absCast;
const tokenize = std.mem.tokenize;

// NEVER USING THIS CRAP AGAIN!