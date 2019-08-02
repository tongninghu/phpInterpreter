#include <iostream>
#include <fstream>
#include "SemanticAnalyzer.h"

using namespace std;


// Driver function
int main(int argc, char * argv[]) {
	FILE* fp = fopen(argv[1], "r");

	if (!fp) {
		cout << "Abort: state file open fail." << endl;
		return 0;
	}
	else {
		cout << "file open successfully." << endl;
	}

	Lexer lexer(fp);
/*
	Token e;
	Token t;

	t = lexer.get_next_token();
	while (t != e) {
			t.print();
			t = lexer.get_next_token();
	}  */
	Parser parser(&lexer);
	AST* tree = parser.program();
	SemanticAnalyzer s;
	s.NodeVisit(tree);
	return 0;
}
