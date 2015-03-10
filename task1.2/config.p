
set terminal png

set xlabel "Number of elements (logscale)"
set ylabel "Nanoseconds per push operation" # Note that we divide by $2!

set yrange [0:100]
set logscale x

plot \
"heaps.dat" using 2:(1000 * $4/$2):(1000 * $6/$2):xticlabel(2) with errorlines title "Lecture heap", \
"heaps.dat" using 2:(1000 * $8/$2):(1000 * $10/$2):xticlabel(2) with errorlines title "STL heap"