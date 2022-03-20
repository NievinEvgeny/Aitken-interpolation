set terminal png
set output "graph.png"

set xrange [1:2]

set yrange [4:5]

set grid

set ylabel "y"

set xlabel "x"

plot "./output.txt" using 1:2 with lines title "Interpolation"