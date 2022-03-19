#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/ioctl.h>
#include <signal.h>

#define BUFLEN 5
#define XITER 0.1
#define YITER 0.5

extern void exit(int); // wow hacky
void handlesigint() {
	printf("\x1b[0m\n");
	exit(0);
}

int main() {

	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	
	float i, m;
	i = 0;
	m = 0;

	char buf[BUFLEN];
	char *c = buf;

	signal(SIGINT, handlesigint);
	printf("\x1b[1m");
	
	while (fread(c, sizeof(char), BUFLEN, stdin)) {
		
		for (c = buf; c; ++c) {
		
			if (*c == '\r' || *c == '\0') break;
			if (*c == '\n') {
				i = 0; 
				m += YITER;
				putchar('\n');
				continue;
			}
			if (*c == ' ') {
				putchar(' ');
				i += XITER;
				continue;
			}
			if (*c == '\t') {
				putchar('\t');
				i += XITER * 4;
				continue;
			}

			printf("\x1b[38;2;%u;%u;%um%c", 
				(unsigned int)(sin(i + m           ) * 127) + 128, 
				(unsigned int)(sin(i + m + 2*M_PI/3) * 127) + 128, 
				(unsigned int)(sin(i + m + 4*M_PI/3) * 127) + 128, 
				*c
			);

			if (i / XITER >= w.ws_col - 1) {
				m = YITER;
				i = 0;
			} else
				i += XITER;

		}
		c -= BUFLEN;
	}

	printf("\x1b[0m\n");

	return 0;
}
