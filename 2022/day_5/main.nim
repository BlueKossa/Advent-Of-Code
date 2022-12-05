import strutils, tables, algorithm, system


proc moveCrates(stacks: var Table[system.int, seq[char]], instructions: seq[string], partTwo: bool): string

proc main(): void = 
    let file = open("input.prod", fmRead)
    var input = readAll(file).replace("\r", "").split("\n\n")
    close(file) 
    var startLines = input[0].splitLines()
    let instructions = input[1].splitLines()

    var stacks: Table[int, seq[char]]

    for line in startLines.reversed():
        var j = 1
        while j < line.len():
            let c = line[j]
            if c.isAlphaNumeric():
                let index = int((j + 3)/4)
                if stacks.hasKey(index):
                    stacks[index].add(c)
                else:
                    stacks[index] = @[c]
            j += 4
    
    var copy = stacks
    let partOneResult = moveCrates(copy, instructions, false)
    let partTwoResult = moveCrates(stacks, instructions, true)
    echo("Part one: ", partOneResult, "\nPart two: ", partTwoResult)

proc moveCrates(stacks: var Table[system.int, seq[char]], instructions: seq[string], partTwo: bool): string = 
    for instruction in instructions:
        let keys = instruction.split(" ")
        let moveCount = parseInt(keys[1])
        let fromIndex = parseInt(keys[3])
        let toIndex = parseInt(keys[5])
        var craneBuffer: seq[char]
        for _ in 0 ..< moveCount:
            let c = stacks[fromIndex].pop()
            craneBuffer.add(c)
        if partTwo:
            craneBuffer = craneBuffer.reversed()
        for c in craneBuffer:
            stacks[toIndex].add(c)

    var r = ""
    for i in 1..stacks.len():
        r.add(stacks[i].reversed()[0])
    return r

main()
