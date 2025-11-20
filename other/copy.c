#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	if (argc < 3) {
		printf ("argc err\n");
	}

	FILE *in, *out;
	int c;

	in = fopen (argv[1], "r");
	out = fopen (argv[2], "w");
	if (!in) {
		perror (argv[1]);
		exit (1);
	}

	while ((c = fgetc (in)) != EOF) {
		if (fputc (c, out) < 0) exit (1);
	}

	fclose (in);
	fclose (out);

	exit (0);
}
