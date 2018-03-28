#include <stdio.h>

void preProc(char *filename, char *res){
	FILE *stream;
	if((stream = fopen("D:/sping/c1/test","r")) == NULL)
	{
		fprintf(stderr,"Can not open output file.\n");
		return ;
	}
	int ch;
	for(int i = 0; (ch = fgetc(stream)) != EOF; ){
		if(ch == '/'){
			ch = fgetc(stream);
			if(ch != '*'){
				ungetc(ch, stream);
			}
			if(ch == '*'){
				while(fgetc(stream) != '*' || fgetc(stream) != '/')
					;
				continue;
			}
		}
		if(ch != ' ' && ch != '\t' && ch != '\n')
			res[i ++] = ch;
		else {
			while((ch = fgetc(stream)) != EOF){
				if(ch == ' ' || ch == '\t' || ch == '\n'){
					continue;
				}
				break;
			}
			if(ch == EOF)
				break;
			ungetc(ch, stream);
			res[i] = 0;

			i = 0;
		}

	}
}
