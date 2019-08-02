test: Lexer.o main.o Parser.o
	clang++ -std=c++11 -g -w main.o SemanticAnalyzer.o Parser.o Lexer.o -o test

Lexer.o: Lexer.h Lexer.cpp
	clang++ -std=c++11 -g -w -c Lexer.cpp

Parser.o: Lexer.o Parser.h Parser.cpp
	clang++ -std=c++11 -g -w -c Parser.cpp

SemanticAnalyzer.o: Lexer.o Parser.o SemanticAnalyzer.cpp
	clang++ -std=c++11 -g -w -c SemanticAnalyzer.cpp

main.o: main.cpp SemanticAnalyzer.o
	clang++ -std=c++11 -g -w -c main.cpp

run:
	./test test.php

clean:
	rm -f test Lexer.o main.o Parser.o SemanticAnalyzer.o
