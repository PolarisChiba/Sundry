rm -rf tests
mkdir tests
g++ gen/gen.cpp -std=c++14 -o gen.out
./gen.out 1000 > tests/1.in
./gen.out 990 > tests/2.in
./gen.out 980 > tests/3.in
./gen.out 100000 > tests/4.in
./gen.out 99990 > tests/5.in
./gen.out 99980 > tests/6.in
rm -f gen.out
for((i=1;i<=2;i++)); do
    g++ validator/val$i.cpp -std=c++14 -o val$i
done
g++ solution/sol.cpp -std=c++14 -o sol
for((i=1;i<=3;i++)); do
    echo $i
    ./val1 < tests/$i.in
    ./sol < tests/$i.in > tests/$i.out
done
for((i=4;i<=6;i++)); do
    echo $i
    ./val2 < tests/$i.in
    ./sol < tests/$i.in > tests/$i.out
done
for((i=1;i<=2;i++)); do
    rm -f val$i
done
rm -f sol