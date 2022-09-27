// FSTreeTraversal.cpp
// Names: Claire Becker and Selena Zhu
// Date: 4/13/22
// Purpose: To traverse through the FSTree and print the paths of the 
//          directories
#include <cstring>
#include <iostream>
#include <limits>
#include "FSTree.h"
#include "DirNode.h"
#include "FSTreeTraversal.h"

using namespace std;

// int main(int argc, char *argv[]){
//     if (argc != 2) {
//         cerr << "Usage: gerp directory output_file";
//     }
//     string topDirectory = argv[1];
//     treeTraversal(topDirectory);
// }

void FSTreeTraversal::treeTraversal(string directory){
    FSTree tree(directory);
    treeTraversalHelper(tree.getRoot(), "");
}

void FSTreeTraversal::treeTraversalHelper(DirNode *tree, string directory){
    string currDir = directory + tree->getName();
    if (tree->isEmpty()) {
        return;
    } 
    if (tree->hasSubDir()) {
        for (int i = 0; i < tree->numSubDirs(); i++) {
            treeTraversalHelper(tree->getSubDir(i), currDir + "/");
        }
    } 
    if (tree->hasFiles()) {
        storeFilePath(tree, currDir);
    }
}

void FSTreeTraversal::storeFilePath(DirNode *curr, string directory){  
    for (int i = 0; i < curr->numFiles(); i++) {
        files new_file;
        new_file.fileName = curr->getFile(i);
        new_file.filePath = directory + "/" + curr->getFile(i);
        filePathList.push_back(new_file);
    }
}