use std::{collections::HashMap, fs::File, io::Read};

fn main() {
    let mut content = String::new();

    let _ = File::open("input.txt")
        .unwrap()
        .read_to_string(&mut content);

    let nums = content
        .lines()
        .enumerate()
        .map(|x| (x.1.parse::<i32>().unwrap(), x.0 as u32))
        .collect::<HashMap<i32, u32>>();

    println!(
        "One: {}\nTwo: {}",
        one(&nums, 2020).expect("No valid result for day 1"),
        two(&nums, 2020).expect("No valid result for day 2")
    );
}

fn one(nums: &HashMap<i32, u32>, desired: i32) -> Option<i32> {
    for i in nums.iter() {
        let compliment = desired - i.0;
        if nums.contains_key(&compliment) {
            return Some(i.0 * compliment);
        }
    }
    None
}

fn two(nums: &HashMap<i32, u32>, desired: i32) -> Option<i32> {
    for i in nums.iter() {
        for j in nums.iter() {
            let compliment = desired - i.0 - j.0;
            if nums.contains_key(&compliment) {
                return Some(i.0 * j.0 * compliment);
            }
        }
    }
    None
}
