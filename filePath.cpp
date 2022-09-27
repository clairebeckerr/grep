// filePath.cpp
// Names: Selena Zhu and Claire Becker
// Date: 4/22/22
// Purpose: to assign each file path to a number representation

#include <iostream>
#include <stdio.h>
#include <functional>

#include "filePath.h"
#include "FSTree.h"
using namespace std;

void treeTraversal(string directory);
void treeTraversalHelper(DirNode *tree, string directory);
void printHelper(DirNode *curr, string directory);

void storeFilePath(string directory) {
    vector<string> pathDatabase;

}