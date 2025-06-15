#include "slow_functions.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// How nice of me to include a global that tells you how many commands there were :)
int total_commands = 0;

// Global variables for synchronization
pthread_mutex_t buffer_mutex;
pthread_cond_t data_written_cond;
pthread_cond_t data_read_cond;
int commands_processed = 0;

// ####################################################################################
// ## Please write some code in the following two functions

void * writer(void * in_ptr)
{
    char ** commands = (char **)in_ptr;
    
    for (int i = 0; i < total_commands; i++) {
        pthread_mutex_lock(&buffer_mutex);
        
        // Wait until the buffer has been read (or this is the first write)
        while (get_written() == 1) {
            pthread_cond_wait(&data_read_cond, &buffer_mutex);
        }
        
        // Write to buffer
        bad_write(commands[i]);
        
        // Signal that data has been written
        pthread_cond_signal(&data_written_cond);
        
        pthread_mutex_unlock(&buffer_mutex);
    }
    
    return NULL;
}

void * reader(void * empty)
{
    for (int i = 0; i < total_commands; i++) {
        pthread_mutex_lock(&buffer_mutex);
        
        // Wait until data has been written
        while (get_written() == 0) {
            pthread_cond_wait(&data_written_cond, &buffer_mutex);
        }
        
        // Read from buffer
        bad_read(NULL);
        
        // Signal that data has been read
        pthread_cond_signal(&data_read_cond);
        
        pthread_mutex_unlock(&buffer_mutex);
    }
    
    return NULL;
}


int main()
{
    // ## SOME SPACE IN CASE YOU NEED TO INITIALISE VARIABLES
    
    // Initialize mutex and condition variables
    if (pthread_mutex_init(&buffer_mutex, NULL) != 0) {
        fprintf(stderr, "Mutex initialization failed\n");
        return 1;
    }
    
    if (pthread_cond_init(&data_written_cond, NULL) != 0) {
        fprintf(stderr, "Condition variable initialization failed\n");
        return 1;
    }
    
    if (pthread_cond_init(&data_read_cond, NULL) != 0) {
        fprintf(stderr, "Condition variable initialization failed\n");
        return 1;
    }

    // ################################################################################
    // ## DO NOT MODIFY BELOW HERE

    // ## Parse STDIN and read into commands
    char * commands[100];
    char line[256];
    while (fgets(line, 256, stdin))
    {
        commands[total_commands] = (char*)(malloc(strlen(line) * sizeof(char)));
        strcpy(commands[total_commands], line);
        total_commands = total_commands + 1;
    }

    pthread_t write1;
    pthread_t read1;

    // Creates a thread which executes writer!
    if(pthread_create(&write1, NULL, writer, commands))
    {
        fprintf(stderr, "Error creating write thread\n");
        return 1;
    }

    // Creates a thread which executes reader!
    if(pthread_create(&read1, NULL, reader, NULL))
    {
        fprintf(stderr, "Error creating read thread\n");
        return 1;
    }

    // Ensure Threads Join Well
    if(pthread_join(write1, NULL)) 
    {
        fprintf(stderr, "Error joining write thread\n");
        return 2;
    }

    if(pthread_join(read1, NULL)) 
    {
        fprintf(stderr, "Error joining read thread\n");
        return 2;
    }

    // Did you really call the right functions?
    get_output();

    // Cleanup
    pthread_mutex_destroy(&buffer_mutex);
    pthread_cond_destroy(&data_written_cond);
    pthread_cond_destroy(&data_read_cond);

    // I am a responsible memory user!
    int command_i;
    for (command_i = 0; command_i < total_commands; command_i++)
    {
        free(commands[command_i]);
    }
    return 0;
    // ## DO NOT MODIFY ABOVE HERE
    // ################################################################################
}