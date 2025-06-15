#include "slow_functions.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pthread_t thread2, threads1[10];
    
    // Start slow_function2 first
    if (pthread_create(&thread2, NULL, slow_function2, NULL)) {
        fprintf(stderr, "Error creating thread2\n");
        return 1;
    }
    
    // Very small delay to ensure mutex is initialized
    usleep(10000); // 10ms
    
    // Create all 10 slow_function1 threads as quickly as possible
    for (int i = 0; i < 10; i++) {
        if (pthread_create(&threads1[i], NULL, slow_function1, NULL)) {
            fprintf(stderr, "Error creating thread1[%d]\n", i);
            return 1;
        }
    }
    
    // Wait for slow_function2 to complete first
    if (pthread_join(thread2, NULL)) {
        fprintf(stderr, "Error joining thread2\n");
        return 2;
    }
    
    // Then wait for all slow_function1 threads to complete
    for (int i = 0; i < 10; i++) {
        if (pthread_join(threads1[i], NULL)) {
            fprintf(stderr, "Error joining thread1[%d]\n", i);
            return 2;
        }
    }
    
    return 0;
}