set xlabel 'Lattice size'
set ylabel 'Equilibrium time'
set dummy t
set term png
set out 'Fit_equilibrium.png'
F(t) = a + b*t**c
a = 800
b = 70
c =2
fit F(t) 'lattice_v_t_eq.txt' via a, b, c
plot 'lattice_v_t_eq.txt' l p pt 7 lc rgb 'red' t 'Data', F(t) lw 3 lc rgb 'black' t 'Least squares fit'
