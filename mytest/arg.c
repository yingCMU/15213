    #include <stdio.h>
    #include <stdlib.h> /* for atoi() */

    int main(int argc,char *argv[]) {
       // int m,n;
      //  if (argc != 4) {
      //      printf("Usage: %s m n filename\n",argv[0]);
      //      return 1;
      //  }
       // m = atoi(argv[1]); /* convert strings to integers */
       // n = atoi(argv[2]);
       // printf("%s received m=%i n=%i filename=%s\n",argv[0],m,n,argv[3]);
	int index=0;
	int set,line,block=0;
	char * file;
	char * extrArg1;
	char * extrArg2;
		printf("Program name: %s\n", argv[index++]);
		printf("Program argc number: %d\n", argc);
// test number of args
	if (argc >11) {
	printf("\n invalid usage: more than 11 args\n");
		return 0;
		}
	if (argc!=9)	{
	printf("\nargc!=9\n");
	index=index+argc-9;
	}
	printf("\n index=%d\n",index);
	set=atoi(argv[++index]);
	++index;
	line=atoi(argv[++index]);
	++index;
	block=atoi(argv[++index]);
	++index;
	file=argv[++index];

printf("%s received set=%i line=%i block=%i filename=%s\n",argv[0],set,line,block,file);
	 /*
while ((argc > 1) && (argv[1][0] == '-'))
	{
		switch (argv[1][1])
		{
			case 'f':
				printf("%s\n",&argv[1][2]);
				break;

			case 'd':
				printf("%s\n",&argv[1][2]);
				printf("%s\n",&argv[1][2]);
				break;

			default:
				printf("Wrong Argument: %s\n", argv[1]);
				usage();
		}

		++argv;
		--argc;
	}
*/
	return (0);
    }


