#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/ioctl.h>
#include <signal.h>

#include "config.h"

void handlesigint() {
	printf("\x1b[0m\n");
	exit(0);
}

typedef double typefp;

int main() {

	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	
	typefp i, m, t, r, g, b;
	i = 0;
	m = 0;

	char buf[BUFLEN];
	char *c = buf;

	#ifndef FG
		#ifndef BG
			#error "Either FG or BG must be defined"
		#endif
	#endif

	#ifdef BOLD
		printf("\x1b[1m");
	#endif

	signal(SIGINT, handlesigint);

	while (fread(c, sizeof(char), BUFLEN, stdin)) {
		
		for (c = buf; c; ++c) {
		
			if (*c == '\0' || *c == 3) break; // if null or EOT
			if (*c == '\n') {
				i = 0; 
				m += YITER;
				#ifdef BG // must reset background if BG is set otherwise newlines drag the color out
					#ifdef BOLD // reenable bold
						printf("\x1b[0m\n\x1b[1m");
					#else
						printf("\x1b[0m\n");
					#endif					
				#else
					putchar('\n');
				#endif	
				continue;
			}
			#ifdef SKIPSPACES
				if (*c == ' ') {
					#ifdef BG
						#ifdef BOLD // reenable bold
							printf("\x1b[0m \x1b[1m");
						#else
							printf("\x1b[0m ");
						#endif
					#else
						putchar(' ');
					#endif	
					i += XITER;
					continue;
				}
				if (*c == '\t') {
					#ifdef BG
						#ifdef BOLD // reenable bold
							printf("\x1b[0m\t\x1b[1m");
						#else
							printf("\x1b[0m\t");
						#endif
					#else
						putchar('\t');
					#endif	
					i += XITER * 4;
					continue;
				}
			#endif

			#define FLOATTOINT(n) ((unsigned int)(n * 127) + 128)
			#define FLOAT3TOINT(a, b, c) FLOATTOINT(a), FLOATTOINT(b), FLOATTOINT(c)
			#ifdef FG
				t = cos(i + m);
				r = sin(i + m);
				g = r * cos(2*M_PI/3) + t * sin(2*M_PI/3); // sin i + m + 38deg
				b = r * cos(4*M_PI/3) + t * sin(4*M_PI/3); // sin i + m + 76deg
				printf("\x1b[38;2;%u;%u;%um", FLOAT3TOINT(r, b, g));
			#endif
			#ifdef BG
				t = cos(i + m + BGOFFSET);
				r = sin(i + m + BGOFFSET);
				g = r * cos(2*M_PI/3) + t * sin(2*M_PI/3); // sin i + m + 38deg
				b = r * cos(4*M_PI/3) + t * sin(4*M_PI/3); // sin i + m + 76deg
				printf("\x1b[48;2;%u;%u;%um", FLOAT3TOINT(r, b, g));
			#endif
			putchar(*c);

			if (i / XITER >= w.ws_col - 1) {
				m = YITER;
				i = 0;
			} else {
				i += XITER;
			}

		}
		c -= BUFLEN;
	}

	printf("\x1b[0m\x1b[1K\x1b[0E");
	return 0;
}
