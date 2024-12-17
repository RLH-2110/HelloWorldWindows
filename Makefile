
all:
	gcc main.c -o main.exe -pedantic -lgdi32

PHONY: clean clear run

run: all
	./main.exe	

clear: clean
clean:
	rm main.exe