set terminal pngcairo  transparent enhanced font "arial,10" fontscale 1.0 size 600, 400 
set output 'errorbars2.png'
set title "Error on y represented by filledcurve shaded region"
set xlabel "Time (sec)" 
set ylabel "Rate" 
set grid layerdefault   lt 0 linecolor 0 linewidth 0.500,  lt 0 linecolor 0 linewidth 0.500
set grid xtics mxtics ytics mytics
set logscale y 10
Shadecolor = "#80E0A080"
#
plot 'data2.txt' using 1:($2+$3):($2-$3) \
      with filledcurve fc rgb Shadecolor title "Shaded error region",\
     '' using 1:2 with lines lw 2 title "Monotonic spline through data"
