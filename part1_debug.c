#include "slow_functions.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pthread_t thread2, threads1[10];
    
    printf("DEBUG: Starting slow_function2\n");
    fflush(stdout);
    
    // Start slow_function2 first to initialize the mutex
    if (pthread_create(&thread2, NULL, slow_function2, NULL)) {
        fprintf(stderr, "Error creating thread2\n");
        return 1;
    }
    
    // Wait just long enough for mutex initialization and "Start 2" to print
    usleep(100000); // 100ms
    
    printf("DEBUG: Starting 10 slow_function1 threads\n");
    fflush(stdout);
    
    // Now create all 10 threads running slow_function1 simultaneously
    for (int i = 0; i < 10; i++) {
        if (pthread_create(&threads1[i], NULL, slow_function1, NULL)) {
            fprintf(stderr, "Error creating thread1[%d]\n", i);
            return 1;
        }
    }
    
    printf("DEBUG: All threads created, waiting for completion\n");
    fflush(stdout);
    
    // Wait for all slow_function1 threads to complete
    for (int i = 0; i < 10; i++) {
        if (pthread_join(threads1[i], NULL)) {
            fprintf(stderr, "Error joining thread1[%d]\n", i);
            return 2;
        }
    }
    
    printf("DEBUG: All slow_function1 threads completed\n");
    fflush(stdout);
    
    // Wait for slow_function2 to complete
    if (pthread_join(thread2, NULL)) {
        fprintf(stderr, "Error joining thread2\n");
        return 2;
    }
    
    printf("DEBUG: slow_function2 completed\n");
    fflush(stdout);
    
    return 0;
}