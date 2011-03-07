all: wordcomplete.o

wordcomplete.o: wordcomplete.c
	gcc `pkg-config --cflags --libs x11` -o wordcomplete wordcomplete.c
