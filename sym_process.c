
#include "process_data.h"
#include "sym_process.h"

void create_symaphores(){
	// initialize semaphores for shared processes
	if ((Mutex = sem_open("Mutex_sem", O_CREAT | O_EXCL, S_IRUSR |  S_IWUSR, 1)) == SEM_FAILED){
		print_error();
	}
	if ((Bus = sem_open("Bus_sem", O_CREAT | O_EXCL, S_IRUSR |  S_IWUSR, 1)) == SEM_FAILED){
		print_error();
	}
	if ((RidersQueue = sem_open("Riders_sem", O_CREAT | O_EXCL, S_IRUSR |  S_IWUSR, 0)) == SEM_FAILED){
		print_error();
	}
}
void create_shared_memory(){

/*	// function return a file descriptor that is associated with a memory object
	if ((action_counter_shm = shm_open("SHM_ACT", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR)) == -1){
		print_error();
	}
	if ((counter_riders_shm = shm_open("SHM_RID", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR)) == -1){
		print_error();
	}
	if ((riders_in_bus_shm = shm_open("SHM_RID_IN", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR)) == -1){
		print_error();
	}*/
		if(( shm_Counters = shm_open("SHM_COUNTERS", O_CREAT | O_EXCL | O_RDWR, 0644)) == -1){
			print_error();
		}
/*	// set the size of shared memory
	ftruncate(action_counter_shm, SHARED_MEMORY_OBJECT_SIZE);
	ftruncate(counter_riders_shm, SHARED_MEMORY_OBJECT_SIZE);
	ftruncate(riders_in_bus_shm, SHARED_MEMORY_OBJECT_SIZE);*/
	ftruncate(shm_Counters, sizeof(Counters));
	// get access shared memory
	/*action_counter = (int *) mmap(NULL, SHARED_MEMORY_OBJECT_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, action_counter_shm, 0);
	counter_riders = (int *) mmap(NULL, SHARED_MEMORY_OBJECT_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, counter_riders_shm, 0);
	riders_in_bus = (int *) mmap(NULL, SHARED_MEMORY_OBJECT_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, riders_in_bus_shm, 0);
*/	
	memory_counters = mmap(NULL, sizeof(Counters), PROT_READ | PROT_WRITE, MAP_SHARED, shm_Counters, 0);
	memory_counters->action_counter = 0;
	memory_counters->counter_riders = 0;
	memory_counters->riders_in_bus = 0;

}
/* close and delete semaphores */
void endProcess(){
	sem_close(Mutex);
	sem_close(Bus);
	sem_close(RidersQueue);

	close(shm_Counters);
	munmap(memory_counters, sizeof(Counters));
	shm_unlink("SHM_COUNTERS");
	/*close(action_counter_shm);
	close(counter_riders_shm);
	close(riders_in_bus_shm);
	
	munmap(action_counter, SHARED_MEMORY_OBJECT_SIZE);
	munmap(counter_riders, SHARED_MEMORY_OBJECT_SIZE);
	munmap(riders_in_bus, SHARED_MEMORY_OBJECT_SIZE);

	shm_unlink("SHM_ACT");
	shm_unlink("SHM_RID");
	shm_unlink("SHM_RID_IN");*/

	sem_unlink("Mutex_sem");
	sem_unlink("Bus_sem");
	sem_unlink("Riders_sem");
}

void print_error(){
		perror("ERROR: Semafor or shared variable wasn't created");
		endProcess();
		exit(1);
}