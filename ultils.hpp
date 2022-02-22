/*
    ultils.hpp
*/

#ifndef ULTILS_HPP
#define ULTILS_HPP

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

struct Answer{
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
};

Answer::Answer(string word = "", int total_score = 0, bool is_times_two = false){
    this->word = word;
    this->total_score = total_score;
    this->is_times_two = is_times_two;
}

Answer Answer::operator=(const Answer &other){
    word = other.word;
    total_score = other.total_score;
    is_times_two = other.is_times_two;
    return (*this);
}

void Answer::update(const char &c, const int &score, const bool &bonus){
    word += c;
    total_score += score;
    is_times_two |= bonus;
}

int Answer::get_score(){
    int res = total_score;
    if(word.size() >= 7) res += 20;
    if(is_times_two) res <<= 1;
    return res;
}

#endif