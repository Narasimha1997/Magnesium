#define _BSD_SOURCE
#include<sys.h>
#include<stdlib.h>
#include<stdio.h>

//allocates a page for object code
PAGE * sys_page_alloc() {
    PAGE * page = (PAGE *)malloc(sizeof(PAGE));

    int __OS_PAGE_SIZE = __GET_SYS_CONF(_SC_PAGESIZE);
    page->allocation_ptr =  (void*)mmap(
         NULL, 
         __OS_PAGE_SIZE, 
         PAGE_NOT_EXECUTABLE, 
         MAP_ANONYMOUS | MAP_PRIVATE, 
         -1, 0
    );

    page->buffer_size = __OS_PAGE_SIZE;
    page->PAGE_FLAGS = PAGE_NOT_EXECUTABLE;

    return page;
}

void sys_page_unalloc(OPCODE_CACHE * opcodecache) {
    
}

OPCODE_CACHE * page_to_opcode_buffer(PAGE * page) {

    if(page->PAGE_FLAGS != PAGE_NOT_EXECUTABLE) {
        fprintf(stdout, "Invalid page found, so disacrding\n");
        exit(0);
    }

    OPCODE_CACHE * opcache = (OPCODE_CACHE *)malloc(sizeof(OPCODE_CACHE));

    opcache->marker = 0;
    opcache->buffer_ptr = page->allocation_ptr;
    return opcache;
}


void make_executable(OPCODE_CACHE * cache){
    mprotect(cache->buffer_ptr, __GET_SYS_CONF(_SC_PAGESIZE), PAGE_NOT_WRITABLE);
}


