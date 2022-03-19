build:
	gcc main.c -o rainbow -s -lm -ffast-math -O3

run:
	cat text.txt | ./rainbow

time:
	time cat text.txt | ./rainbow

install:
	-rm "/usr/local/bin/rainbow"
	ln -s "`pwd`/rainbow" "/usr/local/bin/rainbow"
