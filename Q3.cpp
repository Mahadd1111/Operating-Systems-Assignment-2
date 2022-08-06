#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<string.h>
#include<iostream>
#include<ctime>
#include <random>
using namespace std;

//We randomly generate a time between 5-10 inside the employee and this represents the time employee cannot come to the meeting
//the parent reads this time and after reading from all employees, decides what time everyone is available
//we have sliced time on hourly basis

int array[10];
int randval=123;

int main(){
    cout<<"OWNER: Asking for times employees are unavailable from 5-10 pm"<<endl;
    int k=0;
    int val2;
    int count=0;
    pid_t employee1;
    for(int i=0;i<10;i++){
        int fd1[2];
        pipe(fd1);
        randval=randval+20;
        srand(randval);
        employee1=fork();
        if(employee1==0){
            //employee1
            int val=(rand()%5)+5;
            cout<<"Employee "<<i+1<<" is not available at time: "<<val<<endl;
            close(fd1[0]);
            write(fd1[1],&val,sizeof(val));
            exit(0);
        }
        else{
            wait(NULL);
            close(fd1[1]);
            read(fd1[0],&val2,sizeof(val2));
            array[k]=val2;
            k++;
        }
    }
    for(int i=5;i<=10;i++){
        bool flag=true;
        for(int j=0;j<10;j++){
            if(i==array[j]){
                flag=false;
            }
        }
        if(flag==true){
            cout<<"First Available time for all employees is: "<<i<<" pm"<<endl;
            break;
        }
    }
    return 0;
}