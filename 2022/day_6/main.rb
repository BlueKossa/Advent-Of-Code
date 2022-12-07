require 'set'

def get_marker(len, input)
    buffer = []
    for i in len-1..input.length do
        buffer.push(input[i])
        if buffer.length > len
            buffer.shift
        end
        if Set.new(buffer).length == len
            return i + 1
        end
    end
end

file = File.open('input.txt')
input = file.read
file.close

puts("Day 1: #{get_marker(4, input)}\nDay 2: #{get_marker(14, input)}")