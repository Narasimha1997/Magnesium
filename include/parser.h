#ifndef __PARSER_H
#define __PARSER_H

#include<stdio.h>
#include<asm.h>

#define __READ_N_VALUE(ip_ptr, N) (fscanf(ip_ptr, "%d", N))

#define __READ_INITIAL_VALUE(ip_ptr, initial) (fscanf(ip_ptr, "%ld", initial))

#define __GET_NEXT_TOKEN(ip_ptr, ch)(fscanf(ip_ptr, "%c", ch))

#define __READ_OPERAND(ip_ptr, operand)(ip_ptr, fscanf(ip_ptr, "%ld", operand))

static inline int __HAS_NEXT_INPUTS(FILE * ip_ptr, char * ch, long * operand) {
    __GET_NEXT_TOKEN(ip_ptr, ch);
    if(*ch == ' ') return 1;

    if(* ch != '\n' && *ch != EOF) {
        //read the corresponding operand and return +1
        __READ_OPERAND(ip_ptr, operand);
        return +1;
    } 
    return 0;
}

#endif