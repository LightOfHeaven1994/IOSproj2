

#include "process_data.h"
#include "sym_process.h"

void initProcess(){
/* initialize semaphores for shared processes */
	Mutex = sem_open("Mutex_sem", O_CREAT | O_EXCL, S_IRUSR |  S_IWUSR, 1);
	Bus = sem_open("Bus_sem", O_CREAT | O_EXCL, S_IRUSR |  S_IWUSR, 1);
	RidersQueue = sem_open("Riders_sem", O_CREAT | O_EXCL, S_IRUSR |  S_IWUSR, 0);

	if (Mutex == SEM_FAILED || Bus == SEM_FAILED || RidersQueue == SEM_FAILED){
		perror("ERROR: Semafor wasn't created");
		endProcess();
		exit(1);
	}

	// function return a file descriptor that is associated with a memory object
	action_counter_shm = shm_open("SHM_ACT", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
	if( action_counter_shm == -1){
		perror("ERROR: shared veriable for memory wasn't created");
		endProcess();
		exit(1);
	}
	// set the size of shared memory
	ftruncate(action_counter_shm, SHARED_MEMORY_OBJECT_SIZE);
	// get access shared memory
	action_counter = (int *) mmap(NULL, SHARED_MEMORY_OBJECT_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, action_counter_shm, 0);

}
/* close and delete semaphores */
void endProcess(){
	sem_close(Mutex);
	sem_close(Bus);
	sem_close(RidersQueue);

	close(action_counter_shm);
	munmap(action_counter, SHARED_MEMORY_OBJECT_SIZE);
	shm_unlink("SHM_ACT");

	sem_unlink("Mutex_sem");
	sem_unlink("Bus_sem");
	sem_unlink("Riders_sem");
}