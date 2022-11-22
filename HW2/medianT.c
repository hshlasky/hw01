#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum { MIN_GRADE=0, MAX_GRADE=100 };

void operate(FILE *f);

int main(int argc, char **argv) {
	FILE *f;

	if (argc == 1 || !strcmp("-", argv[1])) {
		f = stdin;
	} else {
		f = fopen(argv[1], "r");
	}
	/* err check */
	if (!f ) {
		fprintf(stderr,"File note found: \"%s\"\n", argv[1]);
		return 1;
	}
	operate(f);
}

void operate(FILE *f) {
	int grade;
	int retval;
	int med_num;
	int line_n = 0;
	int ch=0, ch_n=0;
	int counter = 0;
    FILE *fp = f;
    

  while ((ch = fgetc(fp)) != EOF) {
     if ((ch == '\n')&&(ch_n != '\n')){
        line_n++;
     }
     ch_n=ch;
    }
    if(ch_n != '\n') {
      line_n++;  
    }
  	printf("grade num2: %d \n", line_n);
  	
  	med_num = (line_n+1)/2 ;
  	
  	
  	
  
  
}
