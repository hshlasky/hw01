#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum { MIN_GRADE=0, MAX_GRADE=100 };

void operate(FILE *f);

int main(int argc, char **argv) {
	FILE *f;

	if (argc == 1 || strcmp("-", argv[1])) {
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
	double avg;
	int line_n;

	avg = 0;
	line_n = 0;
	while (1) {
		retval = fscanf(f, "%d", &grade);
		if (retval == EOF) {
			break;
		} else if (retval != 1) {
			/* err - not a number */
			fprintf(stderr, "Error: In line %d: not a number \n", line_n);
			exit(1);
		}
		else if (grade > MAX_GRADE || grade < MIN_GRADE) {
			/* err - illegal grade */
			fprintf(stderr, "Error: In line %d: illegal grade \n", line_n);
			exit(1);
		}
		
		avg += grade;
		line_n++;
	}
	
    if (line_n == 0) {
        printf ("No grade inputed.");
	}
	
    else {
        printf("%.2lf\n", avg / line_n);
	}
}
