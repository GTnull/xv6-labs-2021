// Simple pingpong.

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/syscall.h"

void prime(int *p_left) {
  int p;
  int p_right[2];
  
  if(read(p_left[0], &p, 4) == 0) {
    exit(0);
  } else {
    printf("prime %d\n", p);
  }
  if(pipe(p_right) < 0) exit(1);
  if(fork() == 0) {
    // child
    close(p_right[1]);
    prime(p_right);
    close(p_right[0]);
  } else {
    // parent
    close(p_right[0]);
    int next;
    while(read(p_left[0], &next, 4)) {
      if(next % p != 0) {
        write(p_right[1], &next, 4);
      }
    }
    close(p_right[1]);
  }
  wait(0);
  exit(0);
}

int
main(int argc, char *argv[])
{
  // printf("prime 2\nprime 3\nprime 5\nprime 7\nprime 11\nprime 13\nprime 17\nprime 19\nprime 23\nprime 29\nprime 31\n");
  int p_left[2];
  if(pipe(p_left) < 0) exit(1);
  
  if(fork() == 0) {
    // child
    close(p_left[1]);
    prime(p_left);
    close(p_left[0]);
  } else {
    // parent
    close(p_left[0]);
    for(int i = 2; i < 35; i++) {
      write(p_left[1], &i, 4);
    }
    close(p_left[1]);
  }
  wait(0);
  exit(0);
}