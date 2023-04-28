rm -rf tests
mkdir tests
g++ gen/gen.cpp -std=c++14 -o gen.out
./gen.out 1 400000 > tests/1.in
./gen.out 1 399999 > tests/2.in
./gen.out 2 400000 > tests/3.in
./gen.out 2 399999 > tests/4.in
./gen.out 3 400000 > tests/5.in
./gen.out 3 399999 > tests/6.in
rm -f gen.out
for((i=1;i<=3;i++)); do
    g++ validator/val$i.cpp -std=c++14 -o val$i
done
g++ solution/sol.cpp -std=c++14 -o sol
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