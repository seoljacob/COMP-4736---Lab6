#include "types.h"
#include "user.h"
#include "fcntl.h"

#define PGSIZE 4096

void thread_function(void *arg1, void *arg2) {
  printf(1, "Thread: arg1 = %d, arg2 = %d\n", *(int*)arg1, *(int*)arg2);
  exit();
}

int main(int argc, char *argv[]) {
  void *stack;
  int arg1 = 10;
  int arg2 = 20;

  stack = malloc(PGSIZE);
  if (stack == NULL) {
    printf(1, "Error: could not allocate stack.\n");
    exit();
  }

  printf(1, "Parent: calling clone...\n");
  int pid = clone(thread_function, &arg1, &arg2, stack);
  if (pid < 0) {
    printf(1, "Error: clone failed.\n");
    exit();
  }

  printf(1, "Parent: waiting for child to finish...\n");
  void *join_stack;
  int join_pid = join(&join_stack);
  if (join_pid < 0) {
    printf(1, "Error: join failed.\n");
    exit();
  }

  printf(1, "Parent: child finished.\n");

  exit();
}