local function sum_of_multiplications(file)
    local sum = 0
    for line in io.lines(file) do
        for a, b in string.gmatch(line, "mul%((%d+),(%d+)%)") do
            sum = sum + a * b
        end
    end
    return sum
end

local function sum_of_multiplications_part2(file)
    local sum = 0
    local enabled = true
    for line in io.lines(file) do
        local sub = line
        while sub ~= nil do
            local start_mul, end_mul, a, b = string.find(sub, "mul%((%d+),(%d+)%)")
            local start_do, end_do = string.find(sub, "do%(%)")
            local start_dont, end_dont = string.find(sub, "don't%(%)")

            if enabled then
                if start_mul ~= nil and start_dont == nil or start_mul ~= nil and start_dont ~= nil and start_mul < start_dont then
                    if start_mul ~= nil then
                        sum = sum + a * b
                        sub = string.sub(sub, end_mul)
                    else
                        sub = nil
                    end
                else
                    if start_dont ~= nil then
                        enabled = false
                        sub = string.sub(sub, end_dont)
                    else
                        sub = nil
                    end
                end
            else
                if start_do ~= nil then
                    enabled = true
                    sub = string.sub(sub, end_do)
                else
                    sub = nil
                end
            end
        end
    end
    return sum
end

print(sum_of_multiplications_part2("input.txt"))
