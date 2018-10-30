allerror=""
for f in test/*.in; do
  fname="$(basename $f .in)"
  error="$(cat $f | build/cmpsort | diff test/$fname.out -)";
  if [ ! -z "$error" ]; then
    echo "Test $fname failed";
    echo "$error";
  fi
  allerror="$allerror$error";
done
if [ -z "$allerror" ]; then
  echo "All tests passed";
  exit 0;
else
  echo "Tests failed";
  exit 1;
fi
