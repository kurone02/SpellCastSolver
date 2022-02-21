/*
    trie.hpp
*/

#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#define self (*this) 
using namespace std;

const int ALPHABET_SIZE = 26;

/*
    Declaration
*/

class Trie{
public:
    struct Node{
        int cnt; bool is_leaf;
        Node *child[ALPHABET_SIZE];

        Node(){
            cnt = 0; is_leaf = false;
            for(int i = 0; i < ALPHABET_SIZE; i++) child[i] = NULL;
        }
    };
    typedef Node* PNode;

private:
    /* data */
    PNode root, traverse_ptr;

    /* Private methods*/

    // Create a new node
    PNode create_node(){ return new Node(); }
    // Erase a node from the tree
    PNode erase(PNode current_node, const string &str, const int &current_id);
    // Delete a subtree in Trie
    void delete_subtree(PNode root_tree);
    // Print all words
    void print_all(PNode current_node, string str);

public:
    Trie();
    ~Trie();

    /* Public methods*/

    // Insert a new word into the dictionary
    void insert(const string &str);
    // Search for a word
    bool search(const string &str);
    // Erase a word from the dictionary
    void erase(const string &str);
    // Print all words
    void print_all();
    // Go to the chosen child of a node in the tree
    PNode next_child(const PNode &current_node, const char &c);
    // Check if the next character is in the prefix set
    bool check_next_char(const PNode &current_node, const char &c);
    // Retrieve the root of the tree
    PNode get_root();
};

/*
    Private Implementation
*/

Trie::PNode Trie::erase(PNode current_node, const string &str, const int &current_id){
    if(current_node == NULL) return NULL;
    current_node->cnt--;
    int ord = str[current_id] - 'a';
    current_node->child[ord] = erase(current_node->child[ord], str, current_id + 1);
    if(current_node->cnt == 0){
        delete current_node;
        return NULL;
    } else return current_node;
}

void Trie::delete_subtree(PNode root_tree){
    if(root_tree == NULL) return;
    cerr << root_tree << '\n';
    for(int i = 0; i < ALPHABET_SIZE; i++){
        delete_subtree(root_tree->child[i]);
    }
    delete root_tree;
}

void Trie::print_all(PNode current_node, string str){
    if(current_node == NULL) return;
    if(current_node->is_leaf) cout << str << '\n';
    for(int i = 0; i < ALPHABET_SIZE; i++){
        PNode next_node = current_node->child[i];
        if(next_node != NULL){
            str.push_back('a' + i);
            print_all(next_node, str);
            str.pop_back();
        }
    }
}


/*
    Public Implementation
*/

Trie::Trie(){
    root = create_node();
}

Trie::~Trie(){
    // delete_subtree(root);
}

void Trie::insert(const string &str){
    PNode current_node = root;
    for(char c: str){
        int ord = c - 'a';
        if(current_node->child[ord] == NULL){
            current_node->child[ord] = create_node();
        }
        current_node = current_node->child[ord];
        current_node->cnt++;
    }
    current_node->is_leaf = true;
}

bool Trie::search(const string &str){
    PNode current_node = root;
    for(char c: str){
        int ord = c - 'a';
        if(current_node->child[ord] == NULL){
            return false;
        }
        current_node = current_node->child[ord];
    }
    return current_node->is_leaf;
}

void Trie::erase(const string &str){
    if(!search(str)) return;
    erase(root, str, 0);
}

void Trie::print_all(){
    print_all(root, "");
}

Trie::PNode Trie::next_child(const PNode &current_node, const char &c){
    if(current_node == NULL) return NULL;
    return current_node->child[c - 'a'];
}

bool Trie::check_next_char(const PNode &current_node, const char &c){
    if(current_node == NULL) return false;
    if(current_node->child[c - 'a'] == NULL) return false;
    return true;
}

Trie::PNode Trie::get_root(){
    return root;
}


#endif