#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int t = atoi(argv[1]);
    int q = atoi(argv[2]);

    vector<string> name, species;
    string now = "aaaa";
    while ((int)name.size() < q) {
        name.push_back(now);
        now.back() += 1;
        for (int i = 3; i >= 1; -- i) {
            if (now[i] > 'z') {
                now[i] = 'a';
                now[i - 1] += 1;
            }
        }
        species.push_back(rnd.next("cat|fish|bird|human"));
    }
    shuffle(name.begin(), name.end());

    println(q);
    int num = 0;
    while ( q -- ) {
        string op;
        if (t == 1) op = rnd.next("Birth|Information");
        else if (t == 2) op = rnd.next("Birth|Information|Talk|Sleep|Work|Eat");
        else if (t == 3) op = rnd.next("Birth|Birthsick|Information|Talk|Sleep|Work|Eat|Eatfood|Kill");

        if (num <= 5) {
            if (t != 3) op = "Birth";
            else op = rnd.next("Birth|Birthsick");
        }

        if (op == "Birth") {
            println(op, name.back(), species.back());
            name.pop_back();
            species.pop_back();
            num += 1;
        } else if (op == "Birthsick") {
            println(op, name.back(), species.back(), rnd.next(1, 10));
            name.pop_back();
            species.pop_back();
            num += 1;
        } else if (op == "Information") {
            println(op, rnd.next(1, num));
        } else if (op == "Talk") {
            println(op, rnd.next(1, num));
        } else if (op == "Sleep") {
            println(op, rnd.next(1, num), rnd.next(1, 10));
        } else if (op == "Work") {
            println(op, rnd.next(1, num), rnd.next(1, 10));
        } else if (op == "Eat") {
            vector<int> res = rnd.distinct(2, 1, num);
            println(op, res[0], res[1]);
        } else if (op == "Eatfood") {
            println(op, rnd.next(1, num), rnd.next(1, 10));
        } else if (op == "Kill") {
            vector<int> res = rnd.distinct(2, 1, num);
            println(op, res[0], res[1]);
        }
    }
}