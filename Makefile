test: Lexer.o main.o Parser.o
	clang++ -std=c++11 -g -w main.o Parser.o Lexer.o -o test

Lexer.o: Lexer.h Lexer.cpp
	clang++ -std=c++11 -g -w -c Lexer.cpp

Parser.o: Lexer.o Parser.h Parser.cpp
	clang++ -std=c++11 -g -w -c Parser.cpp

main.o: main.cpp Parser.o
	clang++ -std=c++11 -g -w -c main.cpp

run:
	./test test.php

clean:
	rm -f test Lexer.o main.o Parser.o
