/*
    ultils.hpp
*/

#ifndef ULTILS_HPP
#define ULTILS_HPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct SwapCell{
    int x, y;
    char new_char;
    SwapCell(int x, int y,char new_char){
        this->x = x; this->y = y;
        this->new_char = new_char;
    }
};

struct Answer{
    vector<SwapCell> changed_cells;
    string word;
    int total_score;
    bool is_times_two;

    Answer(string word, int total_score, bool is_times_two);

    // Assign two answers
    Answer operator =(const Answer &other);
    // Update data
    void update(const char &c, const int &score, const bool &bonus);
    // Get total score
    int get_score();
    // Change the cell (x, y) in to the character c
    void add_change(const int &x, const int &y, const char &c);
    // Get total number of swap letters
    int get_num_swaps();
    // Clear all changes
    void clear_changes();
};

Answer::Answer(string word = "", int total_score = 0, bool is_times_two = false){
    this->word = word;
    this->total_score = total_score;
    this->is_times_two = is_times_two;
    this->changed_cells = vector<SwapCell>();
}

Answer Answer::operator=(const Answer &other){
    word = other.word;
    total_score = other.total_score;
    is_times_two = other.is_times_two;
    changed_cells = other.changed_cells;
    return (*this);
}

void Answer::update(const char &c, const int &score, const bool &bonus){
    word += c;
    total_score += score;
    is_times_two |= bonus;
}

int Answer::get_score(){
    int res = total_score;
    if(is_times_two) res <<= 1;
    if(word.size() >= 7) res += 20;
    return res;
}

void Answer::add_change(const int &x, const int &y, const char &c){
    changed_cells.push_back(SwapCell(x, y, c));
}

int Answer::get_num_swaps(){
    return changed_cells.size();
}

void Answer::clear_changes(){
    changed_cells.clear();
}


struct LetterScore{
private:
    static const int ALPHABET_SIZE = 26;
    int scores[ALPHABET_SIZE];
public:
    LetterScore();
    // Get the score of a specific character
    int get_score(const char &c);
};

LetterScore::LetterScore(){
    ifstream fi("letter_score.txt");
    char c;
    while(fi >> c){
        int score; fi >> score;
        scores[c - 'a'] = score;
    }
}

int LetterScore::get_score(const char &c){
    return scores[c - 'a'];
}



#endif