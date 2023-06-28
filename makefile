Dicionario: dicionario.o string.o trie.o char_utils.o menu_utils.o
	gcc -o dicionario dicionario.o string.o trie.o char_utils.o menu_utils.o

dicionario.o: dicionario.c sourcefiles/string/string.h sourcefiles/trie/trie.h sourcefiles/menu_utils/menu_utils.h
	gcc -c dicionario.c

string.o: sourcefiles/string/string.c sourcefiles/string/string.h sourcefiles/char_utils/char_utils.h
	gcc -c sourcefiles/string/string.c

trie.o: sourcefiles/trie/trie.c sourcefiles/trie/trie.h
	gcc -c sourcefiles/trie/trie.c

char_utils.o: sourcefiles/char_utils/char_utils.c sourcefiles/char_utils/char_utils.h
	gcc -c sourcefiles/char_utils/char_utils.c

menu_utils.o: sourcefiles/menu_utils/menu_utils.c sourcefiles/menu_utils/menu_utils.h
	gcc -c sourcefiles/menu_utils/menu_utils.c
