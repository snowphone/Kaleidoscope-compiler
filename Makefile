PARSER_SRC=parser.y
SCANNER_SRC=scanner.l
TARGET=parser
OBJS=$(patsubst %.cpp, %.o, $(wildcard *.cpp))
CXX=clang++
FLAGS= -std=c++11 -g -ferror-limit=1 -Wall -Wno-write-strings

$(TARGET) : $(OBJS) y.tab.o lex.yy.o 
	$(CXX) $(FLAGS) $^ -ly -ll -o $@

scanner: lex.yy.c y.tab.h
	cc -DENABLE_SCANNER_MAIN $< -ll -o $@

y.tab.o : y.tab.c 
	$(CXX) $(FLAGS) -c -x c++ $<

lex.yy.o : lex.yy.c y.tab.h
	$(CXX) $(FLAGS) -c -x c++ -Wno-unused-function $<

y.tab.c : $(PARSER_SRC)
	yacc -d $^

y.tab.h : $(PARSER_SRC)
	yacc -d $^

%.o : %.cpp
	$(CXX) $(FLAGS) -c $^

lex.yy.c : $(SCANNER_SRC)
	lex $^

clean:
	$(RM) y.tab.c y.tab.h y.output scanner lex.yy.c $(TARGET) *.o
