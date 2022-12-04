import java.io.File

fun main() {
    val inputLines = File("input.txt").readLines()
    var partOneSum = 0
    var partTwoSum = 0
    for (line in inputLines) {
        val (a, b) = line.split(",").map {
                    val i = it.split("-").map { it.toInt() }
                    (i[0]..i[1]).toHashSet()
                }

        var commonHashSet = a + b
        if (commonHashSet.size == a.size || commonHashSet.size == b.size) {
            partOneSum += 1
        }
        if (commonHashSet.size != a.size + b.size) {
            partTwoSum += 1
        }
    }
    println("Part one: $partOneSum\nPart two: $partTwoSum")
}
