#! /bin/bash

for ifile in test/*.in; do
  echo -n "Test $(basename $ifile .in) "
  dif="$(cat "$ifile" | bin/mult | diff <(cat "$ifile" | test/mult.py) -)"
  if [ -z "$dif" ]; then echo "PASSED"; else echo "FAILED"; echo "$dif"; fi
done
for i in {1..5}; do
  echo -n "Random Test $i "
  icontent="$(test/rand.py)"
  dif="$(echo "$icontent" | bin/mult | diff <(echo "$icontent" | test/mult.py) -)"
  if [ -z "$dif" ]; then echo "PASSED"; else echo "FAILED"; echo "$dif"; fi
done
