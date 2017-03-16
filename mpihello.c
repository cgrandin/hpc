#include <mpi.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv){
  // Initialize MPI.
  MPI_Init(NULL, NULL);

  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  // Sleep for random number of seconds. (1 to 5).
  // Use the thread_safe version of rand().
  int sleeptime;
  srand(time(NULL));
  sleeptime =  (rand_r() % 5) + 1;
  sleep(sleeptime);

  // Get the current time, with millisecond precision.
  struct timespec mytime;
  if (gettimeofday(&mytime, NULL) == 0)
      // Output process identity and sleep time.
      printf("Hello from processor %s, rank %d out of %d processors! I slept %d seconds until %d nanoseconds past %s",
             processor_name, world_rank, world_size, sleeptime, mytime.tv_nsec, ctime(&mytime.tv_sec));
  else
      // Output error message.
      printf("Hello from processor %s, rank %d out of %d processors! Sorry, I could not access the clock.\n");

  // Finalize the MPI environment. No more MPI calls allowed.
  MPI_Finalize();

  return(0);
}
