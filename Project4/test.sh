#! /bin/bash

BIN="bin/decode"
TESTDIR="test"

for ifile in $TESTDIR/*.in; do
  echo -n "Test $(basename $ifile .in) "
  ofile="$TESTDIR/$(basename "$ifile" .in).out"
  echo "Here"
  dif="$(cat "$ifile" | "$BIN" | diff "$ofile" -)"
  if [ -z "$dif" ]; then echo "PASSED"; else echo "FAILED"; echo "$dif"; fi
done
