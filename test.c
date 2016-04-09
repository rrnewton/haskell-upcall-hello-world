
#include <HsFFI.h>
#ifdef __GLASGOW_HASKELL__
#include "Safe_stub.h"
extern void __stginit_Safe(void);
#endif
#include <stdio.h>
#include <pthread.h>

int main(int argc, char *argv[])
{
    int i;
    hs_init(&argc, &argv);
#ifdef __GLASGOW_HASKELL__
    hs_add_root(__stginit_Safe);
#endif

    printf("Main thread: %d\n", (int)pthread_self());
    
    i = fibonacci_hs(42);
    printf("Fibonacci: %d\n", i);

    print_numcaps();
    
    hs_exit();
    return 0;
}
