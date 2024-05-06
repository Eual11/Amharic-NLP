CFLAGS := -g -Wall -Wextra -Wpedantic -std=c++17
all: stemmer_example normalize_example stopword_remover_example
stemmer_example: 
	g++ -DALP_STEMMER_DEBUG=1 $(CFLAGS) ./examples/stemmer_example.cpp -o ./build/$@
normalize_example:
	g++ $(CFLAGS) ./examples/normalize_example.cpp -o  ./build/$@
stopword_remover_example:
	g++ $(CFLAGS) ./examples/normalize_example.cpp -o  ./build/$@

