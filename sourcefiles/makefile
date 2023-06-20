Dicionario: dicionario.o string.o trie.o
	gcc -o dicionario dicionario.o string.o trie.o

dicionario.o: dicionario.c ./string/string.h ./trie/trie.h
	gcc -c dicionario.c

string.o: ./string/string.c ./string/string.h
	gcc -c ./string/string.c

trie.o: ./trie/trie.c ./trie/trie.h
	gcc -c ./trie/trie.c
