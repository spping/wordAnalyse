/*
 * HashTable.c
 *
 *  Created on: 2018年3月23日
 *      Author: freaky
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"
/*
 *
 * */
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
	if (SearchHash(*H, elem.key, &p) != -1)
		return DUPLICATE;
	else {
		H->elem[p] = elem;
		++H->count;
		return OK;
	}
}

int SearchHash(HashTable H, char *key, unsigned int *pp) {
	*pp = hash(key);
	int si = 1;
	while (H.elem[*pp].key[0] != 0 && strcmp(H.elem[*pp].key, key) != 0) {
		collision(si, pp);
		si++;
	}
	if (!strcmp(key, H.elem[*pp].key))
		return *pp;
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
