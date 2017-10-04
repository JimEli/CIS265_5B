/*************************************************************************
* Title: (CIS265_5B) Polynomial Calculator.
* File: main.c
* Author: James Eli
* Date: 8/28/2017
*
* Write a function that computes the value of the following polynomial:
*   3x^5 + 2x^4 – 5x^3 – x^2 +7x – 6
* Write a program that asks the user to enter a value for x, calls the
* function to compute the value of the polynomial, and then displays the 
* value returned by the function.
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141), using C
*      language options.
*  (2) Conservative limits placed upon range of acceptable values of x.
*  (3) Scientific notation is accepted as input.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   08/28/2017: Initial release. JME
*************************************************************************/
#include <assert.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Definitions.
#define MAX_INPUT_ATTEMPTS 3 // Maximum input attempts befrore aborting.
#define MIN_X -10.0          // Min input value.
#define MAX_X +10.0          // Max input value.

// Calculate the following polynomial: 3x^5 + 2x^4 – 5x^3 – x^2 +7x – 6
double calcPoly(const double x) {
	double y;
	
	y = (3.0 * pow(x, 5.0)) + (2.0 * pow(x, 4.0));
	y = y - (5.0 * pow(x, 3.0)) - (x * x);
	y = y + (7.0 * x) - 6.0;
	return y;
}

// Program starts here.
int main(void) {
	char input[12];                    // Holds user input as string.
	double x;                          // Converted string value of user input.
	int attempts = MAX_INPUT_ATTEMPTS; // Input attempt counter.

	assert(attempts > 0); // Assert attempts valid non-zero, positive number.

	// Display instruction prompt.
	fputs("This program computes the following polynomial:\n", stdout);
	fputs("  3x^5 + 2x^4 - 5x^3 - x^2 + 7x - 6\n\n", stdout);
	fprintf(stdout, "Values for x are limited to numbers between %.2lf and %.2lf\n", MIN_X, MAX_X);

	// Allow only so many input attempts.
	while (attempts--) {
		// Prompt and grab user input.
		fputs("Enter x: ", stdout);
		if (!fgets(input, sizeof input, stdin)) {
			fputs("\nFatal program error!\n", stderr);
			exit(EXIT_FAILURE);
		}
		else if (!strchr(input, '\n')) {
			// input too long, eat remainder.
			while (fgets(input, sizeof input, stdin) && !strchr(input, '\n'))
				; // Empty body.
			fputs("Too many characters input.\n", stdout);
		}
		else {
			// Catch special case of null input.
			if (strlen(input) <= 1)
				continue;

			// Attempt to convert from string to float, and validate.
			if (sscanf_s(input, "%lf", &x)) {
				if (x >= MIN_X && x <= MAX_X) {
					fprintf(stdout, "y = %0.3lf\n", calcPoly(x));
					break; // Exit.
				}
				else
					fprintf(stdout, "Value entered is outside allowable range (%0.2f and %0.2f)\n", MIN_X, MAX_X);
			}
			else
				fputs("Invalid input.\n", stdout);
		}
	}
}

