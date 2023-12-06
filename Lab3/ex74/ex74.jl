using LinearAlgebra
using Plots
using LaTeXStrings

function draw_S_r(f, g, rRange, tRange)
    x = []
    y = []
    z = []
    for r in rRange
        for t in tRange 
            push!(x, real(f(r,t)))
            push!(y, imag(f(r,t)))
            push!(z, real(g(r,t)))
        end
    end
    plt = plot3d(x, y, z, title = "Area of " * L"S_r", legend = false, color = "blue")
    xlabel!(L"x")
    ylabel!(L"y")
    zlabel!(L"z")
    savefig(plt, "lab3/ex74/S_r_plot.png")
end



function draw_S_c(f, g, rRange, tRange)
    x = []
    y = []
    z = []
    for r in rRange
        for t in tRange 
            push!(x, real(f(r,t)))
            push!(y, imag(f(r,t)))
            push!(z, imag(g(r,t)))
        end
    end
    plt = plot3d(x, y, z, title = "Area of " * L"S_c", legend = false, color = "red")
    xlabel!(L"x")
    ylabel!(L"y")
    zlabel!(L"z")
    savefig(plt, "lab3/ex74/S_c_plot.png")
end

function draw_L(f, h, rRange, tRange)
    x = []
    y = []
    z = []
    for r in rRange
        for t in tRange 
            push!(x, real(f(r,t)))
            push!(y, imag(f(r,t)))
            push!(z, h(r,t))
        end
    end
    plt = plot3d(x, y, z, title = "Area of " * L"L", legend = false, color = "green")
    xlabel!(L"x")
    ylabel!(L"y")
    zlabel!(L"z")
    savefig(plt, "lab3/ex74/L_plot.png")
end


f = (r, t) -> r * exp(im * t)
g = (r, t) -> sqrt(r) * exp(im * t / 2) 
h = (r, t) -> abs(log(r) + im * t)


rRange = range(0.0, stop = 1.0, step = 0.02)
tRange = range(start = 0.0, stop = 4pi, step = 0.1)

draw_S_r(f, g, rRange, tRange)
draw_S_c(f, g, rRange, tRange)


rRange = range(0.1, stop = 10.0, step = 0.15)
tRange = range(start = 0.0, stop = 8pi, step = 0.1)

draw_L(f, h, rRange, tRange)