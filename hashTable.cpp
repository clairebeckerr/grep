// hashTable.cpp
// Names: Selena Zhu and Claire Becker
// Date: 4/16/22
// Purpose: the implementation for the hashTable class that creates a 
//          hash table and
#include <iostream>
#include <stdio.h>
#include <functional>
#include "stringProcessing.h"

#include "hashTable.h"

using namespace std;

 /* constructor
 * Purpose: sets initial table size and num items in table, creates a new hash
 * table
 * Parameters: N/A
 * Returns: N/A
 * Effects: initializes hashTable 
 */
hashTable::hashTable(){
    currentTableSize = INITIAL_TABLE_SIZE;
    numItemsInTable  = 0;

    linearTable = new TableEntry[currentTableSize];
    for (int i = 0; i < currentTableSize; i++){
        linearTable[i].isEmpty = true;
    }
}

//  /* deleteList
//  * Purpose: helper function to delete list
//  * Parameters: set of matches
//  * Returns: N/A
//  * Effects: helper that pops matches off of vector
//  */
// void hashTable::deleteList(set<match> matches)
// {
//         matches.clear();
// }

 /* destructor
 * Purpose: deletes hashTable
 * Parameters: N/A
 * Returns: N/A
 * Effects: destructs hashTable, deletes data on heap
 */
hashTable::~hashTable()
{
        for (int i = 0; i < currentTableSize; i++){
                linearTable[i].value.clear();
        }

        delete [] linearTable;
        numItemsInTable = 0;
}

 /* expand
 * Purpose: expands current table to a new table 2 times + 2 bigger
 * Parameters: N/A
 * Returns: N/A
 * Effects: makes linear Table bigger
 */
void hashTable::expand(){
        int oldTableSize = currentTableSize;
        currentTableSize = currentTableSize * 2 + 2;
        TableEntry *new_table = new TableEntry[currentTableSize];
        TableEntry *curr_table = new TableEntry[oldTableSize];
        // copy data into temporary array
        for (int i = 0; i < oldTableSize; i++) {
                curr_table[i].key = linearTable[i].key;
                curr_table[i].value = linearTable[i].value;
                curr_table[i].isEmpty = linearTable[i].isEmpty;
        }
        delete [] linearTable;
        linearTable = new_table;
        numItemsInTable = 0;
        // copy into expanded array
        for (int i = 0; i < oldTableSize; i++){
                for (auto it = curr_table[i].value.begin(); 
                          it != curr_table[i].value.end(); it++){
                        if (not curr_table[i].isEmpty){ 
                                insert(it->sensitiveWord, 
                                        it->lineNumber, 
                                        it->fileNumber,
                                        it->line);
                        }
                }
        }
        delete [] curr_table;
}

 /* insert
 * Purpose: insert a new match into the hash table
 * Parameters: string word, integer of line number and file number, and the 
 * string of the line it is on
 * Returns: N/A
 * Effects: inserts into hashTable
 */
void hashTable::insert(string word, int lineNo, int fileNo, string line) {
        match new_match(fileNo, lineNo, word, line);
        string lower = "";
        for (size_t i = 0; i < word.size(); i++){
                lower += tolower(word[i]);
        }
        int bucket = hash<KeyType>{}(lower) % currentTableSize;
        float loadFactor = (float)numItemsInTable / currentTableSize;
        if (loadFactor > 0.7)
                expand();
        if (linearTable[bucket].isEmpty == false and 
            linearTable[bucket].key != lower) {
                int attempt = 0;
                bool found = false;
                while (not found){
                        int index = (bucket + attempt) % currentTableSize;
                        if (linearTable[index].isEmpty){
                        found = true;
                        linearTable[index].key = lower;
                        linearTable[index].value.insert(new_match);
                        linearTable[index].isEmpty = false; 
                        } else
                                attempt++;
                }
                numItemsInTable++;
        } else {
                if (linearTable[bucket].key == lower and lower != "") {
                        linearTable[bucket].value.insert(new_match);
                } else {
                        linearTable[bucket].key = lower;
                        linearTable[bucket].value.insert(new_match);
                        linearTable[bucket].isEmpty = false;
                        numItemsInTable++;
                }    
        }
}

 /* contains
 * Purpose: checks if a given key is in the hashTable
 * Parameters: a string called key
 * Returns: boolean
 * Effects: none
 */
bool hashTable::contains(KeyType key) {
        for (int i = 0; i < currentTableSize; i++) {
                if (key == linearTable[i].key) {
                        return true;
                }
        }
        return false; 
}

 /* get
 * Purpose: gets the set at the element that contains the word
 * Parameters: a string called word
 * Returns: a set of match structs if found and an empty set if not found
 * Effects: none
 */
set<match> hashTable::get(string word){
        for(int i = 0; i < currentTableSize; i++) {
                // if word is found in hash
                if (linearTable[i].key == word) {
                        return linearTable[i].value;
                }
        }
        // if word is not in hash
        set<match> empty_set;
        return empty_set;  
}


// void hashTable::linearProbe(int attempt, int bucket, string lower, 
//                             bool found, match new_match) {
//         int index = (bucket + attempt) % currentTableSize;
//         // if empty element is found
//         if (linearTable[index].isEmpty){
//                 found = true;
//                 linearTable[index].key = lower;
//                 linearTable[index].value.insert(new_match);
//                 linearTable[index].isEmpty = false; 
//         // traverse
//         } else {
//                 attempt++;
//         }
// }