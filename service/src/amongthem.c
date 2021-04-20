#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>


/* 

	Compilation:
	gcc -o amongthem -no-pie -static -fno-stack-protector amongthem.c && strip amongthem

 */


/*
 *
 *
 * Global task list
 *
 * ?
 */

struct Task {
	uint8_t id;
	char name[30];
	uint8_t time;
};

struct Task tasks[10];

char* checksum = "\xff\xff\xff\xff";

char tasklog[20]; //={0};

uint32_t crc = 0;

#define TASKCOUNT 34

char const *shortTaskNames[]={
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
"Upload Data"
};

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

void finishTask(struct Task task)
{
	printf("Working on %s...", task.name);
	for(int x = 0; x < task.time; x++)
	{
		//sleep(1);
		printf(".");
	}
	printf("\n\nTask completed!\n\n");
}

uint32_t crc32_for_byte(uint32_t r) {
	for(int j = 0; j < 8; ++j)
		r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
	return r ^ (uint32_t)0xFF000000L;
}

void crc32(const void *data, size_t n_bytes, uint32_t* crc) {
	static uint32_t table[0x100];
	if(!*table)
		for(size_t i = 0; i < 0x100; ++i)
			table[i] = crc32_for_byte(i);
	for(size_t i = 0; i < n_bytes; ++i)
		*crc = table[(uint8_t)*crc ^ ((uint8_t*)data)[i]] ^ *crc >> 8;
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

int main(int argc, char** argv)
{
	char buf[20];
	char tid;
	setvbuf(stdout, NULL, _IONBF, 0);
	srand(time(0));

	if (getenv("DEBUG") == NULL)
	{
		//alarm(10);
	}

	//Generating tasks
	shuffleTasks();
	for(int x = 0; x < 10; x++){
		strcpy(tasks[x].name, shortTaskNames[x]);
		tasks[x].id = x;
		tasks[x].time = rand() & 10 + 1;
	}

	printf("Welcome to the Among Them Challenge!\n\n");
	printf("Your task is to navigate through this derelict ship with your fellow \n" \
"crewmates. But be warned; one of your crewmates is an imposter who will stop \n" \
"at nothing to end your quest to restore your ship.\n\nGood luck.\n\n");

	while (strlen(tasklog) < 10)
	{
		//Still tasks remaining
		showTasks();
		printf("  Which task is next? ");
		if (!scanf("%s", &buf))
			continue;
		if (sscanf(buf, "%d", &tid) == 1)
		{
			if (!strchr(tasklog, tid + 0x30) && tid >= 0 && tid <= 9)
			{
				finishTask(tasks[tid]);
				printf("Adding %c to the list\n", tid + 0x30);
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
	printf("%d, %s", strlen(tasklog), &tasklog);

}
