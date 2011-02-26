#include <stdio.h>

/* mycat: concatenate files */
int main(int argc, char *argv[])
{
	FILE *fp;
	void filecopy(FILE *, FILE *);
	if (argc == 1) /* no args, copy standard input */
		filecopy(stdin, stdout);
	else
		while(--argc > 0)
		{
			if((fp = fopen(*++argv, "r")) == NULL)
			{
				printf("cat: cannot open %s\n", *argv);
				return 1;
			} 
			else 
			{
				filecopy(fp, stdout);
				fclose(fp);
			}
		}
	return 0;
}
