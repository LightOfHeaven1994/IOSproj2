
#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h>
#include <sys/stat.h> /*< S_IRUSR, S_IWUSR */
#include <fcntl.h> /*< O_CREAT, O_EXEC */
#include <sys/types.h> /*< pid_t */
#include <unistd.h> /*< pid_t, fork, usleep */
#include <sys/mman.h> /*< shm */

#include "process_data.h"
#include "proj2.h"

#define SHARED_MEMORY_OBJECT_SIZE (sizeof(int)) 

void initProcess();

void endProcess();