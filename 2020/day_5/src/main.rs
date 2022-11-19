use std::{collections::HashMap, fs::File, io::Read, str::Chars};

fn main() {
    let mut content = String::new();
    let _ = File::open("input.txt")
        .unwrap()
        .read_to_string(&mut content);
    let seats = content.lines().map(|l| l).collect::<Vec<&str>>();
    println!("One: {:?}\nTwo: {}", one(&seats), two(&seats));
}

fn one(seats: &Vec<&str>) -> i32 {
    let mut highest = 0;
    for seat in seats {
        let mut instructions = seat.chars();
        let row = find_seat(&mut instructions, 7, 127);
        let col = find_seat(&mut instructions, 3, 7);
        let id = row * 8 + col;
        if id > highest {
            highest = id;
        }
    }
    return highest;
}

fn two(seats: &Vec<&str>) -> i32 {
    let mut seat_ids = HashMap::new();
    for seat in seats {
        let mut instructions = seat.chars();
        let row = find_seat(&mut instructions, 7, 127);
        if row != 0 && row != 127 {
            let col = find_seat(&mut instructions, 3, 7);
            let id = row * 8 + col;
            seat_ids.insert(id, id);
        }
    }
    for i in 0..1024 {
        if seat_ids.contains_key(&(i + 1))
            && seat_ids.contains_key(&(i - 1))
            && !seat_ids.contains_key(&i)
        {
            return i;
        }
    }
    return 0;
}

fn find_seat(instructions: &mut Chars, len: u8, width: i32) -> i32 {
    let mut interval = (0, width);
    for _ in 0..len {
        match instructions.next().unwrap() {
            'F' | 'L' => interval = (interval.0, (interval.0 + interval.1) / 2),
            'B' | 'R' => {
                interval = (
                    (interval.1 as f32 / 2.0).ceil() as i32 + interval.0 / 2,
                    interval.1,
                )
            }
            _ => panic!("Invalid input!"),
        }
    }
    return interval.0;
}
