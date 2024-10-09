#!/usr/bin/gnuplot

set terminal png
set output "cm1_plot.png"
set logscale x 2  # This ensures x-axis represents powers of 2
set xlabel "Stride Size (log scale)"
set ylabel "Average L2 Misses"
set xtics ("2^0" 1, "2^1" 2, "2^2" 4, "2^3" 8, "2^4" 16, "2^5" 32, "2^6" 64, "2^7" 128, "2^8" 256, "2^9" 512, "2^10" 1024, "2^11" 2048, "2^12" 4096, "2^13" 8192, "2^14" 16384, "2^15" 32768, "2^16" 65536, "2^17" 131072, "2^18" 262144, "2^19" 524288) 
plot "cm1_plot.dat" using 1:2 with lines title "8kB", \
     "cm1_plot.dat" using 1:3 with lines title "16kB", \
     "cm1_plot.dat" using 1:4 with lines title "32kB", \
     "cm1_plot.dat" using 1:5 with lines title "64kB", \
     "cm1_plot.dat" using 1:6 with lines title "128kB", \
     "cm1_plot.dat" using 1:7 with lines title "256kB"


pause mouse

