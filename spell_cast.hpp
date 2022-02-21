/*
    spell_cast.hpp
*/

#ifndef SPELL_CAST_HPP
#define SPELL_CAST_HPP

#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include "trie.hpp"
#define self (*this)
using namespace std;

// To traverse adjacent cells in dfs
const int dx[] = {0,  0, 1, -1, 1, -1,  1, -1};
const int dy[] = {1, -1, 0,  0, 1,  1, -1, -1};

/*
    Declaration
*/

class SpellCast{
private:
    /* data */
    int num_cols, num_rows;
    vector<vector<char> > character_matrix;
    vector<vector<string> > level;
    Trie dict;
    string longest_word;

    /* Private methods */

    // Recursively traverse the board
    void dfs(const Trie::PNode &current_node, const int &x, const int &y);
    // Check if the cell is valid
    bool check_valid_cell(const int &x, const int &y);
    // Reset the level to -1
    void reset_level();

public:
    SpellCast(int num_cols, int num_rows);
    ~SpellCast();

    /* Public methods */

    // Print the current board
    void print_current_board();
    // Assign a specific cell a character
    char set_char(const int &row, const int &col, const char &c);
    // Get the character of a specific cell
    char get_char(const int &row, const int &col);
    // Solve SpellCast
    string solve();
};

/*
    Private Implementation
*/

void SpellCast::reset_level(){
    for(auto &row: level){
        for(auto &col: row){
            col = "";
        }
    }
}

bool SpellCast::check_valid_cell(const int &x, const int &y){
    return (0 <= x && x < num_rows) && (0 <= y && y < num_cols);
}

void SpellCast::dfs(const Trie::PNode &current_node, const int &x, const int &y){
    if(current_node == NULL) return;

    level[x][y] += get_char(x, y);

    if(current_node->is_leaf && longest_word.size() < level[x][y].size()){
        longest_word = level[x][y];
    }

    for(int i = 0; i < 8; i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if(!check_valid_cell(new_x, new_y)) continue;
        char next_char = get_char(new_x, new_y);
        if(!dict.check_next_char(current_node, next_char)) continue;
        if(!level[new_x][new_y].empty()) continue;
        level[new_x][new_y] = level[x][y];
        dfs(dict.next_child(current_node, next_char), new_x, new_y);
    }

    level[x][y] = "";
}


/*
    Public Implementation
*/

SpellCast::SpellCast(int num_cols = 5, int num_rows = 5){
    self.longest_word = "";
    self.num_cols = num_cols;
    self.num_rows = num_rows;
    self.character_matrix.resize(num_rows);
    for(auto &row: character_matrix) row.resize(num_cols);
    self.level.resize(num_cols);
    for(auto &row: level) row.resize(num_rows);
    ifstream fi("data.dic");
    string x;
    while(fi >> x){
        dict.insert(x);
    }
}

SpellCast::~SpellCast(){
    for(auto &row: character_matrix) row.clear();
    character_matrix.clear();
    dict.~Trie();
}

void SpellCast::print_current_board(){
    for(auto row: character_matrix){
        for(auto col: row){
            cout << col << ' ';
        }
        cout << '\n';
    }
}

char SpellCast::set_char(const int &row, const int &col, const char &c){
    return character_matrix[row][col] = c;
}

char SpellCast::get_char(const int &row, const int &col){
    return character_matrix[row][col];
}

string SpellCast::solve(){
    longest_word = "";
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            reset_level();
            dfs(dict.next_child(dict.get_root(), get_char(i, j)), i, j);
        }
    }
    return longest_word;
}

#endif
