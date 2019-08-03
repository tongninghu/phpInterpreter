#include <iostream>
#include <fstream>
#include "SemanticAnalyzer.h"

using namespace std;


// Driver function
int main(int argc, char * argv[]) {
	FILE* fp = fopen(argv[1], "r");

	if (!fp) {
		cout << "Abort: file open fail." << endl;
		return 0;
	}
	else {
		cout << "file open successfully." << endl;
	}

	Lexer lexer(fp);
	Parser parser(&lexer);
	AST* tree = parser.program();
	SemanticAnalyzer s;
	s.NodeVisit(tree);
	delete tree;
	return 0;
}
