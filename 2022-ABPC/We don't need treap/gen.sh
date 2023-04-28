rm -rf tests
mkdir tests
g++ gen/gen.cpp -std=c++17 -o gen.out
./gen.out 1 100000 100000 > tests/1.in
./gen.out 100 100000 100000 > tests/2.in
./gen.out 40 100000 300 > tests/3.in
./gen.out 10 100000 9999 > tests/4.in
rm -f gen.out
g++ validator/val.cpp -std=c++17 -o val
g++ solution/sol.cpp -std=c++17 -o sol
echo 0
./val < sample/0.in
./sol < sample/0.in > sample/0.out
for((i=1;i<=4;i++)); do
    echo $i
    ./val < tests/$i.in
    ./sol < tests/$i.in > tests/$i.out
done
rm -f val
rm -f sol