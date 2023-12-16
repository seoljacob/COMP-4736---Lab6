#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define PGSIZE 4096

lock_t lock;

void thread_function1(void *arg1, void *arg2) {
  lock_acquire(&lock);
  printf(1, "Thread 1: arg1 = %d, arg2 = %d\n", *(int*)arg1, *(int*)arg2);
  lock_release(&lock);
  exit();
}

void thread_function2(void *arg1, void *arg2) {
  lock_acquire(&lock);
  printf(1, "Thread 2: arg1 = %d, arg2 = %d\n", *(int*)arg1, *(int*)arg2);
  lock_release(&lock);
  exit();
}

int main(int argc, char *argv[]) {
  int arg1 = 10;
  int arg2 = 20;

  lock_init(&lock);

  printf(1, "Parent: calling thread_create for thread 1...\n");
  int pid1 = thread_create(thread_function1, &arg1, &arg2);
  if (pid1 < 0) {
    printf(1, "Error: thread_create failed for thread 1.\n");
    exit();
  }

  printf(1, "Parent: calling thread_create for thread 2...\n");
  int pid2 = thread_create(thread_function2, &arg1, &arg2);
  if (pid2 < 0) {
    printf(1, "Error: thread_create failed for thread 2.\n");
    exit();
  }

  printf(1, "Parent: waiting for child 1 to finish...\n");
  int join_pid1 = thread_join();
  if (join_pid1 < 0) {
    printf(1, "Error: thread_join failed for child 1.\n");
    exit();
  }

  printf(1, "Parent: waiting for child 2 to finish...\n");
  int join_pid2 = thread_join();
  if (join_pid2 < 0) {
    printf(1, "Error: thread_join failed for child 2.\n");
    exit();
  }

  printf(1, "Parent: both children finished.\n");

  exit();
}