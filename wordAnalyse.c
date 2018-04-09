#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"

int preProc(FILE *stream, char *res);

int getStrOrOper(char *fi, char *word, int (*func)(int c)){
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
	/* j表示每次预处理程序读取到的字符数量，正常情况下是25；然而可能最后一次字符不够
	*  boolean 类型的 truncate = 0 表示没有被截断； = 1表示关键字或者标识符可能被截断；= 2表示双操作符可能被截断
	*/
	int i = 0, truncate = 0, j = 0;

	while (j = preProc(stream, st)) {
		*(st + j) = 0;
		/*
		 *此处便于检测fi到达缓冲区末尾
		 */
		int a = 0;
		if (truncate == 1) {
			fi += getStrOrOper(fi, word + strlen(word), isalnum);
			if ((a = SearchHash(H, word, &a)) != -1) {
				printf("%d\t%s\n", H.elem[a].val, word);
		} else
			printf("Identify\t%s\n", word);

		}
		if(truncate == 2){
			fi += getStrOrOper(fi, word + strlen(word), ispunct);
			while((a = SearchHash(H, word, &a)) == -1){
				word[strlen(word) - 1] = 0;
				fi --;
			}
			printf("%d\t%s\n", H.elem[a].val, word);
		}

		for (; fi <= st + j;) {
			if (isalpha(*fi)) {
				fi += getStrOrOper(fi, word, isalnum);
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
					fi += getStrOrOper(fi, word, ispunct);
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
