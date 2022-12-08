local function main()
    local file = assert(io.open("test.txt", "r"))
    local trees = {}
    local y = 1
    for line in file:lines() do
        trees[y] = {}
        local x = 1
        for i = 1, #line do
            trees[y][i] = line:sub(i, i)
            x = x + 1
        end
        y = y + 1
    end
    file:close()

    local max_score = 0
    local bad_trees = 0

    for line = 1, #trees do
        for tree = 1, #trees[line] do
            if line == 1 or line == #trees or tree == 1 or tree == #trees[line] then
                bad_trees = bad_trees + 1
                goto continue
            end
            local height = trees[line][tree]
            local tree_reach = {
                ["top"] = { ["reach"] = line - 1, ["visible"] = true },
                ["bottom"] = { ["reach"] = #trees - line, ["visible"] = true },
                ["left"] = { ["reach"] = tree - 1, ["visible"] = true },
                ["right"] = { ["reach"] = #trees[line] - tree, ["visible"] = true }
            }

            local direction = { -1, "left", 1 } -- Increment, direction, endpoint
            ::leftright::
            for i = tree + direction[1], direction[3], direction[1] do
                if trees[line][i] >= height then
                    tree_reach[direction[2]] = { ["reach"] = direction[1] * (-1) * (tree - i), ["visible"] = false }
                    break
                end
            end
            if direction[1] == -1 then direction = { 1, "right", #trees[line] } goto leftright end

            direction = { -1, "top", 1 } -- Increment, direction, endpoint
            ::updown::
            for i = line + direction[1], direction[3], direction[1] do
                if trees[i][tree] >= height then
                    tree_reach[direction[2]] = { ["reach"] = direction[1] * (-1) * (line - i), ["visible"] = false }
                    break
                end
            end
            if direction[1] == -1 then direction = { 1, "bottom", #trees } goto updown end

            local score = tree_reach["top"]["reach"] * tree_reach["bottom"]["reach"] * tree_reach["left"]["reach"] *
                tree_reach["right"]["reach"
                ]
            if score > max_score then
                max_score = score
            end
            if tree_reach["top"]["visible"] or tree_reach["bottom"]["visible"] or tree_reach["left"]["visible"] or
                tree_reach["right"]["visible"] then
                bad_trees = bad_trees + 1
            end
            ::continue::
        end
    end

    print("Part 1: " .. bad_trees, "\nPart 2: " .. max_score)
end

main()
-- Super unhappy about this one :/
