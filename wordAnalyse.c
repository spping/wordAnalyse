#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"

int preProc(FILE *stream, char *res);

int getSequence(char *fi, char *word, int (*func)(int c)){
	char *p = word;
	while (func(*fi) && fi != NULL) {
		*(word ++) = *(fi ++);
	}
	*word = 0;
	return strlen(p);
}

int main() {
	char *filename = "Src";
	HashTable H;
	H.elem = malloc(80 * sizeof(ElemType));
	CreateHash(&H, filename);

	FILE *stream;
	if ((stream = fopen("test", "r")) == NULL) {
		fprintf(stderr, "Can not open output file.\n");
		return 0;
	}

	char res[51] = { 0 };
	char *st = res, *fi = res;
	char word[25];
	/* use j as the counts read by "preProc.c", normally it is 25, but in the last time it may less
	 * boolean type "truncate" has 3-cases:
	 *         case:0 --> no truncate;
	 *         case:1 --> key or identify may be truncated;
	 *         case:2 --> operators or delimiter may be truncated;
	 */
	int i = 0, truncate = 0, j = 0;

	while (j = preProc(stream, st)) {
		*(st + j) = 0;
		/*
		 * easy to chech if "fi" at the end
		 */
		int a = 0;
		if (truncate == 1) {
			fi += getSequence(fi, word + strlen(word), isalnum);
			if ((a = SearchHash(H, word, &a)) != -1) {
				printf("%d\t%s\n", H.elem[a].val, word);
		} else
			printf("Identify\t%s\n", word);

		}
		if(truncate == 2){
			fi += getSequence(fi, word + strlen(word), ispunct);
			while((a = SearchHash(H, word, &a)) == -1){
				word[strlen(word) - 1] = 0;
				fi --;
			}
			printf("%d\t%s\n", H.elem[a].val, word);
		}

		if (truncate == 3)
		{
			fi += getSequence(fi, word + strlen(word), isdigit);
			printf ("Number!\t%s\n", word);
		}

		for (; fi <= st + j;) {
			if (isdigit(*fi))
			{
				fi += getSequence(fi, word, isdigit);
				if (fi == st + 25)
				{
					truncate = 3;
					break;
				}

				printf ("Number!\t%s\n", word);
			}
			if (isalpha(*fi)) {
				fi += getSequence(fi, word, isalnum);
				if (fi == st + 25) {
					truncate = 1;
					break;
				}
				int a;
				if ((a = SearchHash(H, word, &a)) != -1) {
					printf("%d\t%s\n", H.elem[a].val, word);
				} else
					printf("Identify!\t%s\n", word);
			} else {
				if(ispunct(*fi)){
					fi += getSequence(fi, word, ispunct);
				        int a = 0;
					while((a = SearchHash(H, word, &a)) == -1){
						word[strlen(word) - 1] = 0;
						fi --;
					}

					if(fi == st + 25){
						truncate = 2;
						break;
					}
					printf("%d\t%s\n", H.elem[a].val, word);


				} else fi ++;
				continue;
			}

		}
		if (res == st)
			st += 25;
		else {
			st = res;
			fi = res;
		}
	}
	return 0;
}
