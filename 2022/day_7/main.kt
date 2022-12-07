import java.io.File

class Dir {
    var parent: List<String>
    var size: Int

    constructor(path: List<String>, size: Int) {
        this.parent = path
        this.size = size
    }
}

fun main() {
    val inputLines = File("input.txt").readLines()
    var filesystem: HashMap<List<String>, Dir> = HashMap()
    var currentPath: List<String> = listOf("/")
    var currentDir: Dir = Dir(currentPath.dropLast(1), 0)

    for (line in inputLines) {
        if (line.contains("$") || line == "") {
            if (line == "$ cd /" || line == "$ ls") {
                continue;
            }

            if (!filesystem.containsKey(currentPath)) {
                filesystem.put(currentPath, currentDir)
                var path = currentDir.parent
                while (path.isNotEmpty()) {
                    filesystem.get(path)!!.size += currentDir.size
                    path = path.dropLast(1)
                }
            } if (line == "") continue;

            val dir = line.split(" ")[2]
            if (dir == "..") {
                currentPath = currentPath.dropLast(1)
            } else {
                currentDir = Dir(currentPath, 0)
                currentPath = currentPath + dir
            }
            continue;
        }
        val args = line.split(" ")
        if (args[0] != "dir") {
            currentDir.size += args[0].toInt()
        }
    }
    
    val totalSpace = 70000000
    val desiredSpace = 30000000
    val usedSpace = filesystem.get(listOf("/"))!!.size
    val freeSpace = totalSpace - usedSpace
    val requiredSpace = desiredSpace - freeSpace

    var optimalDir = usedSpace
    var total = 0
    for (dir in filesystem) {
        val size = dir.value.size
        if (size <= 100000) {
            total += size
        }
        if (size >= requiredSpace && size < optimalDir) {
            optimalDir = size
        }
    }
    println("Day 1: ${total}\nDay 2: ${optimalDir}")
}