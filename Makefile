objects = wordAnalyse.o HashTable.o preProc.o

%.o:%.c
	$(CC) $(CFLAGS) -g -c $< -o $@

wordAnalyse:$(objects) TAGS
	cc -g -o wordAnalyse $(objects)
TAGS:*.[chCH]
	find . -name "*.[chCH]" -print | etags -
