local function sum_of_multiplications(file)
    local sum = 0
    for line in io.lines(file) do 
        for a,b in string.gmatch(line, "mul%((%d+),(%d+)%)") do
            sum =sum + a * b
        end
    end
    return sum
  end

print(sum_of_multiplications("input.txt"))