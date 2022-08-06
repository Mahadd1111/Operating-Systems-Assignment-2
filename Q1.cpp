#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<string.h>
#include<iostream>
using namespace std;

int main(){
    int pipefd1[2];
    int pipefd2[2];
    int pipefd3[2];
    int status;
    int done=0;
    pipe(pipefd1);
    pipe(pipefd2);
    pipe(pipefd3);
    pid_t cpid1=fork();
    if(cpid1==0){
        close(pipefd1[0]);
        dup2(pipefd1[1],1);
        execlp("ls","ls","-l","/",NULL);
    }
    pid_t cpid2=fork();
    if(cpid2==0){
        close(pipefd1[1]);
        close(pipefd2[0]);
        dup2(pipefd1[0],0);
        dup2(pipefd2[1],1);
        execlp("grep","grep","a",NULL);
    }
    pid_t cpid3=fork();
    if(cpid3==0){
        close(pipefd1[0]);
        close(pipefd1[1]);
        close(pipefd2[1]);
        dup2(pipefd2[0],0);
        close(pipefd3[0]);
        dup2(pipefd3[1],1);
        execlp("sort","sort","-r",NULL);
    }
    pid_t cpid4=fork();
    if(cpid4==0){
        close(pipefd1[0]);
        close(pipefd1[1]);
        close(pipefd2[1]);
        close(pipefd2[0]);
        close(pipefd3[1]);
        dup2(pipefd3[0],0);
        close(pipefd3[0]);
        int file=open("count.txt",O_RDWR);
        dup2(file,1);
        execlp("wc","wc",NULL);
    }
    close(pipefd1[0]);
    close(pipefd1[1]);
    close(pipefd2[1]);
    close(pipefd2[0]);
    close(pipefd3[0]);
    close(pipefd3[1]);
    waitpid(cpid1,NULL,0);
    waitpid(cpid2,NULL,0);
    waitpid(cpid3,NULL,0);
    waitpid(cpid4,NULL,0);
}