#include "mpi.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void srandom (unsigned seed);
double dboard (int darts);
#define DARTS 50000
#define ROUNDS 100
#define MASTER 0

int main (int argc, char *argv[]) {
    clock_t begin = clock();
    double	oneProcessPi, allProcessesPiSum, oneRoundPiAverage, piAverage;
    int	taskId, taskCount, returnCode,i;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&taskCount);
    //MPI_Comm_rank(MPI_COMM_WORLD,&taskId);
    MPI_Comm intercomm;
    MPI_Comm_spawn(
            "pi_worker.o",
            MPI_ARGV_NULL,
            taskCount,
            MPI_INFO_NULL,
            0,
            MPI_COMM_SELF,
            &intercomm,
            MPI_ERRCODES_IGNORE
            );

    printf ("MPI task %d has started...\n", taskId);

/* Set seed for random number generator equal to task ID */
//    srandom (taskId);
//
//    piAverage = 0;
//    for (i = 0; i < ROUNDS; i++) {
//        oneProcessPi = dboard(DARTS);
//
//        returnCode = MPI_Reduce(&oneProcessPi, &allProcessesPiSum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);
//
//        if (taskId == MASTER) {
//            oneRoundPiAverage = allProcessesPiSum/taskCount;
//            piAverage = ((piAverage * i) + oneRoundPiAverage)/(i + 1);
//            printf("   After %8d throws, average value of pi = %10.8f\n",
//                   (DARTS * (i + 1)),piAverage);
//        }
//    }
//    if (taskId == MASTER) {
//        printf ("\nReal value of PI: 3.1415926535897 \n");
//        clock_t end = clock();
//        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
//        printf("Elapsed: %f seconds\n", time_spent);//logs computing time
//    }
    MPI_Finalize();

    return 0;
}

double dboard(int darts) {
#define sqr(x)	((x)*(x))
    long random(void);
    double x_coord, y_coord, pi, r;
    int score, n;
    unsigned int cconst;
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

    pi = 4.0 * (double)score/(double)darts;
    return(pi);
}