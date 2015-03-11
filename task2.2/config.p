set terminal png enhanced

set xlabel "Working Set Size (Bytes)"
set ylabel "Cycles / List Element"

set logscale x 2
set format x '2^{%L}'

plot \
"0.dat" using (2**$4):6 every ::3 with linespoints title "NPAD 0", \
"7.dat" using (2**$4):6 every ::3  with linespoints title "NPAD 7", \
"15.dat" using (2**$4):6 every ::3  with linespoints title "NPAD 15", \
"31.dat" using (2**$4):6 every ::3  with linespoints title "NPAD 31"