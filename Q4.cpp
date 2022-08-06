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
    bool flag=false;
    int input=dup(0);
    int output=dup(1);
    while(flag==false){
        cout<<"------------------------"<<endl;
        dup2(input,0);
        dup2(output,1);
        int savestdout[2];
        pipe(savestdout);
        int savestdin[2];
        pipe(savestdin);
        char a[100]="temp";
        char b[100]="temp";
        char c[100]="temp";
        char d[100]="temp";
        char e[100]="temp";
        int fd1[2];
        pipe(fd1);
        int fd5[2];
        pipe(fd5);
        char message[100]="";
        cout<<"Enter an Input string (enter \"Z\" to exit): ";
        cin.ignore();
        cin.getline(message,100);
        if(strcmp(message,"Z")==0){
            flag=true;
            break;
            exit(0);
        }
        int cpid1=fork();
        if(cpid1>0){
            //P1: message->fd1 (write)
            dup2(savestdout[0],0);
            close(savestdout[1]);
            printf("%s:%d\n",message,getpid());
            dup2(fd1[1],1);
            close(fd1[0]);
            printf("%s:%d\n",message,getpid());
            wait(NULL);
            exit(0);
        }
        else{
            //C1: a<-fd1 (read)
            dup2(fd1[0],0);
            close(fd1[1]);
            scanf("%s",a);
            dup2(savestdout[0],0);
            close(savestdout[1]);
            printf("%s\n",a);
            int fd2[2];
            pipe(fd2);
            pid_t cpid2=fork();
            if(cpid2>0){
                //C1: a->fd2 (write)
                dup2(fd2[1],1);
                close(fd2[0]);
                printf("%s:%d\n",a,getpid());
                wait(NULL);
                exit(0);
            }
            else{
                //C2: b<-fd2 (read)
                dup2(fd2[0],0);
                close(fd2[1]);
                scanf("%s",b);
                dup2(savestdout[0],0);
                close(savestdout[1]);
                printf("%s\n",b);
                int fd3[2];
                pipe(fd3);
                pid_t cpid3=fork();
                if(cpid3>0){
                    //C2: b->fd3 (write)
                    dup2(fd3[1],1);
                    close(fd3[0]);
                    printf("%s:%d\n",b,getpid());
                    wait(NULL);
                    exit(0);
                }
                else{
                    //C3: c<-fd3 (read)
                    dup2(fd3[0],0);
                    close(fd3[1]);
                    scanf("%s",c);
                    dup2(savestdout[0],0);
                    close(savestdout[1]);
                    printf("%s\n",c);
                    int fd4[2];
                    pipe(fd4);
                    pid_t cpid4=fork();
                    if(cpid4>0){
                        //C3: c->fd4 (write)
                        dup2(fd4[1],1);
                        close(fd4[0]);
                        printf("%s:%d\n",c,getpid());
                        wait(NULL);
                        exit(0);
                    }
                    else{
                        //C4: d<-fd4 (read)
                        dup2(fd4[0],0);
                        close(fd4[1]);
                        scanf("%s",d);
                        dup2(savestdout[0],0);
                        close(savestdout[1]);
                        printf("%s\n",d);
                        pid_t cpid5=fork();
                        if(cpid5>0){
                            //C4: d->fd5 (write)
                            dup2(fd5[1],1);
                            close(fd5[0]);
                            printf("%s:%d\n",d,getpid());
                            wait(NULL);
                            exit(0);
                        }
                        else{
                            dup2(fd5[0],0);
                            close(fd5[1]);
                            scanf("%s",e);
                            dup2(savestdout[0],0);
                            close(savestdout[1]);
                            printf("%s\n",e);
                        }
                    }
                }
            }
        }
        fflush(stdin);
        fflush(stdout);
    }
}