PARSER_SRC=parser.y
SCANNER_SRC=scanner.l
TARGET=parser
OBJS:=$(patsubst %.cpp, %.o, $(wildcard *.cpp))
CXX=clang++
FLAGS= -g -ferror-limit=1 -Wall $$(llvm-config --cxxflags) -Wno-write-strings -Wno-unused
LDFLAGS:=$$(llvm-config --ldflags --libs)

VERSION=$$(clang --version | grep -Po '\d\.\d\.\d' )

$(TARGET) : $(OBJS) parser.o scanner.o main.o
	$(CXX) -o $@ $^ $(LDFLAGS) 

scanner: scanner.cpp parser.h
	cc -DENABLE_SCANNER_MAIN $< -ll -o $@

parser.cpp : $(PARSER_SRC)
	yacc -d -o $@ $^
	rename 's/hpp/h/' *.hpp

scanner.o : scanner.cpp parser.h
	$(CXX) $(FLAGS) -c -Wno-unused-function $<

parser.o : parser.cpp parser.h
	$(CXX) $(FLAGS) -c -Wno-unused-function $<

%.o : %.cpp
	$(CXX) $(FLAGS) -c $^

scanner.cpp : $(SCANNER_SRC)
	lex -o $@ $^

clean:
	$(RM) parser.cpp parser.h y.output scanner scanner.cpp $(TARGET) *.o
