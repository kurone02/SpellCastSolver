#include <iostream>
#include <cstdio>
#include <fstream>
#include "spell_cast.hpp"
using namespace std;

SpellCast solver;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // freopen("test.inp", "r", stdin);

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            char c; cin >> c;
            solver.set_char(i, j, c);
        }
    }

    cout << solver.solve();
    

    return 0;
}



/*
qwert
asdfg
zxcvb
fgthy
ngfdb

*/