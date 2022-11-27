#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum { MIN_GRADE=0, MAX_GRADE=100 };

/**
 * @brief calculate the median of numbers in a file.
 * @param f the file to read from (stdin if not given a file).
 * @note Prints the median to stdout.
 */
void operate(FILE *f);

int main(int argc, char **argv) {
	FILE *f;
	
	/* check if f is a file.
	 * if given "-" or no input - read from stdin */
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
	int grades[MAX_GRADE+1] = {0};
	int counter;
	int students;
	int retval;
	int grade;
	
	counter = 0;
	students = 0;
	
	/* read numbers from f and check that they are valid grades */
	while (1) {
		retval = fscanf(f, "%d", &grade);
		if (retval == EOF) {
			break;
		} else if (retval != 1) {
			/* err - not a number */
			fprintf(stderr, "Error: In line %d: not a number\n", students+1);
			fclose(f);
			exit(1);
		} else if (grade > MAX_GRADE || grade < MIN_GRADE) {
			/* err - illegal grade */
			fprintf(stderr, "Error: In line %d: illegal grade \n", students+1);
			fclose(f);
			exit(1);
		} else {
			grades[grade]++;
		}
		students++;
	}
	/* find the median out of the histogram */
  	int i = 0;
	while(counter < (students + 1) / 2) {
		counter += grades[i];
		i++;
	}
	
	if (counter == 0) {
		printf ("No grades inputed.\n");
	} else {
		printf ("%d\n", i-1);
	}

	fclose(f);
}
