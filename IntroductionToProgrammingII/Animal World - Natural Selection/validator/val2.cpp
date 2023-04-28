#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    
    int q = inf.readInt(1, 400000, "q");
    inf.readEoln();

    int num = 0;
    while ( q -- ) {
        string op = inf.readToken("Birth|Information|Talk|Sleep|Work|Eat");
        inf.readSpace();
        
        if (op == "Birth") {
            string name = inf.readToken("[a-z]{4}");
            inf.readSpace();
            string species = inf.readToken("cat|fish|bird|human");
            num += 1;
        } else if (op == "Information") {
            int i = inf.readInt(1, num, "i");
        } else if (op == "Talk") {
            int i = inf.readInt(1, num, "i");
        } else if (op == "Sleep") {
            int i = inf.readInt(1, num, "i");
            inf.readSpace();
            int x = inf.readInt(1, 10, "x");
        } else if (op == "Work") {
            int i = inf.readInt(1, num, "i");
            inf.readSpace();
            int x = inf.readInt(1, 10, "x");
        } else if (op == "Eat") {
            int i = inf.readInt(1, num, "i");
            inf.readSpace();
            int j = inf.readInt(1, num, "j");
            ensure(i != j);
        }
        inf.readEoln();
    }
    inf.readEof();
}