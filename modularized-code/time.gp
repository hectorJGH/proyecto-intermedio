set title "Execution time for lattice size"
set xlabel 'Lattice size'
set ylabel 'Time'
set term png
set key right center
set out 'Time.png'
set logscale x
plot "time.txt" u 1:3 w lp lw 2 t "without optimization", "time.txt" u 1:2 w lp lw 2 t "with O3 optimization"
