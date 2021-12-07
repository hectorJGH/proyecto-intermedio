set title "Entropy as a function of time"
set xlabel 'Time (10⁶ step)'
set ylabel 'Entropy'
set term png
set out 'Entropy.png'
plot 'entropia.txt' u 1:2 w l

set title "Radius of the drop as a function of time"
set xlabel 'Time (10⁶ step)'
set ylabel 'Radius'
set term png
set out 'Radius.png'
plot 'entropia.txt' u 1:3 w l 
