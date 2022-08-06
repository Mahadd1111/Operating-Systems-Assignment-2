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
    //Opening the pipe and reading from it
    char str[100]="temp";
    int rpipe=open("MYPIPE1",O_RDWR);
    if(rpipe<0){
        printf("Cannot open read Pipe\n");
    }
    else{
        read(rpipe,str,sizeof(str));
        printf("Value read is: %s\n",str);
        close(rpipe);
    }
    printf("%s\n",str);
    //finding vowels and displlaying count
    int count=0;
    for(int i=0;i<strlen(str);i++){
        if(str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u'||
           str[i]=='A'||str[i]=='E'||str[i]=='I'||str[i]=='O'||str[i]=='U'){
               printf("Vowel %c has occurred\n",str[i]);
               count++;
           }
    }
    printf("Number of Vowels found: %d\n",count);
}