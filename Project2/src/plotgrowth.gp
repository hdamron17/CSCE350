set datafile separator ","
set key autotitle columnhead
builddir="build/"
infile=builddir."output.csv"
outfile2=builddir."plotgrowth2.tex"
outfile3=builddir."plotgrowth3.tex"

set term epslatex color

set xlabel "Number of comparisons"
set ylabel "Input size"

set output outfile3
plot for [i=2:4] infile using 1:i with linespoints pt 7;

set output outfile2
plot for [i=3:4] infile using 1:i with linespoints pt 7;
