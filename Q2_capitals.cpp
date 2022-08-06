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
    //opening the pipe and reading from it
    char str[100]="temp";
    int rpipe=open("MYPIPE2",O_RDWR);
    if(rpipe<0){
        printf("Cannot open read Pipe\n");
    }
    else{
        read(rpipe,str,sizeof(str));
        printf("Value read is: %s\n",str);
        close(rpipe);
    }
    printf("%s\n",str);
    //identifying capitals and count
    int count=0;
    for(int i=0;i<strlen(str);i++){
        if(str[i]>=65 && str[i]<=90){
            cout<<"Capital letter found: "<<str[i]<<endl;
            count++;
        }
    }
    printf("Number of capitals found: %d\n",count);
    return 0;
}