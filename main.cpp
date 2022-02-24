#include <iostream>
#include <cstdio>
#include <fstream>
#include "spell_cast.hpp"
using namespace std;

SpellCast solver;
LetterScore score_data;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // freopen("test.inp", "r", stdin);

    while(true){
        cerr << "Please type in the character matrix:\n";
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                char c; cin >> c;
                solver.set_char(i, j, c);
                // cerr << score_data.get_score(c) << ' ';
                solver.set_score(i, j, score_data.get_score(c));
            }
            // cerr << '\n';
        }
        cerr << "Please type in the Double word position (row, col), if not please type 0 0: ";
        int double_x, double_y; cin >> double_x >> double_y;
        if(double_x != 0 && double_y != 0){
            solver.set_double(double_x - 1, double_y - 1);
        }
        cerr << "Please type in the Double letter position (row, col), if not please type 0 0: ";
        cin >> double_x >> double_y;
        if(double_x != 0 && double_y != 0){
            int old_score = solver.get_score(double_x - 1, double_y - 1);
            solver.set_score(double_x - 1, double_y - 1, old_score << 1);
        }
        cerr << "Please type in the Triple letter position (row, col), if not please type 0 0: ";
        cin >> double_x >> double_y;
        if(double_x != 0 && double_y != 0){
            int old_score = solver.get_score(double_x - 1, double_y - 1);
            solver.set_score(double_x - 1, double_y - 1, old_score * 3);
        }

        Answer res = solver.solve();
        cerr << "The word is: " << res.word << '\n';
        cerr << "Total score is: " << res.get_score() << '\n'; 
        cerr << "----------------------------\n";
    }

    return 0;
}



/*
iipbo
ldwwx
gniee
uettn
agqoo
5 2
3 1
0 0

*/