CFLAGS := -g -Wall -Wextra -Wpedantic -std=c++17
all: main
main: stopword_remover
	g++ $(CFLAGS) ./src/main.cpp -L./lib -lstopword_remover -o ./build/$@

stopword_remover:
	g++ $(CFLAGS) -c ./src/stopword_remover.cpp -o ./bin/$@.o
	ar rcs ./lib/lib$@.a ./bin/$@.o
tests:
	g++ $(CFLAGS) ./src/facet.cpp -o ./build/$@
stemmer:
	g++ $(CFLAGS) ./src/stemmer.cpp -o ./build/$@
