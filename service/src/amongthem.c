#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <locale.h>

/* 

	Build:
	gcc -o amongthem -static amongthem.c && strip amongthem

	#Harden
	gcc -o amongthem -D_FORTIFY_SOURCE=2 -O1 -no-pie -static -fno-stack-protector amongthem.c && strip amongthem

 */

struct Task {
	uint8_t id;
	char name[30];
	uint8_t time;
};

struct Task tasks[10];

//char* checksum = "\xff\xff\xff\xff";
int32_t checksum = 329936096;

char tasklog[20]; 

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

void dots(int count)
{
	for(int x = 0; x < count; x++)
	{
		//sleep(1);
		printf(".");
	}
}

void finishTask(struct Task task)
{
	printf("\n\nWorking on %s...", task.name);
	dots(task.time);
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

/*

3
1
4
5
9
2
6
8
7
0

const char* correct = "3145926870";
const char* flag = "FLAG{SurpriseTheImposterWas5up!}";
const char* encrypted = "\xbb&\xce\xc7\xf4{\xdb\x9c\x015c\xffy\xb5\xbe\x96\x9d\xbb\xc1\xff\xac%\xc8\xd1\xa0\x1br\x98\xa8m\xce\xa8";
char* encrypted ="bb26cec7f47bdb9c013563ff79b5be969dbbc1ffac25c8d1a01b7298a86dcea8";
*/
char encrypted[32] = 
{
	0xbb, 0x26, 0xce, 0xc7, 0xf4, 0x7b, 0xdb, 0x9c, 0x01, 0x35, 0x63, 0xff, 0x79, 0xb5, 0xbe, 0x96,
	0x9d, 0xbb, 0xc1, 0xff, 0xac, 0x25, 0xc8, 0xd1, 0xa0, 0x1b, 0x72, 0x98, 0xa8, 0x6d, 0xce, 0xa8
};

//From: https://en.wikipedia.org/wiki/XXTEA
#define MX (z>>5^y<<2) + (y>>3^z<<4)^(sum^y) + (k[p&3^e]^z);
long btea(long* v, long n, long* k) {
	unsigned long z=v[n-1], y=v[0], sum=0, e, DELTA=0x9e3779b9;
	long p, q ;
	if (n > 1) {          /* Coding Part */
		q = 6 + 52/n;
		while (q-- > 0) {
			sum += DELTA;
			e = (sum >> 2) & 3;
			for (p=0; p<n-1; p++) y = v[p+1], z = v[p] += MX;
			y = v[0];
			z = v[n-1] += MX;
		}
		return 0 ; 
	} else if (n < -1) {  /* Decoding Part */
		n = -n;
		q = 6 + 52/n;
		sum = q*DELTA ;
		while (sum != 0) {
			e = (sum >> 2) & 3;
			for (p=n-1; p>0; p--) z = v[p-1], y = v[p] -= MX;
			z = v[n-1];
			y = v[0] -= MX;
			sum -= DELTA;
		}
		return 0;
	}
	return 1;
}

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
	printf("Sorry, it looks like your crewmates were all killed before your \n"
		"tasks were completed.\n");
	exit(1);
}

int main(int argc, char** argv)
{
	char buf[20];
	char tid;
	setvbuf(stdout, NULL, _IONBF, 0);
	srand(time(0));
/*
	if (getenv("DEBUG") == NULL)
	{
		alarm(30);
	}
*/

	//Generating tasks
	shuffleTasks();
	for(int x = 0; x < 10; x++){
		strcpy(tasks[x].name, shortTaskNames[x]);
		tasks[x].id = x;
		tasks[x].time = rand() & 4 + 1;
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

char* dummy = "80 char width terms are for space cadets.";

/*
	while (strlen(tasklog) < 10)
	{
		//Still tasks remaining
		showTasks();
		printf("q: QUIT\n");
		printf("  Which task do you want to do next? ");
		if (!scanf("%s", &buf))
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
	*/



	strcpy(tasklog, "3145926870");
	printf("%d, %s", strlen(tasklog), &tasklog);
	printf("Good work! Your tasks are done, let's check on your crewmates to see if you saved the ship");
	dots(5);
	printf("\n");
	crc32(&tasklog, strlen(tasklog), &crc);
	if (crc == checksum)
	{
		printf("Congratulations! You managed to save your ship from destruction.");
		long one = (tasklog[0] << 25) + (tasklog[2] << 17) + (tasklog[1] << 9) + (tasklog[3] << 0) + 0;
		long two = (tasklog[2] << 25) + (tasklog[4] << 17) + (tasklog[3] << 9) + (tasklog[5] << 0) + 1;
		long three = (tasklog[4] << 25) + (tasklog[6] << 17) + (tasklog[5] << 9) + (tasklog[7] << 0) + 2;
		long four = (tasklog[6] << 25) + (tasklog[8] << 17) + (tasklog[7] << 9) + (tasklog[9] << 0) + 3;
		long key[4] = {one, two, three, four};
		printf("Key: \n%lu %lu %lu %lu\n", one, two, three, four);
		/*
		for(int i = 0; i < strlen(encrypted) / 2; ++i)
		{
			sscanf(&encb64[i], "%02X", (uint*) &encrypted[2 * i]);
		}
		*/

		if (btea((long *)encrypted, -2, key))
			printf("%s\n", encrypted);
		else
			printf("Failed.");
		//Decrypt the ecnrypted blob
	} else {
		dead();
	}
}
