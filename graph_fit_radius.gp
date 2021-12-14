set title "Radius of the drop as a function of time"
set xlabel 'Time (10^4 step)'
set ylabel 'Radius'
set key left top
set term png
set out 'Radius_fit.png'
set dummy t
F(t) = A* t**B + C
C = 0.707107
A = 4.0 / sqrt(7740)
B = 1.0 / 2
fit F(t) "radius_fit.txt" u 1:3 via A, B
plot "radius_fit.txt" u ($1/10000):3 t 'Radius', F(t*10000) lw 3 t 'Least squares fit'
