
#include <HsFFI.h>
#ifdef __GLASGOW_HASKELL__
#include "Safe_stub.h"
extern void __stginit_Safe(void);
#endif
#include <stdio.h>
#include <pthread.h>
// #include <syscall.h> // Linux specific.

void* child () {
  int i;
  printf("On child thread, pthread %lu.  About to upcall.\n",
         (unsigned long)pthread_self());
  //  printf("lwp %d\n", syscall(SYS_gettid));
  i = fibonacci_hs(42);
  printf("Fibonacci: %d\n", i);
  print_numcaps();  
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    hs_init(&argc, &argv);
#ifdef __GLASGOW_HASKELL__
    hs_add_root(__stginit_Safe);
#endif
    
    printf("On parent thread %lu.  About to spawn.\n", (unsigned long) pthread_self());
    print_numcaps();
    pthread_t thread;
    pthread_create(& thread, NULL, child, NULL);

    void* retval;
    pthread_join(thread, &retval);
    
    printf("Child joined.\n");   
    print_numcaps();
    printf("Exiting Haskell RTS.\n");
    hs_exit();
    pthread_exit(NULL);
    return 0;
}
