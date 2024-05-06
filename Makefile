CFLAGS := -g -Wall -Wextra -Wpedantic -std=c++17
all: stemmer_example normalize_example stopword_remover_example decomposing_example composing_example
stemmer_example: 
	g++ -DALP_STEMMER_DEBUG=1 -DALP_ENABLE_SUGGESTION $(CFLAGS) ./examples/stemmer_example.cpp -o ./build/$@
normalize_example:
	g++ $(CFLAGS) ./examples/normalize_example.cpp -o  ./build/$@
stopword_remover_example:
	g++ $(CFLAGS) ./examples/stopword_remover_example.cpp -o  ./build/$@
decomposing_example:
		g++ $(CFLAGS) ./examples/decomposing_example.cpp -o  ./build/$@
composing_example:
		g++ $(CFLAGS) ./examples/composing_string_example.cpp -o  ./build/$@


