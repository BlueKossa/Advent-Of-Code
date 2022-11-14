use std::{fs::File, io::Read};

fn main() {
    let mut content = String::new();
    let _ = File::open("input.txt")
        .unwrap()
        .read_to_string(&mut content);
    let lines = content.lines().map(|l| l).collect::<Vec<&str>>();
    println!("Day One: {}\nDay Two: {}", one(&lines), two(&lines));
}

fn one(lines: &Vec<&str>) -> u16 {
    let mut valid = 0;
    for line in lines {
        let info = line.split_whitespace().collect::<Vec<&str>>();
        let min_max = info[0]
            .split('-')
            .map(|n| n.parse::<usize>().unwrap())
            .collect::<Vec<usize>>();
        let desired_char = info[1].chars().next().unwrap();
        let password = info[2];
        let count = password.matches(desired_char).count();
        if count >= min_max[0] && count <= min_max[1] {
            valid += 1;
        }
    }
    valid
}

fn two(lines: &Vec<&str>) -> u16 {
    let mut valid = 0;
    for line in lines {
        let info = line.split_whitespace().collect::<Vec<&str>>();
        let pwd_i = info[0]
            .split('-')
            .map(|n| n.parse::<usize>().unwrap())
            .collect::<Vec<usize>>();
        let desired_char = info[1].chars().next().unwrap();
        let mut password = info[2].chars();
        if (password.nth(pwd_i[0] - 1).unwrap() == desired_char)
            ^ (password.nth(pwd_i[1] - pwd_i[0] - 1).unwrap() == desired_char)
        {
            valid += 1;
        }
    }
    valid
}
