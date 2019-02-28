#include<stdio.h>

int main(int argc, char** argv){
    int counter; 
    printf("Program Name Is: %s\n",argv[0]); 
    if(argc==1) 
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name\n"); 
    if(argc>=2) 
    { 
	for(counter=0;counter<argc;counter++) 
            printf("argv[%d]: %s\n",counter,argv[counter]); 
    }
    return 0;
}
