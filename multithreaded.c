
#include "shared.c"


// This version creates threads on the C side:
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
    parent();
   
    void* retval;
    pthread_join(thread, &retval);
    
    printf("Child joined.\n");   
    print_numcaps();
    printf("Exiting Haskell RTS.\n");
    hs_exit();
    pthread_exit(NULL);
    return 0;
}
