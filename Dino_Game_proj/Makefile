CC = gcc
CFLAGS = -I.
DEPS = conio_repl.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Dino_Game_Final: Dino_Game_Final.o conio_repl.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f Dino_Game_Final.o conio_repl.o 

