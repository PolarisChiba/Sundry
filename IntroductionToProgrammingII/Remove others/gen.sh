rm -rf tests
mkdir tests
g++ gen/gen.cpp -std=c++14 -o gen.out
./gen.out 10 100 100 > tests/1.in
./gen.out 10 99 99 > tests/2.in
./gen.out 10 1000 1000 > tests/3.in
./gen.out 10 999 999 > tests/4.in
./gen.out 10 200000 100000 > tests/5.in
./gen.out 10 199999 99999 > tests/6.in
rm -f gen.out
for((i=1;i<=3;i++)); do
    g++ validator/val$i.cpp -std=c++14 -o val$i
done
g++ solution/sol.cpp -std=c++14 -o sol
./val1 < sample/0.in
./sol < sample/0.in > sample/0.out
for((i=1;i<=2;i++)); do
    echo $i
    ./val1 < tests/$i.in
    ./sol < tests/$i.in > tests/$i.out
done
for((i=3;i<=4;i++)); do
    echo $i
    ./val2 < tests/$i.in
    ./sol < tests/$i.in > tests/$i.out
done
for((i=5;i<=6;i++)); do
    echo $i
    ./val3 < tests/$i.in
    ./sol < tests/$i.in > tests/$i.out
done
for((i=1;i<=3;i++)); do
    rm -f val$i
done
rm -f sol