#include "stdio.h"
#include "stdlib.h"
#include <time.h>

double dboardSequential(int darts) {
#define sqr(x)	((x)*(x))
    long random(void);
    double x_coord, y_coord, pi, r;
    int score, n;
    unsigned int cconst;  /* must be 4-bytes in size */
    if (sizeof(cconst) != 4) {
        printf("Wrong data size for cconst variable in dboard routine!\n");
        printf("See comments in source file. Quitting.\n");
        exit(1);
    }
    /* 2 bit shifted to MAX_RAND later used to scale random number between 0 and 1 */
    cconst = 2 << (31 - 1);
    score = 0;

    /* "throw darts at board" */
    for (n = 1; n <= darts; n++)  {
        /* generate random numbers for x and y coordinates */
        r = (double)random()/cconst;
        x_coord = (2.0 * r) - 1.0;
        r = (double)random()/cconst;
        y_coord = (2.0 * r) - 1.0;

        /* if dart lands in circle, increment score */
        if ((sqr(x_coord) + sqr(y_coord)) <= 1.0)
            score++;
    }

/* calculate pi */
    pi = 4.0 * (double)score/(double)darts;
    return(pi);
}

int main(int argc, char** argv) {
    clock_t begin = clock();
int DARTS;
DARTS = 5000000; /* number of throws at dartboard */
/* Darts * rounds matches number of computation of parallel algorithm */
    double sequentialPi = dboardSequential(DARTS);
    printf("Sequential Pi value: %f \n", sequentialPi);//logs computing time
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Elapsed: %f seconds\n", time_spent);//logs computing time
    return 0;
}
