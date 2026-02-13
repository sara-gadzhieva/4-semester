#include <stdio.h>
int main(int argc,char **argv) {
	char *s="abc";
	printf("%s\n",s);
	s[1]='d';
	printf("%s\n",s);
	/**printf("кол-во переданных в функцию параметров:%d\n",argc);
	printf("переданные параметры:\n");
	for(int i=0;i<argc;i++) printf("%d: %s\n",i,argv[i]);**/
	return 0; 
	}
