#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<iostream>
using namespace std;

int main(){
    //taking input string
    char str[256]="tempval";
    //making the pipes
    int check=mkfifo("MYPIPE1",0666);
    if(check<0){
        printf("PIPE NOT CREATED/EXISTS\n");
    }
    else{
        printf("PIPE CREATED\n");
    }
    
    check=mkfifo("MYPIPE2",0666);
    if(check<0){
        printf("PIPE NOT CREATED/EXISTS\n");
    }
    else{
        printf("PIPE CREATED\n");
    }
    check=mkfifo("MYPIPE3",0666);
    if(check<0){
        printf("PIPE NOT CREATED/EXISTS\n");
    }
    else{
        printf("PIPE CREATED\n");
    }
    //writing to the pipes
    while(strcmp(str,"abort")!=0){
        printf("Enter a string input to send to Pipes, entering \"abort\" will exit: ");
        cin.getline(str,256);
        int wpipe=open("MYPIPE1",O_RDWR);
        if(wpipe<0){
            printf("Cannot open write Pipe\n");
        }
        else{
            write(wpipe,str,sizeof(str));
            close(wpipe);
        }
        wpipe=open("MYPIPE2",O_RDWR);
        if(wpipe<0){
            printf("Cannot open write Pipe\n");
        }
        else{
            write(wpipe,str,sizeof(str));
            close(wpipe);
        }
        wpipe=open("MYPIPE3",O_RDWR);
        if(wpipe<0){
            printf("Cannot open write Pipe\n");
        }
        else{
            write(wpipe,str,sizeof(str));
            close(wpipe);
        }
    }
    return 0;
}