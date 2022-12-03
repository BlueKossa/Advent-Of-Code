package main

import (
	"fmt"
	"os"
	"strings"
	"unicode"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func main() {
	dat, err := os.ReadFile("input.txt")
	check(err)
	fmt.Println("Part one: ", part_one(dat), "Part two: ", part_two(dat))
}

func part_one(dat []byte) int {
	lines := strings.Split(string(dat), "\n")
	sum := 0
	for _, line := range lines {
		x, y := line[0:len(line)/2], line[len(line)/2:]
		for _, char := range x {
			if strings.Contains(y, string(char)) {
				sum += convert(char)
				break
			}
		}
	}
	return sum
}

func part_two(dat []byte) int {
	lines := strings.Split(string(dat), "\n")
	sum := 0
	for i := 0; i < len(lines); i += 3 {
		x, y, z := lines[i], lines[i+1], lines[i+2]
		for _, char := range x {
			if strings.Contains(y, string(char)) && strings.Contains(z, string(char)) {
				sum += convert(char)
				break
			}
		}
	}
	return sum
}

func convert(s rune) int {
	if unicode.IsUpper(s) {
		return int(s) - 38
	} else {
		return int(s) - 96
	}
}
