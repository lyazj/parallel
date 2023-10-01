#include <string.h>
#include <stdio.h>
#include <mpi/mpi.h>

int main(int argc, char *argv[])
{
  int rank, np, src, dst, tag = 50;
  char buf[64];
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  if(rank) {
    sprintf(buf, "Greating from process %d!", rank);
    dst = 0;
    MPI_Send(buf, strlen(buf) + 1, MPI_CHAR, dst, tag, MPI_COMM_WORLD);
  } else {
    for(src = 1; src < np; ++src) {
      MPI_Recv(buf, sizeof buf, MPI_CHAR, src, tag, MPI_COMM_WORLD, &status);
      puts(buf);
    }
  }
  MPI_Finalize();
}
