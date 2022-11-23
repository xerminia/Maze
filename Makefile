CXX = g++
STD = -std=c++17
CFLAG = -Wall -Wextra -Werror -pedantic
TEST_FILES = model/maze_generate.cpp model/maze.cpp model/cave.cpp tests.cpp
TEXI2DVI = makeinfo --html

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	GTEST:= $(shell pkg-config --cflags --libs gtest 2>/dev/null)
	ifeq ($(GTEST),)
		GTEST:=-DGTEST_HAS_PTHREAD=1 -lgtest -pthread
	endif
	LEAKS_CMD = CK_FORK=no valgrind --tool=memcheck --leak-check=full --track-origins=yes  --leak-check=full --show-leak-kinds=all ./test
endif
ifeq ($(UNAME), Darwin)
	LEAKS_CMD = CK_FORK=no leaks --atExit -- ./test
	GTEST = -fsanitize=address -DGTEST_HAS_PTHREAD=1 -lgtest -pthread
endif

all: clean install tests

build:
	mkdir build
	cd ./build/ && qmake6 ../ && make

install: build
	mkdir $(HOME)/Desktop/Maze/
	cp -rf build/Maze.app $(HOME)/Desktop/Maze/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/Maze/

dvi:
	$(TEXI2DVI) Maze.texi
	open Maze/index.html

dist:
	rm -rf Maze
	mkdir Maze
	mkdir Maze/src
	cp Makefile *.texi *.cpp *.pro *.png *.inc Maze/src/
	cp -R controller model view example_file Maze/src
	tar -cvzf Maze.tar.gz Maze
	mv Maze.tar.gz $(HOME)/Desktop/
	rm -rf Maze

tests: clean
	$(CXX) $(STD) $(CFLAG) -o all_tests $(TEST_FILES) $(GTEST)
	./all_tests

gcov_report: clean
	$(CXX) $(STD) $(CFLAG) -o test $(TEST_FILES) $(GTEST) --coverage
	./test || true
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.o  *.gc* report *.a test.info \
	build *.out *.pro.user *.pro.user.* \
	*.dSYM example_file/test_cave6.txt \
	all_tests test example_file/test_maze10.txt \
	Maze_html

rebuild: clean all

leaks: tests
	CK_FORK=no leaks --atExit -- ./all_tests

clang:
	clang-format -i controller/*.h \
									model/*.cpp model/*.h \
									view/*.cpp view/*.h \
									*.cpp
	clang-format -n controller/*.h \
									model/*.cpp model/*.h \
									view/*.cpp view/*.h \
									*.cpp

check: leaks clang
