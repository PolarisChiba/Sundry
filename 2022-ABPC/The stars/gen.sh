rm -rf tests
mkdir tests
g++ gen/gen.cpp -std=c++17 -o gen.out
./gen.out 10 > tests/1.in
./gen.out 100 > tests/2.in
./gen.out 1000 > tests/3.in
./gen.out 10000 > tests/4.in
./gen.out 100000 > tests/5.in
./gen.out 500000 > tests/6.in
rm -f gen.out
g++ validator/val.cpp -std=c++17 -o val
g++ solution/sol.cpp -std=c++17 -o sol
./val1 < sample/0.in
./sol < sample/0.in > sample/0.out
for((i=1;i<=6;i++)); do
    echo $i
    ./val < tests/$i.in
    ./sol < tests/$i.in > tests/$i.out
done
rm -f val
rm -f sol