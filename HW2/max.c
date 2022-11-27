#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum { MIN_GRADE=0, MAX_GRADE=100 };

void operate(FILE *f);

/**
 * @brief Accepts inputs from file or stdin.
 * @param argc Number of inputs.
 * @param argc Inputs as strings.
 * @note ?? .
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
 * @brief Found the maximum grade.
 * @param *f file pointer.
 * @note ?? .
 */
void operate(FILE *f) {
    int max;
    int grade;
    int line_n;
    int retval;
    
    max = MIN_GRADE-1;
    line_n = 0;
	
	// scan all the grade, check validity, and save the min grade 
    while (1) {
		retval = fscanf(f, "%d", &grade);
		if (retval == EOF) {
			break;
	
		/* check error - not a number */
		} else if (retval != 1) {
			fprintf(stderr, "Error: In line %d: not a number \n", line_n+1);
			fclose(f);
			exit(1);
		
		/* check error - grade range */
		} else if (grade > MAX_GRADE|| grade < MIN_GRADE) {
			fprintf(stderr, "Error: In line %d: illegal grade \n", line_n+1);
			fclose(f);
			exit(1);
		
		/* check if this minimum grade */
		} else if (grade > max) {
		    max = grade;
		}
		line_n++;
    }
	
	/* if not grade input the minimum will be under
	the min legal grade */
	if (max < MIN_GRADE) {
	    printf ("No grades inputed.");
	} else {
    	printf ("%d", max);
	}
	
	fclose(f);
}
