// gerp.cpp
// Names: Selena Zhu and Claire Becker
// Date: 4/22/22
// Purpose: to find all cases of a given word in a directory

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
// #include "stringProcessing.h"
#include "gerp.h"

using namespace std;


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
// #include "stringProcessing.h"
#include "gerp.h"

using namespace std;
 /* constructor
 * Purpose: creates and traverses tree of files and subdirectories from 
 * original directory. 
 * Parameters: string of directory name
 * Returns: N/A
 * Effects: initializes gerp program
 */
gerp::gerp(string directory) {
    new_tree.treeTraversal(directory);
}

 /* runGerp
 * Purpose: run's gerp's program, reading in commands and performing them
 * Parameters: N/A
 * Returns: N/A
 * Effects:  run's gerp's program until it ends 
 */
void gerp::runGerp(ofstream &outstream, istream &commands){
    bool go = true;
    while (go == true){
        //read in commands from either a file or command line
        cout << "Query? ";
        string command;
        string secondCommand;
        commands >> command;
        if (commands.eof()){
            go = false;
        } else if (command == "@i" or command == "@insensitive"){
            commands >> secondCommand;
            secondCommand = stripNonAlphaNum(secondCommand);
            string sensitive_word = "";
            for (size_t i = 0; i < secondCommand.size(); i++){
                sensitive_word += tolower(secondCommand[i]);
            }
            insensitive_match(secondCommand, outstream, sensitive_word);
        } else if (command == "@f"){
            commands >> secondCommand;
            secondCommand = stripNonAlphaNum(secondCommand);
            outstream.close();
            outstream.open(secondCommand);
        } else if (command == "@q" or command == "@quit"){
                cout << "Goodbye! Thank you and have a nice day." << endl;
                go = false;
        } else {
            command = stripNonAlphaNum(command);
            sensitive_match(command, outstream);
        }
    }
}

 /* print
 * Purpose: prints out path, line number and line for every element in a vector
 * Parameters: set of matches, reference to output
 * Returns: N/A
 * Effects:  prints information about a set of matches
 */
void gerp::print(set<match> matches, ofstream &output) {
    for (auto it = matches.begin(); it != matches.end(); it++) {
        string path = new_tree.filePathList[it->fileNumber].filePath;
        int lineNumber = it->lineNumber;
        string line = it->line;
        output << path << ":" << lineNumber << ": " << line << endl;
    }
}

 /* insensitive_match
 * Purpose: prints all matches insensitive
 * Parameters: string of words, reference to output
 * Returns: N/A
 * Effects:  prints insensitive matches
 */
void gerp::insensitive_match(string word, ofstream &output, string sensitive) {
    if (new_hash.contains(word)){
        set<match> found = new_hash.get(word);
        print(found, output);
    } else {
        output << sensitive << " Not Found." << endl;
    } 
}

 /* sensitive_match
 * Purpose: prints all matches sensitive
 * Parameters: string of words, reference to output
 * Returns: N/A
 * Effects:  prints sensitive matches
 */
void gerp::sensitive_match(string word, ofstream &output){
    set<match> sensitiveSet;
    string lower = "";
    for (size_t i = 0; i < word.size(); i++){
        lower += tolower(word[i]);
    }
    if (new_hash.contains(lower)){
        set<match> found = new_hash.get(lower);
        for (auto it = found.begin(); it != found.end(); it++) {
            if (it->sensitiveWord == word){
                sensitiveSet.insert(*it);
            }                    
        }
        if (sensitiveSet.size() == 0) {
            output << word << " Not Found. Try with @insensitive or @i." 
            << endl;
        }
        print(sensitiveSet, output);
    } else {
        output << word << " Not Found. Try with @insensitive or @i." << endl;
    }
}

 /* index_file
 * Purpose: prints all matches sensitive
 * Parameters: reference to file, file number
 * Returns: N/A
 * Effects:  adds files to hash table
 */
void gerp::index_file(ifstream &one_file, int fileNumber){
    string line, word;
    int i = 1;
    //loops until last line of file
    while (getline(one_file, line)){
        stringstream iss(line);
        //assign variables
        while(iss >> word) {
            string clean_word = stripNonAlphaNum(word);
            new_hash.insert(clean_word, i, fileNumber, line);
        }
        i++;
    }
    //close file
    one_file.close();
}

 /* stripNonAlphaNum
 * Purpose: remove all leading and trailing non alphanumeric characters
 * Parameters: string
 * Returns: N/A
 * Effects:  returns a string with just numbers or alpha characters
 */
std::string gerp::stripNonAlphaNum(std::string old_string){
    size_t i = 0;
    size_t j = 0;

    if (old_string.size() != 0){
        while (i < old_string.length() and not isAlphaNum(old_string.at(i))) {
            i++;
        }
        j = old_string.length() - 1;
        while (j > 0 and not isAlphaNum(old_string.at(j))) {
            j--;
        }
    }
    return old_string.substr(i, j - i + 1);
}

 /* isAlphaNum
 * Purpose: remove all leading and trailing non alphanumeric characters
 * Parameters: character
 * Returns: boolean 
 * Effects:  returns a boolean if letter is a alphan/num
 */
bool gerp::isAlphaNum(char letter) {
    if ((letter < 48 or (letter > 57 and letter < 65) 
        or (letter > 90 and letter < 97) or letter > 122)) {
            return false;
        }
    return true;
}