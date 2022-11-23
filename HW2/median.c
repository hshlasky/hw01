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
	int grades[MAX_GRADE] = {0};
	int counter = 0;
	int students = 0;
	int retval;
	int grade;
	
	while (1) {
		retval = fscanf(f, "%d", &grade);
		if (retval == EOF) {
			break;
		} else if (retval != 1) {
			/* err */
			fprintf(stderr, "Error: not a number\n");
			exit(1);
		} else {
			grades[grade]++;
		}
		students++;
	}
  
	for (int i = 0;i < MAX_GRADE;i++) {
		counter += grades[i];
		if (counter >= (students + 1) / 2) {
			grade = i;
			break;
		}
	}

	if (counter == 0) {
		printf ("No grades inputed.\n");
	} else {
		printf ("%d\n", grade);
	}

	fclose(f);
}
