set terminal png enhanced

set xlabel "Working Set Size (Bytes)"
set ylabel "Cycles / List Element"

set logscale x 2
set logscale y

set format x '2^{%L}'

plot "data.dat" using (2**$1):2 with errorlines title "Cycles"
