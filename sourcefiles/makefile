Dicionario: dicionario.o string.o trie.o char_utils.o
	gcc -o dicionario dicionario.o string.o trie.o char_utils.o

dicionario.o: dicionario.c ./string/string.h ./trie/trie.h
	gcc -c dicionario.c

string.o: ./string/string.c ./string/string.h ./char_utils/char_utils.h
	gcc -c ./string/string.c

trie.o: ./trie/trie.c ./trie/trie.h
	gcc -c ./trie/trie.c

char_utils.o: ./char_utils/char_utils.h
	gcc -c ./char_utils/char_utils.c
