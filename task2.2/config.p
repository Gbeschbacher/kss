set terminal png enhanced

set xlabel "Working Set Size (Bytes)"
set ylabel "Cycles / List Element"

set logscale x 2
set format x '2^{%L}'

plot \
"data_predefined.dat" using (2**$1):2 with errorlines title "NPAD 0", \
"data_predefined.dat" using (2**$1):3 with errorlines title "NPAD 7", \
"data_predefined.dat" using (2**$1):4 with errorlines title "NPAD 15", \
"data_predefined.dat" using (2**$1):5 with errorlines title "NPAD 31", \
"data_predefined.dat" using (2**$1):6 with errorlines title "NPAD 63"