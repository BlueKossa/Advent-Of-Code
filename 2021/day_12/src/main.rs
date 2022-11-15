#![feature(map_try_insert)]

use std::{
    collections::{hash_map::Entry, HashMap},
    fs::File,
    io::Read,
};

// TODO: remove large bool
#[derive(Debug)]
struct Cave {
    neighbors: Vec<String>,
    large: bool,
}

fn main() {
    let mut content = String::new();
    let _ = File::open("input.txt")
        .unwrap()
        .read_to_string(&mut content);
    let mut caves = HashMap::new();
    for line in content.lines() {
        add_neighbors(&mut caves, line)
    }
    println!("{:?}", caves.get("start").unwrap());
    let mut paths = 0;
    let mut small_visited = HashMap::new();
    let start_cave = caves.get("start").unwrap();
    find_path(start_cave, small_visited, &mut paths, &caves);
    println!("{paths}");
}

fn find_path(
    cave: &Cave,
    small_visited: HashMap<String, bool>,
    paths: &mut u32,
    caves: &HashMap<String, Cave>,
) {
    /* println!("{:?}", cave); */

    for c in &cave.neighbors {
        // TODO: Remove clone
        let mut scoped_visited: HashMap<String, bool> = small_visited.clone();
        match c.as_str() {
            "end" => {
                /* println!("Ended!"); */
                /* println!("{scoped_visited:?}"); */
                *paths += 1;
                continue;
            }
            _ if scoped_visited.contains_key(c) || c == "start" => {
                /* println!("Got stuck on {c}"); */
                continue;
            }
            _ => {
                /* println!("{c}"); */
                let new_cave = caves.get(c).unwrap();
                /*                 if c.chars().next().unwrap().is_lowercase() {
                    scoped_visited.insert(c.to_string(), true);
                } */
                scoped_visited.insert(c.to_string().to_lowercase(), true);
                find_path(new_cave, scoped_visited, paths, caves);
            }
        }
    }
}

fn add_neighbors(caves: &mut HashMap<String, Cave>, pairs: &str) {
    let keys = pairs.split("-").map(|k| k).collect::<Vec<&str>>();
    let mut iter: (usize, usize) = (0, 1);
    for _ in 0..2 {
        match caves.entry(keys[iter.0].to_string()) {
            Entry::Vacant(e) => {
                let large: bool;
                if keys[iter.0].chars().next().unwrap().is_uppercase() {
                    large = true;
                } else {
                    large = false;
                }
                e.insert(Cave {
                    neighbors: Vec::<String>::from([keys[iter.1].to_string()]),
                    large,
                });
            }
            Entry::Occupied(mut e) => {
                e.get_mut().neighbors.push(keys[iter.1].to_string());
            }
        }
        iter = (1, 0);
    }
}
