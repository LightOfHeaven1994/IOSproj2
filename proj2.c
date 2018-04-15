/**
* @file proj2.c
* @author Egor Shamardin <xshama00>
* @brief Main file for work with bus-riders
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


#include "process_data.h"
#include "proj2.h"
#include "sym_process.h"


// Main function
int main(int argc, char *argv[])
{	
	int size = sizeof(int);
	printf("%d\n", size);
	params = getParam(argc, argv);

	// Create Process
	initProcess();
	// Riders creation processing
	pid_t Rid_Proc; /*< ID of process */
	pid_t Rid_New_Proc = fork(); /*< Do new process */
	
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
			Rid_Proc = fork(); /*< Do new process for every rider */
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

	// Bus creation processing
	pid_t Bus_Proc; /*< ID of process */
	pid_t Bus_New_Proc = fork(); /*< Do new process */

	if (Bus_New_Proc == -1){
		perror("ERROR: process creation failed");
		endProcess();
		exit(1);
	}
	else if (Bus_New_Proc == 0){
		for(int y = 1; y < params->C; y++){
			if (params->ABT !=0){
				usleep(params->ABT*1000);
			}
			else if(params->ABT == 0){
				usleep(0);
			}
			Bus_Proc = fork();
			if (Bus_Proc == -1){
				perror("ERROR: process creation failed");
				endProcess();
				exit(1);
			}
			else if (Bus_Proc == 0){
				createBus(y);
				sem_close(Mutex);
				sem_close(Bus);
				sem_close(RidersQueue);
				exit(0);
			}
		}
	}


	// Exit process
	endProcess();


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
	if (argc != 5){
		perror("ERROR: Wrong count of arguments!");
		exit(1);
	}
	int A = atol(argv[1]); /*< Count of riders */
	int C = atol(argv[2]); /*< Count of buses */
	int ART = atol(argv[3]); /*< Count of milliseconds riders process */
	int ABT = atol(argv[4]); /*< Count of milliseconds bus process */

	if (A <= 0){
		perror("ERROR: Wrong count of riders");
		exit(1);
	}
	
	if (C <= 0){
		perror("ERROR: Wrong count of buses");
		exit(1);
	}

	if (ART < 0 || ART > 1000){
		perror("ERROR: Wrong count of milliseconds for riders process");
		exit(1);
	}

	if (ABT < 0 || ABT > 1000){
		perror("ERROR: Wrong count of milliseconds for riders process");
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
	*action_counter = *action_counter + 1;
	printf("\n%d \t : RID %d \t : start", *action_counter, rider_id);
	sem_post(Mutex);
}

void createBus(int bus_id){

	sem_wait(Mutex);
	*action_counter = *action_counter + 1;
	printf("\n%d \t : BUS %d \t : start", *action_counter, bus_id);
	sem_post(Mutex);

}