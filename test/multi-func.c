#include<stdio.h>
#include "sub_func.h"

void func(int index){
    printf("function call success %d\n", index);
}

int main(int argc, char* argv[]){
    printf("main entry\n");
    func2(123);
    func(123);
    return 0;
}

