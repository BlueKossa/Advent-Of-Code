use std::{fs::File, io::Read};

struct Passport {
    birth_year: Option<i32>,
    issue_year: Option<i32>,
    expiration_year: Option<i32>,
    height: Option<Height>,
    hair_color: Option<String>,
    eye_color: Option<String>,
    id: Option<String>,
    country_id: Option<String>,
}

enum HeightType {
    Inches,
    Cm,
}

struct Height {
    measurement: HeightType,
    value: i32,
}

fn create_height(str: &str) -> Option<Height> {
    if str.contains("in") {
        let x: &[_] = &['i', 'n'];
        let value = str.trim_end_matches(x).parse::<i32>().unwrap();
        return Some(Height {
            measurement: HeightType::Inches,
            value,
        });
    } else if str.contains("cm") {
        let x: &[_] = &['c', 'm'];
        let value = str.trim_matches(x).parse::<i32>().unwrap();
        return Some(Height {
            measurement: HeightType::Cm,
            value,
        });
    }
    None
}

impl Default for Passport {
    fn default() -> Self {
        Passport {
            birth_year: None,
            issue_year: None,
            expiration_year: None,
            height: None,
            hair_color: None,
            eye_color: None,
            id: None,
            country_id: None,
        }
    }
}

impl Passport {
    fn is_valid(&self) -> bool {
        fn birth_year_valid(year: Option<i32>) -> bool {
            match year {
                Some(year) => {
                    if 1920 <= year && year <= 2002 {
                        return true;
                    }
                    false
                }
                None => false,
            }
        }

        fn issue_year_valid(year: Option<i32>) -> bool {
            match year {
                Some(year) => {
                    if 2010 <= year && year <= 2020 {
                        return true;
                    }
                    false
                }
                None => false,
            }
        }

        fn expiration_year_valid(year: Option<i32>) -> bool {
            match year {
                Some(year) => {
                    if 2020 <= year && year <= 2030 {
                        return true;
                    }
                    false
                }
                None => false,
            }
        }

        fn height_valid(height: &Option<Height>) -> bool {
            match height {
                Some(height) => match height.measurement {
                    HeightType::Inches => {
                        if 59 <= height.value && height.value <= 76 {
                            return true;
                        } else {
                            return false;
                        }
                    }
                    HeightType::Cm => {
                        if 150 <= height.value && height.value <= 193 {
                            return true;
                        } else {
                            return false;
                        }
                    }
                },
                None => false,
            }
        }

        fn hair_color_valid(color: &Option<String>) -> bool {
            match color {
                Some(color) => {
                    if color.contains("#") && color.len() == 7 {
                        for char in color.chars() {
                            if !char.is_ascii_hexdigit() {
                                break;
                            }
                        }
                        return true;
                    }
                    false
                }
                None => false,
            }
        }

        fn eye_color_valid(color: &Option<String>) -> bool {
            match color {
                Some(color) => match color.as_str() {
                    "amb" | "blu" | "brn" | "gry" | "grn" | "hzl" | "oth" => return true,
                    _ => return false,
                },
                None => false,
            }
        }

        fn id_valid(number: &Option<String>) -> bool {
            match number {
                Some(number) => {
                    if number.len() == 9 {
                        for char in number.chars() {
                            if !char.is_numeric() {
                                break;
                            }
                        }
                        return true;
                    }
                    false
                }
                None => false,
            }
        }

        if birth_year_valid(self.birth_year)
            && issue_year_valid(self.issue_year)
            && expiration_year_valid(self.expiration_year)
            && height_valid(&self.height)
            && hair_color_valid(&self.hair_color)
            && eye_color_valid(&self.eye_color)
            && id_valid(&self.id)
        {
            return true;
        }
        false
    }
}
fn main() {
    let mut content = String::new();
    let _ = File::open("input.txt")
        .unwrap()
        .read_to_string(&mut content);
    let passports = content
        .split("\r\n\r\n")
        .map(|s| s.replace("\r\n", " "))
        .collect::<Vec<String>>();

    println!("One: {}\nTwo: {}", one(&passports), two(&passports));
}

fn one(passports: &Vec<String>) -> i32 {
    let mut valid = 0;
    for passport in passports {
        if passport.contains("byr")
            && passport.contains("iyr")
            && passport.contains("eyr")
            && passport.contains("hgt")
            && passport.contains("hcl")
            && passport.contains("ecl")
            && passport.contains("pid")
        {
            valid += 1;
        }
    }
    valid
}

fn two(passports: &Vec<String>) -> i32 {
    let mut valid = 0;
    for passport in passports {
        let mut pp = Passport::default();
        let fields = passport.split(" ").collect::<Vec<&str>>();
        for field in fields {
            let field_split = field.split(":").collect::<Vec<&str>>();
            match field_split[0] {
                "byr" => pp.birth_year = Some(field_split[1].parse::<i32>().unwrap()),
                "iyr" => pp.issue_year = Some(field_split[1].parse::<i32>().unwrap()),
                "eyr" => pp.expiration_year = Some(field_split[1].parse::<i32>().unwrap()),
                "hgt" => pp.height = create_height(field_split[1]),
                "hcl" => pp.hair_color = Some(field_split[1].to_string()),
                "ecl" => pp.eye_color = Some(field_split[1].to_string()),
                "pid" => pp.id = Some(field_split[1].to_string()),
                "cid" => pp.country_id = Some(field_split[1].to_string()),
                _ => {}
            }
        }
        if pp.is_valid() {
            valid += 1;
        }
    }
    valid
}
