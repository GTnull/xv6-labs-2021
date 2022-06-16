#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
#include "kernel/fs.h"

#define NULL ((char*)0) 

char* readline() {
  char buf[512];
  char c;
  int i = -1;
  while(read(0, &c, 1) != 0) {
    if(c == '"') {
      continue;
    }
    if(c == '\n') {
      // printf("woo, %d, n\n", i);
      break;
    }else{
      // printf("debug: %c,\n", c);
      buf[++i] = c; 
    }
  }
  if(i == -1) return NULL;
  char *p = malloc((i + 1) * sizeof(char));
  memmove(p, buf, i + 1);
  return p;
}
int
main(int argc, char *argv[])
{
  if(argc < 3) {
    fprintf(2, "Usage : xargs command args...\n");
    exit(1);
  }

  // if(strcmp(argv[1], "-n") == 0) {

  // }
  char *new_argv[MAXARG];
  for(int i = 1; i < argc; i++) {
    new_argv[i-1] = argv[i];
  }

  char *line;
  while((line = readline()) != NULL) {
    new_argv[argc-1] = line;
    // printf("line: %s\n", line);
    if(fork() == 0) {
      exec(new_argv[0], new_argv);
      wait(0);
      exit(0);
    }else{
      wait(0);
    }
  }

  exit(0);
}
