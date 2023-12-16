#include "types.h"
#include "stat.h"
#include "user.h"

void thread(void *arg1, void *arg2) {
  printf(1, "Hello from thread! arg1: %d arg2: %d\n", *(int*)arg1, *(int*)arg2);
  exit();
}

int main(int argc, char *argv[]) {
  printf(1, "Hello from main!\n");
  int arg1 = 10;
  int arg2 = 20;
  void *stack = malloc(4096);
  int pid = clone(thread, &arg1, &arg2, stack);
  if(pid < 0) {
    printf(2, "Error: clone failed\n");
    exit();
  }
  printf(1, "clone created a new thread with pid %d\n\n", pid);
  wait();
  exit();
}