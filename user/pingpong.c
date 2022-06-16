// Simple pingpong.

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/syscall.h"

int
main(int argc, char *argv[])
{
  int p[2]; // p[1]: write p[0]: read
  if (pipe(p) < 0)
      exit(1);
  if (fork() == 0) {
    // child
    write(p[1], "x", 1);
    int child_pid = getpid();
    printf("%d: received ping\n", child_pid);
  } else {
    char* buf = (char*)malloc(1 * sizeof(char*));
    read(p[0], buf, 1);
    int parent_pid = getpid();
    sleep(1);
    printf("%d: received pong\n", parent_pid);
  }

  exit(0);
}