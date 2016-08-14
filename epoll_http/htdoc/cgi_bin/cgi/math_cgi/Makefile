
MATH=math_cgi

MATH_SRC=$(shell ls | grep -E "*.cpp")
MATH_OBJ=$(MATH_SRC:.cpp=.o)

.PHONY:all
all:$(MATH)

$(MATH):math_cgi.cpp
	g++ -o $@ $^

%.o:$(shell pwd)/%.cpp
	g++ -c $<

.PHONY:clean
clean:
	rm -f  math_cgi
