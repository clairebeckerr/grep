#ifndef GERP_H
#define GERP_H

#include "FSTreeTraversal.h"
#include "hashTable.h"
#include <string>

class gerp{

public:
    gerp(string directory);
    hashTable new_hash;
    FSTreeTraversal new_tree;
    void runGerp(ofstream &outstream,istream &commands);
    void index_file(ifstream &files, int fileNumber);
    std::string stripNonAlphaNum(std::string old_string);
    bool isAlphaNum(char letter);
private:
    void print(set<match> matches, ofstream &output);
    void insensitive_match(string word, ofstream &output, string sensitive);
    void sensitive_match(string word, ofstream &output);

};

#endif