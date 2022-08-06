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
    int rpipe=open("MYPIPE3",O_RDWR);
    if(rpipe<0){
        printf("Cannot open read Pipe\n");
    }
    else{
        read(rpipe,str,sizeof(str));
        printf("Value read is: %s\n",str);
        close(rpipe);
    }
    printf("%s\n",str);
    //reversing a string
    int n=strlen(str);
    for(int i=0;i<n/2;i++){
        char temp=str[i];
        str[i]=str[n-i-1];
        str[n-i-1]=temp;
    }
    printf("Reverse string is: %s\n",str);
}