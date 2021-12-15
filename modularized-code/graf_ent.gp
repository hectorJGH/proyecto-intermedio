set title "Entropy as a function of time"
set xlabel 'Time (step)'
set ylabel 'Entropy'
set term png
set logscale x
set out 'Entropy.png'
plot 'entropia.txt' u 1:2 w l t ''

unset logscale x
set title "Radius of the drop as a function of time"
set xlabel 'Time (10^5 step)'
set ylabel 'Radius'
set term png
set out 'Radius.png'
plot 'entropia.txt' u ($1/100000):3 w l t '' 
