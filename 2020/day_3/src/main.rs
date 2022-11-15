use std::{fs::File, io::Read};

fn main() {
    let mut content = String::new();
    let _ = File::open("input.txt")
        .unwrap()
        .read_to_string(&mut content);
    let lines = content.lines().map(|l| l).collect::<Vec<&str>>();
    let instructions = [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)];
    println!("One: {}\nTwo: {}", one(&lines), two(&lines, instructions));
}

fn one(lines: &Vec<&str>) -> u32 {
    let line_len = lines[0].len();
    let mut i = 0;
    let mut trees = 0;
    for line in lines {
        if line.chars().nth(i).unwrap() == '#' {
            trees += 1;
        }
        i += 3;
        if i >= line_len {
            i -= line_len;
        }
    }
    trees
}

fn two(lines: &Vec<&str>, instructions: [(usize, usize); 5]) -> u32 {
    let line_len = lines[0].len();
    let mut result = 1;
    for i in instructions {
        let height = lines.len();
        let mut y = 0;
        let mut x = 0;
        let mut trees = 0;
        while y < height {
            if lines[y].chars().nth(x).unwrap() == '#' {
                trees += 1
            }
            x += i.0;
            y += i.1;
            if x >= line_len {
                x -= line_len;
            }
        }
        result *= trees;
    }
    result
}
