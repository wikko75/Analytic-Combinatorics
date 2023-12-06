import Random
using Plots

"""
    fix(n::Vector{Int64}, reps::Int64)

Returns average number of fixed points in permutations (performed reps - times) of n::Vector{Int64}
"""
function fix(n::Vector{Int64}, reps::Int64)
    fixedPoints = 0
    for i in 1:reps
        shuffled = fisherYates(n)
        fixedPoints += fixedPointsCounter(shuffled)
    end
    return fixedPoints / reps
end


"""
    fixedPointsCounter(n::Vector{Int64})

Returns no. of fixed points in permutation of n::Vector{Int64}
"""
function fixedPointsCounter(n::Vector{Int64})
    fixedPoints = 0
    for (index, num) in enumerate(n) 
        fixedPoints += (index == num)
    end
    fixedPoints
end


"""
    fisherYates(n::Vector{Int64})
Shuffles copy of vector n (passed by value) using Fisher-Yates algorithm. Returns shuffled vector. Does not modify passed vector n.
"""
function fisherYates(n::Vector{Int64})
    l = length(n)
    N = n # do not modify passed vector
    for num in l:-1:1 
        randomNum = Random.rand(1:num)
        if randomNum != num
            i = findfirst(x -> x == num, N)
            j = findfirst(x -> x == randomNum, N)
            temp = N[i]
            N[i] = N[j]
            N[j] = temp
        end
    end
    return N
end


function test(maxN::Int64, step::Int64, reps::Int64)
    if maxN < 1
        println("maxN must be >= 1")
        return
    end
    if step < 1
        println("step must be >= 1")
        return
    end
    if reps < 1
        println("reps must be >= 1")
        return
    end

    avgFixedPoints = []
    for N in 1:step:maxN
        n = [i for i in 1:N]
        push!(avgFixedPoints, fix(n, reps))
    end
    println(avgFixedPoints)
    return avgFixedPoints
end



maxN = 100
step = 1
reps = 50000
avgFixedPoints = test(maxN, step, reps)

x = range(1, stop=maxN)

plot = scatter(x, avgFixedPoints, title="fix(n) for n in 1:100", legend=false)
ylims!(0.5, 1.5)
yticks!(0.5:0.1:1.5)
xlims!(0, maxN + 1)
xticks!(0:10:maxN)
xlabel!("n")
ylabel!("fixed points (avg)")
display(plot)
savefig(plot, "ex66/fix_n_avg.png")