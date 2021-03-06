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
#include "ultils.hpp"
#define self (*this)
using namespace std;

LetterScore score_data;

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
    bool is_optimized_gem;
    vector<vector<char> > character_matrix;
    vector<vector<int> > score_matrix;
    vector<vector<bool> > double_matrix;
    vector<vector<Answer> > level;
    Trie dict;
    Answer longest_word;

    /* Private methods */

    // Recursively traverse the board
    void dfs(const Trie::PNode &current_node, const int &x, const int &y, const int &num_swaps);
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
    // Assign a specific cell a score
    int set_score(const int &row, const int &col, const int &c);
    // Get the score of a specific cell
    int get_score(const int &row, const int &col);
    // Assign a cell to be x2
    bool set_double(const int &row, const int &col);
    // Get if the cell is double word or not
    bool get_double(const int &row, const int &col);
    // Solve SpellCast
    Answer solve(const int &num_swaps);
    // Set the state to optimze gem
    void optimize_gem();
    // Set the state to optimze score
    void optimize_score();
};

/*
    Private Implementation
*/

void SpellCast::reset_level(){
    for(auto &row: level){
        for(auto &col: row){
            col = Answer();
        }
    }
}

bool SpellCast::check_valid_cell(const int &x, const int &y){
    return (0 <= x && x < num_rows) && (0 <= y && y < num_cols);
}

void SpellCast::dfs(const Trie::PNode &current_node, const int &x, const int &y, const int &num_swaps){
    if(current_node == NULL) return;

    // Update current answer
    level[x][y].update(get_char(x, y), get_score(x, y), get_double(x, y));

    // For debugging
    // cerr << x << ' ' << y << ' ' << get_score(x, y) << ' ' << get_double(x, y) << ' ' << num_swaps << ": " << longest_word.word << ' ' << longest_word.get_score() << ' ' << level[x][y].word << ' ' << level[x][y].get_score() << '\n';

    // Update optimal answer
    if(current_node->is_leaf){
        int longest_word_score = longest_word.get_score();
        int levelxy_score = level[x][y].get_score();

        if(is_optimized_gem){
            if(longest_word.word.size() >= 7) longest_word_score -= 20;
            if(level[x][y].word.size() >= 7) levelxy_score -= 20;
        }

        if(longest_word_score < levelxy_score){
            longest_word = level[x][y];
        } else if(longest_word_score == levelxy_score){
            if(longest_word.get_num_swaps() > level[x][y].get_num_swaps()){
                longest_word = level[x][y];
            }
        }
    }

    for(int i = 0; i < 8; i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if(!check_valid_cell(new_x, new_y)) continue;
        char next_char = get_char(new_x, new_y);
        if(!level[new_x][new_y].word.empty()) continue;
        if(!dict.check_next_char(current_node, next_char)){
            if(num_swaps > 0){
                char old_char = next_char;
                for(char new_char = 'a'; new_char <= 'z'; new_char++){
                    if(!dict.check_next_char(current_node, new_char)) continue;
                    level[new_x][new_y] = level[x][y];
                    int old_score = get_score(new_x, new_y);
                    set_char(new_x, new_y, new_char);
                    set_score(new_x, new_y, 0);
                    level[new_x][new_y].add_change(new_x, new_y, new_char);
                    dfs(dict.next_child(current_node, new_char), new_x, new_y, num_swaps - 1);
                    set_char(new_x, new_y, old_char);
                    set_score(new_x, new_y, old_score);
                    level[new_x][new_y].clear_changes();
                }
            }
        } else{
            level[new_x][new_y] = level[x][y];
            dfs(dict.next_child(current_node, next_char), new_x, new_y, num_swaps);
        }
    }

    level[x][y] = Answer();
}


/*
    Public Implementation
*/

SpellCast::SpellCast(int num_cols = 5, int num_rows = 5){
    self.longest_word = Answer();
    self.num_cols = num_cols;
    self.num_rows = num_rows;
    self.is_optimized_gem = false;
    self.character_matrix.resize(num_rows);
    for(auto &row: character_matrix) row.resize(num_cols);
    self.score_matrix.resize(num_rows);
    for(auto &row: score_matrix) row.resize(num_cols);
    self.double_matrix.resize(num_rows);
    for(auto &row: double_matrix) row.resize(num_cols);
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

int SpellCast::set_score(const int &row, const int &col, const int &c){
    return score_matrix[row][col] = c;
}

int SpellCast::get_score(const int &row, const int &col){
    return score_matrix[row][col];
}

bool SpellCast::set_double(const int &row, const int &col){
    return double_matrix[row][col] = true;
}

bool SpellCast::get_double(const int &row, const int &col){
    return double_matrix[row][col];
}

Answer SpellCast::solve(const int &num_swaps){
    longest_word = Answer();
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            reset_level();
            dfs(dict.next_child(dict.get_root(), get_char(i, j)), i, j, num_swaps);
        }
    }
    return longest_word;
}

void SpellCast::optimize_gem(){
    is_optimized_gem = true;
}

void SpellCast::optimize_score(){
     is_optimized_gem = false;
}

#endif
