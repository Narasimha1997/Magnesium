#ifndef __EXEC_H
#define __EXEC_H

#include<stdio.h>
#include<parser.h>
#include<sys.h>
#include<asm.h>

void compile_recurrence_relation(OPCODE_CACHE * cache);

long exec_recurrence_relation(FILE * fd);

#endif