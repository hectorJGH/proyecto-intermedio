set title "Entropy as a function of time"
set xlabel 'Time (step)'
set ylabel 'Entropy'
set term png
set logscale x
set out 'Entropy.png'
plot 'entropia.txt' u 1:2 w l t ''

set title "Radius of the drop as a function of time"
set xlabel 'Time (10^6 step)'
set ylabel 'Radius'
set term png
set out 'Radius.png'
plot 'entropia.txt' u ($1/10000.):3 w l t '' 
