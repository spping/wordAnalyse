#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_BUF_LEN 25

int preProc(FILE *stream, char *res) {
	int ch, j = 0;
	for (int i = 0; i < MAX_BUF_LEN && (ch = fgetc(stream)) != EOF;) {
		if (ch == '/') {
			ch = fgetc(stream);
			if (ch != '*') {
				ungetc(ch, stream);
			}
			if (ch == '*') {
				while (fgetc(stream) != '*' || fgetc(stream) != '/')
					;
				continue;
			}
		}
		if (!isspace(ch)) {
			res[i++] = ch;
			j++;
		} else {
			while ((ch = fgetc(stream)) != EOF) {
				if (isspace(ch)) {
					continue;
				}
				break;
			}
			if (ch == EOF)
				break;
			ungetc(ch, stream);
			if (i == 0)
				continue;
			res[i] = ' ';
			i++;
			j++;
		}

	}
	return j;
}
