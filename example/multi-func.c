#include<stdio.h>
#include "sub_func.h"

void func(){
    printf("function call success %d\n", 2);
}

int main(int argc, char* argv[]){
    printf("main entry\n");
    printf("the value returned by func2 %d\n", func2(123));
    int a = 2;
    if (a>2)
        func();
    else
        func2(123);
    return 0;
}

