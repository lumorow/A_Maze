CC = g++
CFLAG = -Wall -Wextra -Werror
UNAME:= $(shell uname -s)
BD=build/

ifeq ($(UNAME), Linux)
OPEN_CMD = xdg-open
ADD_LIB = -lm -lrt -lpthread -D_GNU_SOURCE
leaks_util := valgrind --leak-check=full
endif

ifeq ($(UNAME), Darwin)
OPEN_CMD = open
leaks_util := CK_FORK=no leaks --atExit --
endif

all: install

tests: clean
	$(CC) tests/mazeTest.cc model/cave/cave.cc model/maze/maze.cc model/maze/solver.cc model/matrix.cc -o test -lgtest
	$(leaks_util) ./test

install: clean $(BD)
	cp -r view/* build
	cd build; qmake; make;
	cp -r  ./build/Maze.app .

uninstall: clean
	rm -rf ./view/view.app

dvi: 
	$(OPEN_CMD) dvi.html


dist: install
	@rm -rf Maze.tar.gz
	tar -czvf Maze.tar.gz Maze.app dvi.html
	@rm -rf Maze.app


./$(BD):
	mkdir $(BD)

clang:
	@cp -f ../materials/linters/.clang-format . && \
	clang-format -i */*.cc */*.h; \
	clang-format -n */*.cc  */*.h; \
	rm -f .clang-format

cppcheck:
	@cppcheck --enable=all --suppress=unusedFunction --suppress=missingInclude ../src/

leaks:
	$(leaks_util) ./test

clean:
	@rm -rf *.o *.gcda *.gcno *.info clang-format suppression.cfg
	@rm -rf ./build/*
	@rm -rf ./build_tests/*
	@rm -rf Maze.tar.gz
	@rm -rf Maze.app
	@rm -f suppression.cfg
	@rm -rf Maze
	@rm -f clang-format
	@rm -f ./test

rebuild: clean all
