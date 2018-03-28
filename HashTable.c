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

/*
 *
 * */
 
 void preProc(char *filename, char *res);
 
 
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
	while (H.elem[*pp].key[0] != 0 && strcmp(H.elem[*pp].key, key) != 0) {
		collision(pp);
	}
	if (!strcmp(key, H.elem[*pp].key))
		return SUCCESS;
	else
		return UNSUCCESS;
}

void collision(unsigned int *pp) {
	static int si = 1;
	*pp = (*pp + si++) % 80;
}

Status CreateHash(HashTable *H, char *filename) {
	ElemType me;
	char res[400];
	char *dilm = " \n";
	int id = 1;
	H->count = 0;
	FILE *stream;
	if((stream = fopen(filename,"r")) == NULL)
	{
		fprintf(stderr,"Can not open output file.\n");
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

int main() {
	char *filename = "test";
//	HashTable H;
//	H.elem = malloc(80 * sizeof(ElemType));
//	CreateHash(&H, filename);
//	/*for (int i = 0; i < 80; i++) {
//		if(H.elem[i].key[0] != 0)
//			printf("%d\t%s\n", H.elem[i].val, H.elem[i].key);
//	}*/
//	FILE *stream;
//	if((stream = fopen("test","r")) == NULL)
//	{
//		fprintf(stderr,"Can not open output file.\n");
//		return 0;
//	}
//	char res[12];
//	int ch;
//	for(int i = 0; (ch = fgetc(stream)) != EOF;)
//		if(ch != ' ' && ch != '\t' && ch != '\n')
//			res[i ++] = ch;
//		else {
//			while(ch = fgetc(stream) != EOF){
//				if(ch == ' ' || ch == '\t' || ch == '\n')
//					continue;
//			}
//			if(ch == EOF)
//				break;
//			ungetc(ch, stream);
//			printf("%s", res);
//		}
	char res[12] = {0};
	preProc(filename, res);
	if(res[0] != NULL)
		printf("%s\t", res);
	return 0;
}
