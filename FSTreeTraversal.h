// FSTreeTraveral.h
// Names: Selena Zhu and Claire Becker
// Date: 4/24/22
// Purpose: The interface for the FSTreeTraversal class

#ifndef _FSTREETRAVERSAL_H_
#define _FSTREETRAVERSAL_H_

#include "FSTree.h"
#include "DirNode.h"
using namespace std;

struct files {
    string fileName;
    string filePath;
};

class FSTreeTraversal {
public:
    void treeTraversal(string directory);
    vector<files> filePathList;
private:
    void treeTraversalHelper(DirNode *tree, string directory);
    void printHelper(DirNode *curr, string directory);
    void storeFilePath(DirNode *curr, string directory);
};

#endif