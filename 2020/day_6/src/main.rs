use std::{
    collections::{hash_map::Entry, HashMap},
    fs::File,
    io::Read,
};

fn main() {
    let mut content = String::new();
    let _ = File::open("input.txt")
        .unwrap()
        .read_to_string(&mut content);
    let groups = content
        .split("\r\n\r\n")
        .map(|s| {
            s.to_string()
                .replace("\r\n", " ")
                .trim()
                .split(" ")
                .map(str::to_string)
                .collect::<Vec<String>>()
        })
        .collect::<Vec<Vec<String>>>();
    println!("One: {}\nTwo: {}", one(&groups), two(&groups));
}

fn one(groups: &Vec<Vec<String>>) -> usize {
    let mut result = 0;
    for group in groups {
        let mut yes_questions = HashMap::new();
        for member in group {
            for question in member.chars() {
                yes_questions.insert(question, true);
            }
        }
        result += yes_questions.len();
    }
    result
}

fn two(groups: &Vec<Vec<String>>) -> usize {
    let mut result = 0;
    for group in groups {
        let mut yes_questions = HashMap::new();
        for member in group {
            for question in member.chars() {
                match yes_questions.entry(question) {
                    Entry::Vacant(_) => {
                        yes_questions.insert(question, 1);
                    }
                    Entry::Occupied(mut e) => {
                        *e.get_mut() += 1;
                    }
                }
            }
        }
        for answer in group[0].chars() {
            if yes_questions.get(&answer).unwrap() == &group.len() {
                result += 1;
            }
        }
    }
    result
}
