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

    cerr << "Please type in the character matrix:\n";
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            char c; cin >> c;
            solver.set_char(i, j, c);
        }
    }
    cerr << "Please type in the score matrix:\n";
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            int x; cin >> x;
            solver.set_score(i, j, x);
        }
    }
    cerr << "Please type in the Double word position (row, col): ";
    int double_x, double_y; cin >> double_x >> double_y;
    if(double_x != 0 && double_y != 0){
        solver.set_double(double_x - 1, double_y - 1);
    }

    Answer res = solver.solve();
    cerr << "The word is: " << res.word << '\n';
    cerr << "Total score is: " << res.get_score() << '\n'; 

    return 0;
}



/*
inrlo
yoidb
tahri
belee
qfges

1 2 2 3 1
4 1 1 3 4
2 1 4 4 1
4 1 3 1 1
8 5 3 1 2

*/