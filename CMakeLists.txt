cmake_minimum_required(VERSION 3.12)
project(assignment1MPI C)

set(CMAKE_C_STANDARD 99)

add_executable(assignment1MPI main.c sequentialPi.c Question1D/parallelReview.c Question1D/pi_worker.c)
include_directories(/usr/local/lib/mpi/)