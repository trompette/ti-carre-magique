CC:=docker run --rm --volume $(shell pwd):/opt trompette/tigcc:latest
CFLAGS:=-O2 -Wall
SRC:=$(wildcard *.c)

carremag:
	$(CC) $(CFLAGS) $(SRC) -o $@

docker-image:
	docker build . -t trompette/tigcc:latest
