/**
* @file proj2.h
* @author Egor Shamardin <xshama00>
* @brief Standard header for proj2.c
*/

int main(int argc, char *argv[]);

Data_t *getParam(int argc, char *argv[]);

void initProcess();

void endProcess();

void createRider(int rider_id);

void createBus(int bus_id);