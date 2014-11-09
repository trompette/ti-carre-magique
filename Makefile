all:
	$(TIGCC)/bin/tigcc -O2 -Wall game.c game_io.c carremag.c -o carremag
