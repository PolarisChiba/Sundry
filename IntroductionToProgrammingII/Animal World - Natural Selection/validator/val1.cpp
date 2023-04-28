#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    
    int q = inf.readInt(1, 400000, "q");
    inf.readEoln();

    int num = 0;
    while ( q -- ) {
        string op = inf.readToken("Birth|Information");
        
        if (op == "Birth") {
            inf.readSpace();
            string name = inf.readToken("[a-z]{4}");
            inf.readSpace();
            string species = inf.readToken("cat|fish|bird|human");
            num += 1;
        } else if (op == "Information") {
            inf.readSpace();
            int i = inf.readInt(1, num, "i");
        }
        inf.readEoln();
    }
    inf.readEof();
}