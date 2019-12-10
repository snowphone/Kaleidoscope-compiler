PARSER_SRC=parser.y
SCANNER_SRC=scanner.l
TARGET=parser
BUILD_DIR=./build
_OBJS=$(PARSER_SRC:.y=.o) $(SCANNER_SRC:.l=.o) $(patsubst %.cpp, %.o, $(wildcard *.cpp)) 
OBJS=$(addprefix $(BUILD_DIR)/, $(_OBJS))

CXX=clang++
FLAGS= -g -ferror-limit=1 -Wall $$(llvm-config --cxxflags) -Wno-write-strings -Wno-unused
LDFLAGS:=$$(llvm-config --ldflags --libs)

VERSION=$$(clang --version | grep -Po '\d\.\d\.\d' )
CPU=$$(lscpu | grep -i 'cpu(s):' | grep -Po '\d+')

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $^ $(LDFLAGS) 

$(BUILD_DIR)/%.o : %.cpp 
	$(CXX) $(FLAGS) -c $< -o $@

scanner.cpp : $(SCANNER_SRC)
	lex -o $@ $^

parser.cpp : $(PARSER_SRC)
	rm -f parser.h
	yacc -d -o $@ $^
	rename 's/hpp/h/' *.hpp

.PHONEY: clean
clean:
	$(RM) parser.cpp parser.h y.output scanner scanner.cpp $(TARGET) $(OBJS)
