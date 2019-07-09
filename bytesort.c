#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#define NORMAL 0
#define COMPACT 1
#define HEX 2
#define PRINTABLE 4
#define NEWLINE 8
int mode;

inline void help()
{
	puts(
		"Sorts all the bytes from STDIN and writes them to STDOUT.\n\n"

		"  -h, --help       Shows this message.\n"
		"  -c, --compact    Prints each character only once followed by the\n"
		"                   number of times it appears. (aaaaa --> a:5)\n"
		"  -x, --hex        Replaces each byte with it hex code in compact mode.\n"
		"  -p, --printable  Ignored all bytes outside the range of printable\n"
		"                   ASCII characters [0x21; 0x7E].\n"
		"  -n, --newline    Adds a newline to the end of the output.\n\n"

		"WARNING: This program may exit with an error when attempting\n"
		"         to sort more than 18447 Petabytes of data.\n"
	);

	exit(0);
}

inline void setup(int argc, char **argv)
{
	mode = NORMAL;

	for(int i=1; i<argc; i++)
	{
		if(strcmp(argv[i], "-h")==0 || strcmp(argv[i], "--help")==0)
		{
			printf("Usage: cat [FILE] | %s [OPTION]...\n\n", argv[0]);
			help();
		}

		else if(strcmp(argv[i], "-c")==0 || strcmp(argv[i], "--compact"  )==0)mode |= COMPACT;
		else if(strcmp(argv[i], "-x")==0 || strcmp(argv[i], "--hex"      )==0)mode |= HEX;
		else if(strcmp(argv[i], "-p")==0 || strcmp(argv[i], "--printable")==0)mode |= PRINTABLE;
		else if(strcmp(argv[i], "-n")==0 || strcmp(argv[i], "--newline"  )==0)mode |= NEWLINE;

		else
		{
			fprintf(stderr,
				"Unable to parse argument: %s\n"
				"Try '%s --help' for more information.\n",
			argv[i], argv[0]);

			exit(-1);
		}
	}
}

inline void spam(char c, uint64_t n, char *buff, int len)
{
	if(n > 64)
	{
		if(len > n)len = n;
		memset(buff, c, len);

		while(n >= len)
		{
			fwrite(buff, 1, len, stdout);
			n -= len;
		}
	}

	while(n > 8)
	{
		putchar(c);
		putchar(c);
		putchar(c);
		putchar(c);
		putchar(c);
		putchar(c);
		putchar(c);
		putchar(c);
		n -= 8;
	}

	while(n > 0)
	{
		putchar(c);
		n--;
	}
}

inline void feed(uint64_t *hist)
{
	int byte = 0;
	int p_check = mode & PRINTABLE;

	for(uint64_t i=0; i<UINT64_MAX; i++)
	{
		byte = getchar();
		if(byte == EOF)return;

		if(p_check)
		{
			if(byte < 0x21 || byte > 0x7E)
				continue;
		}

		hist[byte]++;
	}

	while(1)
	{
		byte = getchar();
		if(byte == EOF)return;
	
		if(p_check)
		{
			if(byte < 0x21 || byte > 0x7E)
				continue;
		}

		if(hist[byte] == UINT64_MAX)
		{
			perror("Too many bytes to sort");
			exit(-1);
		}

		hist[byte]++;
	}
}

int main(int argc, char *argv[])
{
	setup(argc, argv);

	uint64_t *hist = calloc(0x100, sizeof(uint64_t));

	feed(hist);

	if(mode & COMPACT)
	{
		int hexmode = mode & HEX;

		for(int i=0; i<0x100; i++)
		{
			if(hist[i] == 0)continue;

			if(hexmode)printf("%02X", i);
			else putchar((char)i);

			printf(":%" PRIu64 " ", hist[i]);
		}	
	}

	else
	{
		const int size = 4096;
		char *buff = malloc(size);

		for(int i=0; i<0x100; i++)
		{
			if(hist[i] == 0)continue;
			spam((char)i, hist[i], buff, size);
		}

		free(buff);
	}

	free(hist);

	if(mode & NEWLINE)
	{
		putchar('\n');
	}

	exit(0);
}
