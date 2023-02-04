NAME 	=	simple_navigator

GRAPH_LIB = s21_graph.a

ALGO_LIB = s21_graph_algorithms.a

SRC 	=  	main.cpp \
			interface/console_interface.cpp\

OBJ 	= $(patsubst %.cpp,%.o,$(SRC))

SRC_GRAPH = graph/s21_graph.cpp\

OBJ_GRAPH	= $(patsubst %.cpp,%.o,$(SRC_GRAPH))

SRC_ALGO = graph_algorithms/s21_graph_algorithms.cpp\
			aco/colony.cpp\
            aco/ant.cpp\

OBJ_ALGO 	= $(patsubst %.cpp,%.o,$(SRC_ALGO))

HEADER  =	interface/console_interface.h\
			graph_algorithms/s21_graph_algorithms.h\
            containers/node.h\
            containers/simple_stack/simple_stack.h\
            containers/simple_queue/simple_queue.h\
            aco/colony.h\
            aco/ant.h\
            graph/s21_graph.h\

CFLAGS	= 	-Wall -Wextra -Werror -g3

TEST_FLAGS = -fprofile-arcs -ftest-coverage

CSTD	= 	-std=c++17

all: $(NAME)

format : $(SRC) $(SRC_GRAPH) $(SRC_ALGO) main.cpp tests/tests.cpp $(HEADER)
	clang-format -style=google -n $(SRC) $(SRC_GRAPH) $(SRC_ALGO) $(HEADER) tests/tests.cpp

test : $(SRC_ALGO) $(SRC_GRAPH) tests/tests.cpp clean
	c++ $(CSTD) $(TEST_FLAGS) tests/tests.cpp $(SRC_ALGO) $(SRC_GRAPH) -lgtest -lpthread -o test
	./test
	lcov --no-external -c -d . -o tests.info
	genhtml tests.info -o coverage
	rm -rf *.gcda *.gcno

s21_graph.a : $(OBJ_GRAPH)
	ar rc $@ $(OBJ_GRAPH)
	ranlib $@

s21_graph_algorithms.a : $(OBJ_ALGO)
	ar rc $@ $(OBJ_ALGO)
	ranlib $@

$(NAME): $(OBJ) s21_graph.a s21_graph_algorithms.a
	c++ $(CFLAGS) $(CSTD) $(OBJ) $(ALGO_LIB) $(GRAPH_LIB) -o $@

%.o: %.cpp Makefile $(HEADER)
	c++ $(CFLAGS) $(CSTD) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJ_ALGO) $(OBJ_GRAPH) $(NAME)
	rm -rf test coverage *.a *.gcno *.gcda *.info *.png *.dot


