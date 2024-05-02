#ifndef __MapRegisters__
#define __MapRegisters__

#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#endif

#define NUM_REGISTERS 16
#define FILE_PATH "registers.bin"
#define FILE_SIZE 1024  // Same size as used in the first program

typedef struct {
    unsigned short *registradores[NUM_REGISTERS];
} Hardware;

Hardware hardware;

/**  
 * FUNCTIONS TO MAP REGISTER MEMORY ADDRESS  
 * Function to open or create the file and map it into memory
 */ 
char* registers_map(const char* file_path, int file_size, int* fd) {
    *fd = open(file_path, O_RDWR | O_CREAT, 0666);
    if (*fd == -1) {
        perror("Error opening or creating file");
        return NULL;
    }

    /* Ensure the file is of the correct size */
    if (ftruncate(*fd, file_size) == -1) {
        perror("Error setting file size");
        close(*fd);
        return NULL;
    }

    /* Map the file into memory */ 
    char *map = mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
    if (map == MAP_FAILED) {
        perror("Error mapping file");
        close(*fd);
        return NULL;
    }

    return map;
}

/**
 *  Function to release mapped memory and file descriptor 
 */ 
int registers_release(void* map, int file_size, int fd) {
    if (munmap(map, file_size) == -1) {
        perror("Error unmapping the file");
        close(fd);
        return -1;
    }

    if (close(fd) == -1) {
        perror("Error closing file");
        return -1;
    }

    return 0;
}

int initializeRegisters(){
    int fd;
    char* map = registers_map(FILE_PATH, FILE_SIZE, &fd);

    if (map == NULL) {
        return EXIT_FAILURE;
    }

  /* DECLARATION OS REGISTERS */
  unsigned short *base_address = (unsigned short *)map;

    for (int i = 0 ; i < NUM_REGISTERS ; i++){
        hardware.registradores[i] = base_address + i;
        printf("Current value of R%d: 0x%02x\n", i +1 , *hardware.registradores[i]);
    }

}