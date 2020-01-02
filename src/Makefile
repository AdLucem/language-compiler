lang: parser.yy scanner.ll main.cpp
		bison -d -o parser.cpp parser.yy
		flex -o scanner.cpp scanner.ll
		g++ -g -o ast parser.cpp scanner.cpp main.cpp -ll

clean: 
		rm parser.cpp scanner.cpp