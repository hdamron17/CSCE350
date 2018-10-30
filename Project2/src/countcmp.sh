counts="$(seq 200 200 6000)"
repeat=3
echo "Size,Selection Sort,Quicksort,STL Sort"
for i in $counts; do
  data="";
  for alg in selection qsort stl; do
    sum="";
    for c in $(seq 1 1 $repeat); do
      point="$(src/generate_sort.sh $alg $i | build/cmpsort | grep "Comparisons: " | cut -d" " -f2)";
      if [ ! -z "$sum" ]; then sum="$sum+"; fi;
      sum="$sum$point"
    done;
    avg=$(echo "scale=2; ($sum)/$repeat" | bc);
    if [ ! -z "$data" ]; then data="$data,"; fi;
    data="$data$avg";
  done;
  echo "$i,$data";
done
