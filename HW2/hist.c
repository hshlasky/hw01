#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *f;
static int nbins = 10;

/**
 * @brief Split grades into n_bins.
 * @param bins Pointer to the array that holds the histogram.
 * @note Prints the histogram to stdout.
 */
void operate(int *bins);

/**
 * @brief Accepts inputs from file or stdin and defines the number of bins (default 10).
 * @param argc Number of inputs.
 * @param argc Inputs as strings.
 * @note If .
 */
void parse_arg(int argc, char **argv) {
	f = stdin;
	for (int i=0; i<argc; i++) {
		if(argc == 1 || !strcmp(argv[i], "-")) {
			f = stdin;
		} else if (!strcmp(argv[i], "-n_bins")) {
			nbins = (i<argc-1) ? atoi(argv[i+1]) : 10;
			i++;
		} else {
			f = fopen(argv[i], "r");
			}
		}
 }
int main(int argc, char **argv) {
	parse_arg(argc, argv);
	/*err check*/
	if(!f) {
	   fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
	   return 1;
	}
	/* Initiate array */
	int *bins = (int*)malloc(sizeof(int)*nbins);
	for (int i=0; i<nbins; ++i) {
		bins[i] = 0;
	}
	operate(bins);
	free(bins);
}

void operate(int *bins) {

	int grade;
	int retval;
	double pace;

	while (1) {
		retval = fscanf(f, "%d", &grade);
		if (retval == EOF) {
			break;
		} else if (retval != 1) {
		/* err */
		fprintf(stderr, "Error: not a number\n");
		exit(1);
		}
		/* Find bins */
		int n = grade / (100 / nbins);
		bins[n]++;
	}
	/* Print bins */
	pace = 100.0 / nbins;
		for (int i=0; i<nbins; ++i) {
			printf("%.0lf-%.0lf\t%d\n",
				i * pace,
				(i < nbins - 1) ? ((i+1) * pace-1) : 100,
				bins[i]);
	}
}
