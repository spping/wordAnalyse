/*
 * hashtable.h
 *
 *  Created on: 2018年3月23日
 *      Author: freaky
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

typedef struct {
	int val;
	char key[12];
}ElemType;
typedef struct {
	ElemType *elem;
	int count;
	int sizeindex;
}HashTable;

typedef int Status;

#define SUCCESS 	1
#define UNSUCCESS 	0
#define DUPLICATE  -1
#define OK			1

unsigned int hash(char *str);
void collision(int si, unsigned int *pp);

Status SearchHash(HashTable H, char *key, unsigned int *p);
Status InsertHash(HashTable *H, ElemType elem);
Status CreateHash(HashTable *H, char *);


#endif /* HASHTABLE_H_ */
