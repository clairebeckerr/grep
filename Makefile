#
# Makefile for gerp
#
# Project 3 (spring 2022)
#

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 
LDFLAGS = -g3


gerp: main.o gerp.o FSTreeTraversal.o hashTable.o stringProcessing.o \
		FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) -o gerp $^

gerp.o: gerp.cpp gerp.h hashTable.h FSTreeTraversal.h stringProcessing.h
	$(CXX) $(CXXFLAGS) -c gerp.cpp

hashTable.o: hashTable.cpp hashTable.h
	${CXX} ${CXXFLAGS} -c hashTable.cpp

treeTraversal: FSTreeTraversal.o FSTree.o DirNode.o
	${CXX} ${LDFLAGS} -o treeTraversal $^

FSTreeTraversal.o: FSTreeTraversal.cpp FSTreeTraversal.h FSTree.o DirNode.o
	${CXX} ${CXXFLAGS} -c FSTreeTraversal.cpp

stringProcessing.o: stringProcessing.h stringProcessing.cpp
	${CXX} ${CXXFLAGS} -c stringProcessing.cpp

%.o: %.cpp $(shell echo *.h)
	${CXX} ${CXXFLAGS} -c $<

unit_test: unit_test_driver.o hashTable.o gerp.o FSTree.o DirNode.o\
		   FSTreeTraversal.o
	${CXX} ${LDFLAGS} unit_test_driver.o hashTable.o DirNode.o gerp.o \
					  FSTree.o FSTreeTraversal.o

clean:
	mv FSTree.o FSTree.keep
	mv DirNode.o DirNode.keep
	rm -rf hw3 *.o *.dSYM
	mv FSTree.keep FSTree.o 
	mv DirNode.keep DirNode.o

# Don't forget to add your testing files to this rule if you use it!
provide:
	provide comp15 proj3_gerp FSTreeTraversal.cpp \
									 FSTreeTraversal.h \
									 stringProcessing.h \
									 stringProcessing.cpp \
									 README \
									 unit_tests.h \
									 test_directory \
									 gerp.cpp gerp.h \
									 hashTable.cpp hashTable.h \
									 main.cpp Makefile

