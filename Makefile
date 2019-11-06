PARSER_SRC=parser.y
SCANNER_SRC=scanner.l
TARGET=parser
OBJS=$(patsubst %.cpp, %.o, $(wildcard *.cpp))
CXX=clang++

%.o : %.cpp
	$(CXX) -c $^

$(TARGET) : y.tab.c lex.yy.c $(OBJS)
	$(CXX) -ferror-limit=1 $^ -ly -ll -o $@

y.tab.c : $(PARSER_SRC)
	yacc -d $^

y.tab.h : $(PARSER_SRC)
	yacc -d $^

scanner: lex.yy.c y.tab.h
	cc -DENABLE_SCANNER_MAIN $< -ll -o $@

lex.yy.c : $(SCANNER_SRC)
	lex $^

clean:
	$(RM) y.tab.c y.tab.h y.output scanner lex.yy.c $(TARGET) *.o