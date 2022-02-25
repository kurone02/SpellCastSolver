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
            solver.set_score(i, j, score_data.get_score(c));
        }
    }
    cerr << "Do you want to optimize gems? (y/n): ";
    char optimize_gem; cin >> optimize_gem;
    if(optimize_gem == 'y' || optimize_gem == 'Y'){
        cerr << "Please type in the gem matrix:\n";
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                char gems; cin >> gems;
                solver.set_score(i, j, gems - '0');
            }
        }
    } else{
        cerr << "Please type in the Double word position (row, col), if not please type 00: ";
        char inp_x, inp_y; cin >> inp_x >> inp_y;
        int double_x = inp_x - '0';
        int double_y = inp_y - '0';
        if(double_x != 0 && double_y != 0){
            solver.set_double(double_x - 1, double_y - 1);
        }
        cerr << "Please type in the Double letter position (row, col), if not please type 00: ";
        cin >> inp_x >> inp_y;
        double_x = inp_x - '0';
        double_y = inp_y - '0';
        if(double_x != 0 && double_y != 0){
            int old_score = solver.get_score(double_x - 1, double_y - 1);
            solver.set_score(double_x - 1, double_y - 1, old_score << 1);
        }
        cerr << "Please type in the Triple letter position (row, col), if not please type 00: ";
        cin >> inp_x >> inp_y;
        double_x = inp_x - '0';
        double_y = inp_y - '0';
        if(double_x != 0 && double_y != 0){
            int old_score = solver.get_score(double_x - 1, double_y - 1);
            solver.set_score(double_x - 1, double_y - 1, old_score * 3);
        }
    }
    Answer res;
    if(optimize_gem == 'y' || optimize_gem == 'Y'){
        solver.optimize_gem();
        res = solver.solve(0);
    } else{
        cerr << "Please type in the number of gems: ";
        solver.optimize_score();
        int num_gems; cin >> num_gems;
        res = solver.solve(num_gems / 3);
    }
    cerr << "The word is: " << res.word << '\n';
    cerr << ((optimize_gem == 'y' || optimize_gem == 'Y')? "Total gem is: " : "Total score is: ") 
         << res.get_score() - (((optimize_gem == 'y' || optimize_gem == 'Y') && (res.word.size() >= 7))? 20 : 0) 
         << '\n'; 
    if(res.get_num_swaps() > 0){
        cerr << "The number of swaps: " << res.get_num_swaps() << '\n';
        for(auto swap: res.changed_cells){
            cerr << "The cell (" << swap.x + 1 << ", " << swap.y + 1 << ") is changed into " << swap.new_char << '\n';
        }
    }
    

    return 0;
}


// Some random test cases from the game

/*
iipbo
ldwwx
gniee
uettn
agqoo
52
31
00
10

*/

/*
xgxxx
xexxx
xtxxx
xtxxx
xxxxx
12
31
00
10

*/

/*
iaaek
ieeca
sbgvo
yngot
moenf
n
55
00
14
3

*/ // -> 56 footrace

/*
nrdte
egiia
rnosa
tdmpn
bnrki
y
10101
10100
01001
11000
00010

*/

/*
uswue
iptdu
eyaec
ozhvo
egyqw
y
10011
10000
01000
10100
10011

*/ // 4: yogh