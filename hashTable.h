// hashTable.h
// Names: Selena Zhu and Claire Becker
// Date: 4/17/22
// Purpose: the interface to create the hash table

#include <string>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct match {
    int fileNumber;
    int lineNumber;
    string sensitiveWord;
    string line;

    match(int fnum, int lnum, string sWord, string l){
        fileNumber = fnum;
        lineNumber = lnum;
        sensitiveWord = sWord;
        line = l;
    }

    bool operator<(const match &other) const {
        if ((this->fileNumber == other.fileNumber) and 
            (this->lineNumber == other.lineNumber) and 
            (this->sensitiveWord == other.sensitiveWord)) {
            return false;
        } 
        return true;
    }

    match &operator=(const match &other) {
        if (this == &other) {
            return *this;
        }
        this->fileNumber = other.fileNumber;
        this->lineNumber = other.lineNumber;
        this->sensitiveWord = other.sensitiveWord;
        this->line = other.line;
        return *this;
    }
};

typedef string KeyType;
typedef set<match> ValueType;


class hashTable {
public: 
    hashTable();
    ~hashTable();
    void insert(string word, int lineNo, int fileNo, string line);
    set<match> get(string word);
    bool contains(KeyType key);
    // hashTable &operator=(const hashTable &other);

private:
    struct TableEntry {
        bool      isEmpty = true;
        KeyType   key;
        ValueType value;
    };
    void expand();
    static const int INITIAL_TABLE_SIZE = 99999;
    int currentTableSize;
    int numItemsInTable;

	TableEntry *linearTable;

};