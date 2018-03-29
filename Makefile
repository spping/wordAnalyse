objects = HashTable.o preProc.o

%.o:%.c
	$(CC) $(CFLAGS) -g -c $< -o $@

wordAnalyse:$(objects)
	cc -g -o wordAnalyse $(objects)
HashTable.o:hashtable.h
preProc.o:preProc.c
