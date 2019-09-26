#include<exec.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char const *argv[]){

    if(argc < 2) {
        fprintf(stdout, "Usage : magnesium file_path\n");
        exit(0);
    }

    FILE * fp = fopen(argv[1], "r");
    if(fp == NULL) {
        fprintf(stdout, "No such file ! %s\n", argv[1]);
        exit(0);
    }

    exec_recurrence_relation(fp);
    return 0;
}
