# Where my Rust enums at :(
struct Data
    property data : Array(Int32 | Data)
    
    def initialize(data : Int32 | Data | Nil = nil)
        @data = Array(Int32 | Data).new
        @data << data if data
    end
end

def parse(iterator) : Data
    list = Data.new()
    num = ""
    iterator.each do |c|
        case c
        when '['
            list.data << parse(iterator)
        when ']'
            if num != ""
                list.data << num.to_i 
            end
            break
        when ','
            if num != ""
                list.data << num.to_i
                num = ""
            end
        else
            num += c.to_s
        end
    end
    return list
end

def compare(lhs : Data | Int32, rhs : Data | Int32) : Int32
    case {lhs, rhs}
    when {Int32, Int32}
        return rhs <=> lhs
    when {Data, Int32}
        return compare(lhs, Data.new(rhs))
    when {Int32, Data}
        return compare(Data.new(lhs), rhs)
    when {Data, Data}
        lhs.data.each_with_index do |value, index|
            if rhs.data[index]?
                result = compare(value, rhs.data[index])
                if result != 0
                    return result
                end
            else
                break
            end
        end
        return rhs.data.size <=> lhs.data.size
    end
    return 0
end

def part1(packets : Array(Data)) : Int32
    result = 0
    packets.each_slice(2).each_with_index do |pair, index|
        result += (index + 1) if compare(pair[0], pair[1]) > 0
    end
    return result
end

def part2(packets : Array(Data)) : Int32
    result = 1
    new_packets = [Data.new(Data.new(2)), Data.new(Data.new(6))]
    packets.concat(new_packets)
    sorted = packets.sort! { |a, b| compare(b, a) }
    sorted.each_with_index do |packet, index|
        if packet == new_packets[0] || packet == new_packets[1]
            result *= index + 1
        end
    end
    return result
end

def main()
    input = File.read("input")
    packets = input.split("\n").reject { |line| line.empty? }.map { |line| parse(line.chars.each) }
    puts "Part 1: #{part1(packets)}\nPart 2: #{part2(packets)}"
end

main

