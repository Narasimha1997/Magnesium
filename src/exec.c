#include<stdio.h>
#include<parser.h>
#include<sys.h>
#include<stdlib.h>
#include<asm.h>


void compile_recurrence_relation(FILE * fp, OPCODE_CACHE * cache) {
    
    char operation;
    long operand;

    while(__HAS_NEXT_INPUTS(fp, &operation, &operand)) {
        //process the data:
        if(operation == ' ') continue;

        asm_immediate_assignment(cache, x86_64_immediate_assignment, 2, &operand, 8);

        //process operator:
        binary_instruction_encoder(cache, operation, x86_64_REG_RAX, x86_64_REG_RDI);
        operand = 0; operation = 0;
    }
}


long * exec_recurrence_relation(FILE * fd) {
    if(fd == NULL) {
      fprintf(stdout, "Invalid Input stream, exiting ");
      exit(0);
    }

    //create page , allocate and execute:
    PAGE * allocated_page = sys_page_alloc();
    OPCODE_CACHE * buffer = page_to_opcode_buffer(allocated_page);

    int N;
    long initial;

    __READ_N_VALUE(fd, &N);
    __READ_INITIAL_VALUE(fd, &initial);
    
    asm_move_instruction(buffer, x86_64_REG_RAX, x86_64_REG_RDI);
    compile_recurrence_relation(fd, buffer);
    asm_terminate_code(buffer);

    make_executable(buffer);

    long (*recurrence_relation)(long)  = (void *)buffer->buffer_ptr, result = initial;

    int iter;
    printf("Running for %d times \n", N);
    
    for(iter = 0; iter < N; iter ++ ){
        result = recurrence_relation(result);
        printf("Step %d : Result = %ld\n", (iter + 1),  result);
    }
}


