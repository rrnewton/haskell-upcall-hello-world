
#include <HsFFI.h>
#ifdef __GLASGOW_HASKELL__
#include "Safe_stub.h"
extern void __stginit_Safe(void);
#endif
#include <stdio.h>
#include <pthread.h>

void* child () {
  int i;
  printf("On child thread.  About to upcall.\n");
  i = fibonacci_hs(42);
  printf("Fibonacci: %d\n", i);  
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    hs_init(&argc, &argv);
#ifdef __GLASGOW_HASKELL__
    hs_add_root(__stginit_Safe);
#endif

    printf("On parent thread.  About to spawn.\n");
    pthread_t thread;
    pthread_create(& thread, NULL, child, NULL);

    void* retval;
    pthread_join(thread, &retval);

    printf("Child joined, exiting Haskell RTS.\n");
    hs_exit();
    pthread_exit(NULL);
    return 0;
}
