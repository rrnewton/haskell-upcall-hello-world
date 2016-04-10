
#include <HsFFI.h>
#ifdef __GLASGOW_HASKELL__
#include "Safe_stub.h"
extern void __stginit_Safe(void);
#endif
#include <stdio.h>
#include <pthread.h>
// #include <syscall.h> // Linux specific.

// int reps = 100 * 1000 * 1000;
int reps = 100 * 1000;

void* child () {
  int i, n;
  printf("On child thread, pthread %lu.  About to upcall.\n",
         (unsigned long)pthread_self());
  //  printf("lwp %d\n", syscall(SYS_gettid));
  for(i=0; i<reps; i++)
    n = fibonacci_hs(42);
  printf("  Fibonacci, child: %d\n", n);
  print_numcaps();  
  // pthread_exit(NULL);
  return NULL;
}

void parent() {
  int i,n;
  for(i=0; i<reps; i++)
    n = fibonacci_hs(42);
  printf("  Fibonacci, main: %d\n", n);
}
