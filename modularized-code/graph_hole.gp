set title "Number of molecules inside in function of time"
set xlabel 'Time (10^5 step)'
set ylabel 'Molecules'
set term png
set out 'Hole_fit.png'
set dummy t
F(t) = A * exp(-(t-100000)/tau) 
A = 300
tau = 500000
fit F(t) "hole_last.txt" via A, tau
plot "hole.txt" u ($1/100000):2 t 'Data', F(t*100000) lw 3 t 'Least squares fit'

