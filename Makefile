
all:
	gcc main.c -o main.exe -pedantic

PHONY: clean clear run

run: all
	./main.exe	

clear: clean
clean:
	rm main.exe