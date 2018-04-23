/**
* @file proj2.c
* @author Egor Shamardin <xshama00>
* @brief Main out_file for work with bus-riders
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "process_data.h"
#include "proj2.h"
#include "sym_process.h"

#define COUNT_OF_ARGUMENTS 5
FILE *out_file;
// Main function
int main(int argc, char *argv[])
{	
	params = getParam(argc, argv);

	create_symaphores(); // create symaphores
	create_shared_memory(); // create shared memory

	out_file = fopen("proj2.out", "w+"); // open out_file for write
	
	// Bus creation processing
	Bus_New_Proc = fork(); // pid_t Bus_New_Proc

	if (Bus_New_Proc == -1){
		perror("ERROR: process creation failed");
		endProcess();
		exit(1);
	} 
	else if (Bus_New_Proc == 0){
		for(int y = 1; y <= params->C; y++){
			if (params->ABT !=0){
				usleep(params->ABT*1000);
			}
			else if(params->ABT == 0){
				usleep(0);
			}
			Bus_Proc = fork(); // pid_t Bus_Proc
			if (Bus_Proc == -1){
				perror("ERROR: process creation failed");
				endProcess();
				exit(1);
			}
			else if (Bus_Proc == 0){
				if (y == 1){
					sem_wait(Mutex);
					memory_counters->action_counter = memory_counters->action_counter + 1;
					fprintf(out_file,"\n%d \t : BUS   \t : start", memory_counters->action_counter);
					sem_post(Mutex);
					}
				createBus(y);
				sem_close(Mutex);
				sem_close(Bus);
				sem_close(RidersQueue);
				exit(0);
			}
		}
	}

	// Riders creation processing
	
	Rid_New_Proc = fork(); //pid_t Rid_New_Proc
	
	if (Rid_New_Proc == -1){
		perror("ERROR: process creation failed");
		endProcess();
		exit(1);
	}
	else if (Rid_New_Proc == 0){
		for (int x = 1; x <= params->A; x++){
			if (params->ART != 0){
				usleep(params->ART*1000); /*< multiply on 1000 because of translations milSec to micSec*/
			}
			else if (params->ART == 0){
				usleep(0);
			}
			Rid_Proc = fork(); //pid_t Rid_New_Proc
			if (Rid_Proc == -1){
				perror("ERROR: process creation failed");
				endProcess();
				exit(1);
			}
			else if (Rid_Proc == 0){
				createRider(x);
				sem_close(Mutex);
				sem_close(Bus);
				sem_close(RidersQueue);
				exit(0);
			}
		}
	}

	// Exit process
	endProcess();
	fclose(out_file);
	exit(0);
}

/*
* @brief Help function for check arguments and write them to structure
* @param argc count of arguments
* @param argv arguments
*
* @return data_param structure with arguments from terminal
*/
Data_t *getParam(int argc, char *argv[]) {

	// Count of arguments
	if (argc != COUNT_OF_ARGUMENTS){
		perror("ERROR: Wrong count of arguments!");
		exit(1);
	}
	int A = atol(argv[1]); /*< Count of riders */
	int C = atol(argv[2]); /*< Count of places in bus */
	int ART = atol(argv[3]); /*< Count of milliseconds riders process */
	int ABT = atol(argv[4]); /*< Count of milliseconds bus process */

	if (A <= 0 || C <= 0){
		perror("ERROR: Wrong count of riders or bus places");
		exit(1);
	}
	if (ART < 0 || ART > 1000 || ABT < 0 || ABT > 1000){
		perror("ERROR: Wrong count of milliseconds for riders or bus process");
		exit(1);
	}

	// Alocation structure
	Data_t *data_param = NULL;
    data_param = malloc(sizeof(Data_t));

    // Check for malloc fail
    if (data_param == NULL) {
        perror("ERROR: Allocation memory was failed");
        exit(1);
    }

    data_param->A = A;
    data_param->C = C;
    data_param->ART = ART;
    data_param->ABT = ABT;

    return data_param;
}

/*< Create new rider */
void createRider(int rider_id){

	sem_wait(Mutex);
	memory_counters->action_counter = memory_counters->action_counter + 1;
	memory_counters->action_counter = memory_counters->action_counter +1;
	fprintf(out_file, "\n%d \t : RID %d \t : start\n", memory_counters->action_counter, rider_id);
	sem_post(Mutex);

	sem_wait(Mutex);
	memory_counters->action_counter = memory_counters->action_counter + 1;
	fprintf(out_file,"%d \t : RID %d \t : enter: %d", memory_counters->action_counter, rider_id, rider_id);
	sem_post(Mutex);

}

void createBus(int bus_id){

	sem_wait(Mutex);
	memory_counters->action_counter = memory_counters->action_counter + 1;
	fprintf(out_file, "\n%d \t : BUS   \t : arrival", memory_counters->action_counter);
	sem_post(Mutex);

	sem_wait(Mutex);
	if (memory_counters->riders_in_bus != 0){
		memory_counters->action_counter = memory_counters->action_counter + 1;
		fprintf(out_file, "\n%d \t : BUS   \t : start boarding: %d", memory_counters->action_counter, memory_counters->riders_in_bus);
	}
	sem_post(Mutex);

	sem_wait(Mutex);
	memory_counters->action_counter = memory_counters->action_counter + 1;
	if (memory_counters->counter_riders != 0){
		fprintf(out_file, "\n%d \t : BUS   \t : start boarding : %d", memory_counters->action_counter, memory_counters->counter_riders);
		for (int i = 1; i <= memory_counters->action_counter + 1; i++){
			memory_counters->action_counter = memory_counters->action_counter + 1;
			memory_counters->riders_in_bus = memory_counters->riders_in_bus + 1;
			fprintf(out_file, "\n%d \t : RID %d   \t : boarding", memory_counters->action_counter, i);
		}
	}
	else if (memory_counters->counter_riders == 0){
		fprintf(out_file, "\n%d \t : BUS    \t : depart", memory_counters->action_counter);
	}
	sem_post(Mutex);

	sem_wait(Mutex);
	memory_counters->action_counter = memory_counters->action_counter + 1;
	fprintf(out_file, "\n%d \t : BUS   \t : end", memory_counters->action_counter);
	sem_post(Mutex);



}