/*
 * HashTable.c
 *
 *  Created on: 2018年3月23日
 *      Author: freaky
 */
#include "hashtable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
 *
 * */

int preProc(FILE *stream, char *res);

unsigned int hash(char* str) {
	unsigned int hash = 0;
	int i;

	for (i = 0; *str; i++) {
		if ((i & 1) == 0) {
			hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
		} else {
			hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
		}
	}

	return (hash & 0x7FFFFFFF) % 80;
}

Status InsertHash(HashTable *H, ElemType elem) {

	unsigned int p;
	if (SearchHash(*H, elem.key, &p))
		return DUPLICATE;
	else {
		H->elem[p] = elem;
		++H->count;
		return OK;
	}
}

Status SearchHash(HashTable H, char *key, unsigned int *pp) {
	*pp = hash(key);
	int si = 1;
	while (H.elem[*pp].key[0] != 0 && strcmp(H.elem[*pp].key, key) != 0) {
		collision(si, pp);
		si++;
	}
	if (!strcmp(key, H.elem[*pp].key))
		return SUCCESS;
	else
		return UNSUCCESS;
}

void collision(int si, unsigned int *pp) {
	*pp = (*pp + si) % 80;
}

Status CreateHash(HashTable *H, char *filename) {
	ElemType me;
	char res[400];
	char *dilm = " \n";
	int id = 1;
	H->count = 0;
	FILE *stream;
	if ((stream = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "Can not open output file.\n");
		return 0;
	}
	res[fread(res, 1, 400, stream)] = 0;
	fclose(stream);
	for (int i = 0; i < 80; i++) {
		H->elem[i].key[0] = 0;
	}
	char *k = strtok(res, dilm);
	strcpy(me.key, k);
	me.val = id;
	InsertHash(H, me);
	while ((k = strtok(NULL, dilm)) != NULL) {
		strcpy(me.key, k);
		me.val = ++id;
		InsertHash(H, me);
	}

	return OK;
}

int keyOrIdentify(char *fi, char *word){
	char *p = word;
	while (isalnum(*fi) && fi != NULL) {
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
	for (int i = 0; i < 80; i++) {
		if (H.elem[i].key[0] != 0)
			printf("%d\t%s\n", H.elem[i].val, H.elem[i].key);
	}
	FILE *stream;
	if ((stream = fopen("test", "r")) == NULL) {
		fprintf(stderr, "Can not open output file.\n");
		return 0;
	}

	char res[50] = { 0 };
	char *st = res, *fi = res;
	char word[25];
	/* j表示每次预处理程序读取到的字符数量，正常情况下是25；然而可能最后一次字符不够
	*  boolean 类型的 truncate = 0 表示没有被截断； = 1表示关键字或者标识符可能被截断；= 2表示双操作符可能被截断
	*/
	int i = 0, truncate = 0, j = 0;

	while (j = preProc(stream, st)) {
		*(st + j) = 0;
		if (truncate == 1) {
			fi += keyOrIdentify(fi, word + strlen(word));
			int a = 0;
			if (SearchHash(H, word, &a)) {
				printf("Find!\n");
			} else
				printf("NoResults!\n");
		}
		for (; fi <= st + j;) {
			if (isalpha(*fi)) {
				fi += keyOrIdentify(fi, word);
				if (fi == st + 25) {
					truncate = 1;
					break;
				}
				int a;
				if (SearchHash(H, word, &a)) {
					printf("Find!\n");
				} else
					printf("NoResults!\n");
			} else {
				fi++;
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
