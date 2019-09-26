#include<asm.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

//creates a buffer of machine instruction word

//this function performs immediate assignment of operand to %rdi register
void asm_immediate_assignment(OPCODE_CACHE * buffer, uint64_t word, unsigned int size,  const void * data, unsigned int op_size) {
    int iter;

    //create instruction for immediate assignment
    for(iter = size - 1; iter >= 0; iter --) 
       buffer->buffer_ptr[buffer->marker ++] = (word >> (iter * 8)) & 0xff;
    
    //move the operand , in little endian format, this will be taken care by OS itself
    memcpy(buffer->buffer_ptr + buffer->marker, data, op_size);
    buffer->marker = buffer->marker + op_size; 
}

void asm_move_instruction(OPCODE_CACHE * cache, uint8_t DESTINATION, uint8_t SOURCE) {
    uint8_t movByte = get_mod_reg_encoded_byte(x86_64_Direct, SOURCE, DESTINATION);
    add_instruction_to_cache(cache, 3, x86_64_REGISTER_REX, x86_64_MOV, movByte);
}

void asm_terminate_code(OPCODE_CACHE * cache) {
    //adds ret instruction
    cache->buffer_ptr[cache->marker ++] = x86_64_RET;
}

void binary_instruction_encoder(OPCODE_CACHE * buffer,  char operator, uint8_t DESTINATION, uint8_t SOURCE) {
    //create x86_64 instruction word :
     uint8_t modReg = 0;
    
    uint8_t xorMByte, divMByte;

    switch(operator) {
        case '+' :
           modReg = get_mod_reg_encoded_byte(
               x86_64_Direct, SOURCE, DESTINATION
           );
           add_instruction_to_cache(
               buffer, 3 , 
               x86_64_REGISTER_REX,  
               x86_64_ADD, 
               modReg
            ); break;
        
        case '-' :
            modReg = get_mod_reg_encoded_byte(
               x86_64_Direct, SOURCE, DESTINATION
            );
            add_instruction_to_cache(
               buffer, 3 , 
               x86_64_REGISTER_REX,  
               x86_64_SUB, 
               modReg
            ); break;
        case '*' :
            modReg = get_mod_reg_encoded_byte(
               x86_64_Direct, DESTINATION, SOURCE
            );
            add_instruction_to_cache(
               buffer, 4 , 
               x86_64_REGISTER_REX,  
               x86_64_IMUL_PREFIX,
               x86_64_IMUL, 
               modReg
            ); break;
        
        case '^' :
            modReg = get_mod_reg_encoded_byte(
               x86_64_Direct, SOURCE, DESTINATION
            );
            add_instruction_to_cache(
               buffer, 3 , 
               x86_64_REGISTER_REX,  
               x86_64_XOR, 
               modReg
            ); break;
        
        case '|' :
            modReg = get_mod_reg_encoded_byte(
               x86_64_Direct, SOURCE, DESTINATION
            );
            add_instruction_to_cache(
               buffer, 3 , 
               x86_64_REGISTER_REX,  
               x86_64_OR, 
               modReg
            ); break;
        
        case '&' :
            modReg = get_mod_reg_encoded_byte(
               x86_64_Direct, SOURCE, DESTINATION
            );
            add_instruction_to_cache(
               buffer, 3 , 
               x86_64_REGISTER_REX,  
               x86_64_AND, 
               modReg
            ); break;
        
        case '/' :
            modReg = get_mod_reg_encoded_byte(
               x86_64_Direct, SOURCE, DESTINATION
            );
            xorMByte = get_mod_reg_encoded_byte(
                x86_64_Direct,
                x86_64_REG_RDX,
                x86_64_REG_RDX
            );
            divMByte = get_mod_reg_encoded_byte(
                x86_64_Direct,
                SOURCE,
                SOURCE
            );

            add_instruction_to_cache(
                buffer, 3, 
                x86_64_REGISTER_REX,
                x86_64_XOR,
                xorMByte
            );
            add_instruction_to_cache(
                buffer, 3,
                x86_64_REGISTER_REX,
                x86_64_IDIV,
                divMByte
            );
            break;
    }
}

//test
