#!/usr/bin/gnuplot

set terminal png
set output "cm1_plot.png"
set logscale x 2  # This ensures x-axis represents powers of 2
set xlabel "Stride Size (log scale)"
set ylabel "Average L2 Misses"
plot "cm1_plot.dat" using 1:2 with lines title "8kB", \
     "cm1_plot.dat" using 1:3 with lines title "16kB", \
     "cm1_plot.dat" using 1:4 with lines title "32kB", \
     "cm1_plot.dat" using 1:5 with lines title "64kB", \
     "cm1_plot.dat" using 1:6 with lines title "128kB", \
     "cm1_plot.dat" using 1:7 with lines title "256kB", \
     "cm1_plot.dat" using 1:8 with lines title "512kB", \
     "cm1_plot.dat" using 1:9 with lines title "1MB";


pause mouse

