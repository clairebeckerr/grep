// main.cpp
// Names: Selena Zhu and Claire Becker
// Date: 4/22/22
// Purpose: The main that reads in files and arguments in order to run the 
//          gerp class

#include "gerp.h"
#include "stringProcessing.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template<typename streamtype>
void open_check(streamtype &stream, string file_name);
void abort(string error_message);

 /* main
 * Purpose: initialize the metrosim game based
 * on whether the user would like to enter commands manually or read them
 * in from a file.
 * Parameters: argc, argv
 * Returns: N/A
 * Effects: calls runMetroSim program
 */
int main(int argc, char *argv[])
{
    // Declare file streams.
    ofstream outstream;

    //checks for 3 options: incorrect number of arguments, 3 arguments in
    //which case: read commands from user input, or 4 arguments in which case
    //read commands from commands file.
    if (not (argc == 3)) {
        abort("Usage: ./gerp inputDirectory outputFile");
    } else {
        gerp new_gerp(argv[1]);
        for (size_t i = 0; i < new_gerp.new_tree.filePathList.size(); i++) {
            ifstream one_file;
            string file_path = new_gerp.new_tree.filePathList.at(i).filePath;
            open_check(one_file, file_path);
            new_gerp.index_file(one_file, i);
            one_file.close();
        }
        open_check(outstream, argv[2]);
        
        new_gerp.runGerp(outstream, std::cin);
        
        //close streams
        // for (int i = 0; i < new_gerp.new_tree.filePathList.size(); i++) {
        //     one_file.close();
        // }
        outstream.close();
    }
        return 0;
}

 /* open_check
 * Purpose: Trys to open the given file, abort if it fails.
 * on whether the user would like to enter commands manually or read them
 * in from a file.
 * Parameters: a stream, a file name
 * Returns: N/A
 * Effects: If it returns, it can be assumed that the stream is open.
 */
template<typename streamtype>
void open_check(streamtype &stream, string file_name)
{
    stream.open(file_name);
    if (not stream.is_open())
        abort("Error could not open file " + file_name);
}

 /* abort
 * Purpose: prints error message if file could not be opened
 * Parameters: a string of the error messages
 * Returns: N/A
 * Effects: Informs user the file coudl not be opened. 
 */
void abort(string error_message)
{
    cerr << error_message << endl;
    exit(EXIT_FAILURE);
}
