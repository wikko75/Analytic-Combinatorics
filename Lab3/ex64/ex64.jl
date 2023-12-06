using TaylorSeries
using Plots
using LaTeXStrings

f = z -> 1/(1 - z)^z

taylor = taylor_expand(f, 0.0; order = 100)

r = [getcoeff(taylor, i) for i in 0:100]

plt = scatter(0:100, r, label=false)
xticks!(0:10:100)
xlabel!(L"n")
ylabel!(L"r_n")
title!(L"Coefficients $r_n = [x^n]f(z)$")
savefig(plt, "ex64/r_n_coeff_plot.png")