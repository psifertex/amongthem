#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#include "xxtea.h"

struct Task {
	uint8_t id;
	char name[30];
	uint8_t time;
	uint8_t original_name;
};

struct Task tasks[10];

char tasklog[20]; 

char* dummy = "Did you know at certain optimization levels the compiler just leaves in dead code and un-referenced strings?";

#define TASKCOUNT 34

char const *shortTaskNames[] = {
"Align Telescope",
"Assemble Artifact",
"Buy Beverage",
"Calibrate Distributor",
"Chart Course",
"Clean O2 Filter",
"Clean Toilet",
"Clear Asteroids",
"Decontaminate",
"Divert Power",
"Dress Mannequin",
"Empty Garbage",
"Fill Canisters",
"Fix Shower",
"Fix Weather Node",
"Fuel Engines",
"Make Burger",
"Measure Weather",
"Monitor Tree",
"Pick Up Towels",
"Polish Ruby",
"Prime Shields",
"Process Data",
"Put Away Pistols",
"Put Away Rifles",
"Record Temperature",
"Repair Drill",
"Run Diagnostics",
"Sort Records",
"Sort Samples",
"Stabilize Steering",
"Store Artifacts",
"Submit Scan",
"Unlock Manifolds",
"Upload Data",
"There are comments hidden but",
"be glad I didnt intentionally",
"break specific tools!",
};

uint32_t checksum = 329936096;
uint32_t checksum_left = 3059920253;
uint32_t checksum_right = 1411751734;

char* dummy2 = "Sure, sure, make an IDA book and a Ghidra book, where's the Binary Ninja book?!";

void shuffleTasks()
{
	int size = TASKCOUNT;
	for (int i; i < size - 1;i++)
	{
		int j = rand() % TASKCOUNT;
		const char* temp = shortTaskNames[i];
		shortTaskNames[j] = shortTaskNames[i];
		shortTaskNames[i] = temp;
	}
}

/*
struct Task randomTask()
{
	struct Task task;
	strcpy(task.name, shortTaskNames[rand() % 34 ]);
	task.time = rand() % 10 + 1;
	return task;
}
*/

void dots(int count)
{
	for(int x = 0; x < count; x++)
	{
		if (getenv("DEBUG") == NULL)
		{
			sleep(1);
		}
		printf(".");
	}
}

void finishTask(struct Task task)
{
	printf("\n\nWorking on %s...", task.name);
	dots(task.time);
	printf("\n\nTask completed!\n\n");
}

uint32_t crc32(const void *data, size_t n_bytes) {
	uint32_t crc = 0;
	static uint32_t table[0x100];
	uint32_t r;
	if(!*table)
		for(size_t i = 0; i < 0x100; ++i)
		{
			r = i;
			for(int j = 0; j < 8; j++)
			{
				r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
			}
			table[i] = r ^ (uint32_t)0xFF000000L;
		}
	for(size_t i = 0; i < n_bytes; ++i)
		crc = table[(uint8_t)crc ^ ((uint8_t*)data)[i]] ^ crc >> 8;
	return crc;
}

void showTasks()
{
	printf("Your remaining tasks are: \n");
	for (int x = 0; x < 10; x++)
	{
		if (strchr(tasklog, x + 0x30))
			continue;
		printf("%d: %s\n", x, tasks[x].name);
	}
	printf("\n");
}

//const char* correct = "3145926870";

extern char encrypted[];
extern size_t encrypted_len;

void dead()
{
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⠋⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⠈⢻⣿⣿⡄⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⣸⣿⡏⠀⠀⠀⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣄⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⣿⣿⠁⠀⠀⢰⣿⣿⣯⠁⠀\\/⠀⠀\\/⠈⠙⢿⣷⡄⠀\n"
"⠀⠀⣀⣤⣴⣶⣶⣿⡟⠀⠀⠀⢸⣿⣿⣿⣆⠀/\\⠀⠀/\\⠀⠀⠀⣿⣷⠀\n"
"⠀⢰⣿⡟⠋⠉⣹⣿⡇⠀⠀⠀⠘⣿⣿⣿⣿⣷⣦⣤⣤⣤⣶⣶⣶⣶⣿⣿⣿⠀\n"
"⠀⢸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀\n"
"⠀⣸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠉⠻⠿⣿⣿⣿⣿⡿⠿⠿⠛⢻⣿⡇⠀⠀\n"
"⠀⠸⣿⣧⡀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠃⠀⠀\n"
"⠀⠀⠛⢿⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⣰⣿⣿⣷⣶⣶⣶⣶⠶⠀⢠⣿⣿⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⣽⣿⡏⠁⠀⠀⢸⣿⡇⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⢹⣿⡆⠀⠀⠀⣸⣿⠇⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁⠀⠈⠻⣿⣿⣿⣿⡿⠏⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠈⠛⠻⠿⠿⠿⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("DEFEAT\n\nYour crewmates were all killed before you could finish your tasks.");
	exit(1);
}

int nameused(uint8_t index)
{
	for(int x = 0; x < 10; x++)
	{
		if (tasks[x].original_name == index)
			return 1;
	}
	return 0;
}

int main(int argc, char** argv)
{
	char buf[20];
	char tid;

	setvbuf(stdout, NULL, _IONBF, 0);
	srand(time(0));

	if (getenv("DEBUG") == NULL)
	{
		alarm(30);
	}

	//Generate tasks
	for(int x = 0; x < 10; x++){
		tasks[x].id = x;
		uint8_t randIndex;
		do
		{
			randIndex = rand() % TASKCOUNT;
		} while (nameused(randIndex));
		strcpy(tasks[x].name, shortTaskNames[randIndex]);
		tasks[x].time = (rand() & 4) + 1;
		tasks[x].original_name = randIndex;
	}


	setlocale(LC_ALL, NULL);
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⡀⣄⣤⣦⣶⣤⣤⣤⣤⣤⣠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀	                                                     	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⡀⣤⣷⣿⢿⠻⠛⠛⠛⠛⠙⠉⠛⡿⣿⣴⢀⠀⠀⠀⠀⠀⠀⠀⠀	                                                     	⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⡄⣿⣿⢻⠈⣀⣀⢀⠀⠀⠀⠀⠀⠀⠀⠋⣿⣼⠀⠀⠀⠀⠀⠀⠀⠀	                                                     	⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⠋⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⠈⢻⣿⣿⡄⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⣄⣿⣿⣿⢿⠿⠿⠿⣿⣿⣿⣾⣶⣠⠀⠀⠀⡏⣿⣸⠀⠀⠀⠀⠀⠀⠀	                                                     	⠀⠀⠀⠀⠀⠀⠀⣸⣿⡏⠀⠀⠀⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣄⠀⠀⠀\n");
	printf("⠀⡄⣷⢿⠙⠈⠀⠀⠀⠀⠀⠀⠀⠁⣯⣿⣿⢰⠀⠀⠁⣿⣿⠀⠀⠀⠀⠀⠀⠀	        Welcome to the Among Them Challenge!         	⠀⠀⠀⠀⠀⠀⠀⣿⣿⠁⠀⠀⢰⣿⣿⣯⠁⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⣷⡄⠀\n");
	printf("⠀⣷⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣆⣿⣿⣿⢸⠀⠀⠀⡟⣿⣶⣶⣴⣤⣀⠀⠀	                                                     	⠀⠀⣀⣤⣴⣶⣶⣿⡟⠀⠀⠀⢸⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣷⠀\n");
	printf("⠀⣿⣿⣿⣶⣶⣶⣶⣤⣤⣤⣦⣷⣿⣿⣿⣿⠘⠀⠀⠀⡇⣿⣹⠉⠋⡟⣿⢰⠀	 Your task is to navigate through this derelict ship 	⠀⢰⣿⡟⠋⠉⣹⣿⡇⠀⠀⠀⠘⣿⣿⣿⣿⣷⣦⣤⣤⣤⣶⣶⣶⣶⣿⣿⣿⠀\n");
	printf("⠀⠃⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠹⠀⠀⠀⠀⡇⣿⣿⠀⠀⡇⣿⢸⠀	 with your fellow crewmates. But be warned; one of   	⠀⢸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀\n");
	printf("⠀⠀⡇⣿⢻⠛⠿⠿⡿⣿⣿⣿⣿⠿⠻⠉⠀⠀⠀⠀⠀⡇⣿⣿⠀⠀⡇⣿⣸⠀	 your crewmates is a fraud who will stop at nothing  	⠀⣸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠉⠻⠿⣿⣿⣿⣿⡿⠿⠿⠛⢻⣿⡇⠀⠀\n");
	printf("⠀⠀⠃⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⣿⣿⠀⡀⣧⣿⠸⠀	 to kill you all before you can restore the ship.    	⠀⠸⣿⣧⡀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠃⠀⠀\n");
	printf("⠀⠀⠀⣿⣿⢠⠀⠶⣶⣶⣶⣶⣷⣿⣿⣰⠀⠀⠀⠀⠀⣇⣿⣿⣿⣿⢿⠛⠀⠀	                                                     	⠀⠀⠛⢿⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⣰⣿⣿⣷⣶⣶⣶⣶⠶⠀⢠⣿⣿⠀⠀⠀\n");
	printf("⠀⠀⠀⡇⣿⢸⠀⠀⠁⡏⣿⣽⠀⡇⣿⣿⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀	 Good luck.                                          	⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⣽⣿⡏⠁⠀⠀⢸⣿⡇⠀⠀⠀\n");
	printf("⠀⠀⠀⠇⣿⣸⠀⠀⠀⡆⣿⢹⠀⡇⣿⣿⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀	                                                     	⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⢹⣿⡆⠀⠀⠀⣸⣿⠇⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠏⡿⣿⣿⣿⣿⠻⠈⠀⠁⣿⣿⣴⣠⣀⣄⣦⣿⢿⠀⠀⠀⠀⠀⠀⠀	                                                     	⠀⠀⠀⠀⠀⠀⠀⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁⠀⠈⠻⣿⣿⣿⣿⡿⠏⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠋⠿⠿⠿⠿⠻⠛⠈⠀⠀⠀⠀⠀⠀⠀	                                                     	⠀⠀⠀⠀⠀⠀⠀⠈⠛⠻⠿⠿⠿⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");

	char* dummy3 = "80 char width terms are for space cadets.";

	while (strlen(tasklog) < 10)
	{
		//Still tasks remaining
		showTasks();
		printf("q: QUIT\n");
		printf("  Which task do you want to do next? ");
		if (!scanf("%19s", &buf))
			continue;
		if ((buf[0] & 0xdf) == 0x51) //let's talk about upper to lower conversion in hex!
			exit(0);
		if (sscanf(buf, "%d", &tid) == 1)
		{
			if (!strchr(tasklog, tid + 0x30) && tid >= 0 && tid <= 9)
			{
				finishTask(tasks[tid]);
				//printf("Adding %c to the list\n", tid + 0x30);
				tasklog[strlen(tasklog)] = tid + 0x30;
			} else {
				printf("ERROR: That is not a valid remaining task.\n\n");
			}
		} else {
			printf("Invalid digit. You entered:\n\n");
			printf(&buf);
			printf("\n\nPlease enter a valid task.\n\n");
		}

	}

	//Uncomment to debug
	//strcpy(tasklog, "3145926870");
	//printf("%lu, %s", strlen(tasklog), tasklog);
	printf("Good work! Your tasks are done, let's check on your crewmates to see if you saved the ship");
	dots(5);
	printf("\n");

	if ((crc32(&tasklog, 10) == checksum) && \
		(crc32(&tasklog, 5) == checksum_left) && \
		(crc32(&tasklog[5], 5) == checksum_right))
	{
		printf("\nCongratulations! You managed to save your ship from destruction.\n\n");
		long one = (tasklog[0] << 25) + (tasklog[2] << 17) + (tasklog[1] << 9) + (tasklog[3] << 0) + 0;
		long two = (tasklog[2] << 25) + (tasklog[4] << 17) + (tasklog[3] << 9) + (tasklog[5] << 0) + 1;
		long three = (tasklog[4] << 25) + (tasklog[6] << 17) + (tasklog[5] << 9) + (tasklog[7] << 0) + 2;
		long four = (tasklog[6] << 25) + (tasklog[8] << 17) + (tasklog[7] << 9) + (tasklog[9] << 0) + 3;
		long key[4] = {one, two, three, four};
		//printf("Key: \n%#lx, %#lx, %#lx, %#lx\n", one, two, three, four);

		if (!btea((long *)encrypted, -encrypted_len, key)) {
			printf("%s\n", encrypted);
		} else {
			printf("Failed.");
		}
	} else {
		dead();
	}
}
