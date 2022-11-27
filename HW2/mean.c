#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum { MIN_GRADE=0, MAX_GRADE=100 };

void operate(FILE *f);

/**
 * @brief Accepts inputs from file or stdin.
 * @param argc Number of inputs.
 * @param argc Inputs as strings.
 */
int main(int argc, char **argv) {
	FILE *f;

	if (argc == 1 || !strcmp("-", argv[1])) {
		f = stdin;
	} else {
		f = fopen(argv[1], "r");
	}
	/* error file check */
	if (!f ) {
		fprintf(stderr,"File note found: \"%s\"\n", argv[1]);
		return 1;
	}
	operate(f);
}

/**
 * @brief Calculate the average.
 * @param *f file pointer.
 * @note Prints avg to stdout.
 */
void operate(FILE *f) {
	int grade;
	int retval;
	double avg;
	int line_n;	
	avg = 0;
	line_n = 0;
	
	// scan all the grade, check validity, and sum all the grades 
	while (1) {
		retval = fscanf(f, "%d", &grade);
		if (retval == EOF) {
			break;
		} else if (retval != 1) {
			/* check error - not a number */
			fprintf(stderr, "Error: In line %d: not a number \n", line_n);
			fclose(f);
			exit(1);
		
		/* check error - grade range */
		} else if (grade > MAX_GRADE || grade < MIN_GRADE) {
			fprintf(stderr, "Error: In line %d: illegal grade \n", line_n);
			fclose(f);
			exit(1);
		}
		
		avg += grade;
		line_n++;
	}
	
	/* if not grade input line_n will be zero */
    if (line_n == 0) {
        printf ("No grade inputed.");
	}
	
	/* calculate the average.*/
    else {
        printf("%.2lf\n", avg / line_n);
	}
	
	fclose(f);
}
