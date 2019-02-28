#include<stdio.h>

void func(int index){
    printf("function call success %d", index);
}

int main(int argc, char* argv[]){
    func(123);
    return 0;
}

