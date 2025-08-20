/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * This is the producer process that writes to the shared memory region.
 *
 * Figure 3.17
 *
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
	const int SIZE = 4096;
	const char *name = "OS";
	const char *message0= "freeeee";
	const char *message1= "OSisFUN";

	int shm_fd;
	void *ptr;

	/* create the shared memory segment */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* configure the size of the shared memory segment */
	ftruncate(shm_fd,SIZE);

	/* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	/**
	 * Now write to the shared memory region.
 	 *
	 * Note we must increment the value of ptr after each write.
	 */
	
	void *curr = ptr ;
	for(int i = 0 ; i < 512 ; i++ ){	
		sprintf(curr,"%s",message0);
		curr += strlen(message0);
		//sleep(1) ;
	}
	

	curr = ptr ;
	for(int i = 0 ; i < 512 ; i++ ){	
		sprintf(curr,"%s",message1);
		curr += strlen(message1);
		sleep(1) ;
	}
	
	return 0;
}
