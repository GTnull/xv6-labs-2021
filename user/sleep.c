// Simple sleep.

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/syscall.h"

int
main(int argc, char *argv[])
{
  if(argc < 2){
    fprintf(2, "Usage: sleep 10...\n");
    exit(1);
  }

  int n = atoi(argv[1]);
  sleep(n);
  exit(0);
}