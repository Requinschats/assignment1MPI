#include "mpi.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int size;
    MPI_Comm parent;
    MPI_Init(&argc, &argv);
    MPI_Comm_get_parent(&parent);
    MPI_Comm_remote_size(parent, &size);

    /*
     * The manager is represented as the process with rank 0
     */

    MPI_Finalize();
    return 0;
}

