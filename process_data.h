/**
* @file process_data.h
* @author Egor Shamardin <xshama00>
* @brief Header for process data
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h> /*< S_IRUSR, S_IWUSR */
#include <fcntl.h> /*< O_CREAT, O_EXEC */
#include <sys/types.h> /*< pid_t */
#include <unistd.h> /*< pid_t, fork, usleep */
#include <sys/mman.h> /*< shm */

#define SHARED_MEMORY_OBJECT_SIZE (sizeof(int)) 
/*
* @brief Structure for process
*/
//***********************************************************
typedef struct {
	int A; /*< Count of riders process*/
	int C; /*< Count of buses process*/
	int ART; /*< Count time for generation new rider process*/
	int ABT; /*< Count time for generation new bus process*/
} Data_t;
Data_t *params;
//***********************************************************
typedef struct {
	int action_counter;
	int counter_riders;
	int riders_in_bus;	
} Counters;

Counters *memory_counters;
int shm_Counters;
//***********************************************************

// Semaphores
sem_t *Bus;
sem_t *RidersQueue;
sem_t *Mutex;

pid_t Bus_Proc; /*< ID of process */
pid_t Bus_New_Proc;

pid_t Rid_Proc; /*< ID of process */
pid_t Rid_New_Proc;


/*int action_counter_shm;

int counter_riders_shm;

int riders_in_bus_shm;*/
