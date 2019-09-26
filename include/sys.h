#ifndef __SYS_H
#define __POSIX_SOURCE

#include<unistd.h>
#include<sys/mman.h>
#include <sys/types.h>
#include<fcntl.h>
#include<asm.h>

#define __GET_SYS_CONF(parameter) (sysconf(parameter))

#define PAGE_NOT_EXECUTABLE  (PROT_READ | PROT_WRITE)
#define PAGE_NOT_WRITABLE (PROT_READ | PROT_EXEC)

struct mmap_allocation_t {
    void * allocation_ptr;  //points to page on memory
    unsigned int buffer_size; // Size of the page, usually size of the page supported by OS
    u_int8_t PAGE_FLAGS; //Flags used , can check if the page is R / W / X able
};

//A PAGE type is a logical representation of a page in memory
typedef struct mmap_allocation_t PAGE;

//allocates a a page and returns the start address
PAGE * sys_page_alloc();

//given a pointer, unallocate the page if it points to a valid page
void sys_page_unallc(PAGE * page);

OPCODE_CACHE * page_to_opcode_buffer(PAGE * page);

void finalize_opcode_cache(OPCODE_CACHE * cache);
void make_executable(OPCODE_CACHE * cache);


#endif