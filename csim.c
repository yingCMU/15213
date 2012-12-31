#include "cachelab.h"

/*
*int main()
*{
*	printSummary(0, 0, 0);
*	return 0;
*}
*/
/*
 * getopt.c
 * 
 * Copyright 2012 lily <lily@localhost.localdomain>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

    typedef struct{
	int valid ;
	unsigned long tag ;
	int lru ;

	}Line;
/*
 * one cache set has E Lines 
 */
	typedef struct{
	Line* lines ;
	int timer;
	}Set;

int hitC, missC, evictC=0;
int s = 0, b = 0, E = 0, t = 0;
 int setSize = 0, blockSize = 0;
 const int  m = sizeof(long) * 8;
Set *sets = NULL;
unsigned long setMask = 0, tagMask = 0; 
FILE * trace=NULL;



void maskSetup(){
	 printf("%ld",tagMask);  
      setMask=(1L<<(s+b))-(1L<<b);
      t=m-s-b;
      tagMask = (1L << 63 >> (t-1));
      printf("\n!!setMASK  %lx\n",setMask); 
      }
void mallocInit(){
	sets = (Set *)malloc(setSize * sizeof(Set));
	if(sets == NULL){
		fprintf(stderr, "malloc error");
	}
	// malloc initialization
     int i=0;
    	while (i < setSize){
		Set *set = (sets + i);
		set->lines = (Line *)malloc(E * sizeof(Line));
		if(set->lines == NULL){
			fprintf(stderr, "malloc error");
		}	
		set->timer = 0;
		int j = 0;
		while( j < E){
			Line *line = (set->lines + j);
			line->valid = 0;
			line->tag = 0;
			line->lru = 0;
			j++;
		}
		i++;
	} // malloc initialization
	return;
}

void cache(unsigned long mem_addr){
	unsigned long set_id, tag_id;
	set_id = (setMask & mem_addr) >> b;
	tag_id = tagMask & mem_addr;
	printf("\n in cache mem_addr>> %lx; set_mask>> %lx;   tag_mask >>%lx \n",mem_addr,setMask, tagMask);
	Set *set = sets + set_id;
	//printf( "here1 !\n");
	//should be a pointer
	Line *line;
	//printf( "here3 !\n");
	//error in this line
	//printf("! here %p",set);
	int i = 0, lru_line = 0, current_lru = set->lines->lru;
	//printf( "here4 !\n");
	while(i < E){
		line = set->lines + i;
		if(line->valid == 0){//cold miss		
			line->tag = tag_id;//fill cache
			line->valid = 1;
			set->timer++;
			line->lru = set->timer;
			missC++;
			printf("  miss \n");
			printf("tag_id %lx \n",tag_id);
						printf("  -------------------------- \n");
			return;
		}else if(line->tag == tag_id){
			//hit
			set->timer++;
			line->lru = set->timer;
			hitC++;
			printf("  hit \n");
			printf("\ntag_id %lx \n",tag_id);
			printf("  -------------------------- \n");
			return;
		}else if(line->lru < current_lru){
			//unhit
			current_lru = line->lru;
			lru_line = i;
		printf("  miss  ");
		}
		i++;
	}
	//printf( "here2 !\n");
	//evict here
	evictC++;
        missC++;
        line = set->lines + lru_line;
	line->tag = tag_id;
	set->timer++;
	line->lru = set->timer;
	printf("  evictions\n");
	printf("  -------------------------- \n");

	return;
	 }


  void traceFun(FILE *file){
	 if(file == NULL){
     
     exit(-1);
	 }
	else{
		// printf( "trace file open !\n");
		char line[30];
		
		
		while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
		{
		fputs ( line, stdout ); /* write the line */
		//printf("!!!   >%c \n ",*(line+1));
		if(*line=='I')
		continue;
		
		else if(*(line + 1) == 'M'){
			*(line+1)='0';
			*(line+2)='x';
			//char * sp=(line+1)
			char * ep=strchr(line, ',');
			
			//	
				*ep='\0';
				//printf(" now line  %s \n ",line);	
				
				//strcat(memStr,sp);
			//	printf("now   %s \n ",(line+1));
			//	printf("memstr  %s \n ",(line+1));
				unsigned long mem_addr = 0;
				
				mem_addr =strtoul((line+1), NULL, 0);
				
				//printf("mem address   %ld  %lx \n ",mem_addr ,mem_addr );
			cache(mem_addr);
			cache(mem_addr);
			//printf("come here\n");
			}
			
			else{*(line+1)='0';
			*(line+2)='x';
			//char * sp=(line+1)
			char * ep=strchr(line, ',');
			
			//	
				*ep='\0';
				//printf(" now line  %s \n ",line);	
				
				//strcat(memStr,sp);
			//	printf("now   %s \n ",(line+1));
			//	printf("memstr  %s \n ",(line+1));
				unsigned long mem_addr = 0;
				
				mem_addr =strtoul((line+1), NULL, 0);
				
				//printf("mem address   %ld  %lx \n ",mem_addr ,mem_addr );
			cache(mem_addr);
				
			}
		}//while readline
		
	    }// if not "I"
	
  
	  fclose ( file );
	  return;
  }

  int main (int argc, char **argv)
     { 
		int vflag=0,hflag=0; 
       printf("%d %d ",vflag,hflag);
       char *argValue = NULL;
       int index;
       int c;
     
       opterr = 0;
          
      
       
     
     while((c = getopt(argc, argv, "vhb:s:E:t:")) != -1){
		switch(c){
			 case 'v':
			 printf("\n -v \n");
             vflag = 1;
             break;
             case 'h':
             printf("\n -h \n");
             hflag = 1;
             break;
			case 's':
				argValue = optarg;
				s = atoi(argValue);
				if(s < 0 && s > m ){
					printf("s should between 0 and word length\n");
					exit(-1);
				}
				setSize = 1 <<	s;		
				break;
			case 'E':
				argValue = optarg;
				E = atoi(argValue);
				if(E < 1){
					printf("E should larger than 0\n");
					exit(-1);
				}
				break;
			case 'b':
				argValue = optarg;
				b = atoi(argValue);
				blockSize = 1 << b;	
				if(b < 0 && b > m){
					printf("b should between 0 and word length\n");
					exit(-1);
				}
				break;
			case 't':
				maskSetup();
				argValue = optarg;
				trace = fopen(argValue, "r");
				if(trace == NULL){
					printf( "%s open error!\n", argValue);
					exit(-1);
				}
				mallocInit();
				traceFun(trace);
				break;
           case '?':
             if (optopt == 'c')
               fprintf (stderr, "Option -%c requires an argument.\n", optopt);
             else if (isprint (optopt))
               fprintf (stderr, "Unknown option `-%c'.\n", optopt);
             else
               fprintf (stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
             return 1;
           default:
             abort ();
           } // swith
     } // while
     
     
    
      printf ("\nset = %d, line = %d, block = %d,   \n",
              s, E, b);
     
       for (index = optind; index < argc; index++)
         printf ("Non-option argument %s\n", argv[index]);
         
     
      printSummary(hitC, missC, evictC);;
	//free	malloc memory
	/*int i=0;
	while (i < setSize){
		Set *set = (sets + i);
		free(set->lines);
	}*/
	free(sets);
	printf("/n hh come here\n");
	return 0;
     }
     
     
     
