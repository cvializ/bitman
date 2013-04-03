target all:
	gcc -Werror -Wall -std=c99 --static -o bitman main.c scanner.c parser.c hexnumber.c
