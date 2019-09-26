#ifndef __ASM_H

#define __ASM_H

#include<stdint.h>
#include<unistd.h>
#include<stdarg.h>

#define INSTRUCTION_BUFFER_SIZE 8  //can hold 8 bytes at a time, For VLIW machine increase the length
#include<stdio.h>
//declaration of assembly buffer :

// list of x86_64 assembly opcodes supported by Magnesium

//NOTE : These instructions work only on Little-endian x86 machines like Intel

//Machine design description : 

//The machine works according to System V ABI specification
//Prototype of assembly structure 
//     Start -> mov rax, rdi
//              / - do some op with rdi -/
//     End   -> ret rax
//We look at the opcodes of these instructions and define them as a constant

//Prefixes
#define x86_64_REGISTER_REX 0x48

//addressing modes 
#define x86_64_Direct 0x0c

//instuctions //TODO: Add more instructions later
#define x86_64_MOV 0x89
#define x86_64_RET 0xc3
#define x86_64_ADD 0x01
#define x86_64_SUB 0x29
#define x86_64_XOR 0x31
#define x86_64_AND 0x21
#define x86_64_OR  0x09
#define x86_64_IMUL 0xaf //to be implemented
#define x86_64_IDIV 0x00 //to be implemented

#define x86_64_IMUL_PREFIX 0x0f


//register numbers:   //TODO: Add extened registers later
#define x86_64_REG_RAX 0x00
#define x86_64_REG_RCX 0x01
#define x86_64_REG_RDX 0x02
#define x86_64_REG_RBX 0x03
#define x86_64_REG_RSP 0x04
#define x86_64_REG_RBP 0x05
#define x86_64_REG_RSI 0x06
#define x86_64_REG_RDI 0x07

#define x86_64_immediate_assignment 0x48bf


typedef struct opcode_buffer {
    unsigned char * buffer_ptr; //Points to a page that is executable
    unsigned int marker; // marker points to existing byte position in cache
} OPCODE_CACHE;

static inline uint8_t get_mod_reg_encoded_byte(uint8_t mode, uint8_t source, uint8_t destination) {
    //see notes.txt for more details
    uint8_t mod_reg_byte = 0x00;
    mod_reg_byte = (mod_reg_byte | mode << 4);
    mod_reg_byte = (mod_reg_byte | source << 3);
    mod_reg_byte = (mod_reg_byte | destination);

    return mod_reg_byte; 
}

static inline void add_instruction_to_cache(OPCODE_CACHE * cache, int num_args, ...) {
    va_list arg_ptr;
    uint8_t itr = 0;
    va_start(arg_ptr, num_args);
    while(itr < num_args) {
        cache->buffer_ptr[cache->marker ++] = (unsigned char) va_arg(arg_ptr, int);
        itr ++;
    }
    va_end(arg_ptr);
}

void asm_immediate_assignment(OPCODE_CACHE * buffer, uint64_t word, unsigned int size,  const void * data, unsigned int op_size);
void binary_instruction_encoder(OPCODE_CACHE * buffer,  char operator, uint8_t DESTINATION, uint8_t SOURCE);
void asm_terminate_code(OPCODE_CACHE * cache);
void asm_move_instruction(OPCODE_CACHE * cache, uint8_t DESTINATION, uint8_t SOURCE);
//instruction example :
//mov rax, rdi 

#endif


