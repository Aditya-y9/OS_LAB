#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
int n=0;
int m=0;
pid_t pid;
do{
printf("Enter the number:\n");
scanf("%d",&m);
}
while(m<=0);
pid=fork();
if(pid==0)
{
printf("child \n");
printf("%d",m);
while(m!=1)
{
if(m%2==0)
{
m=m/2;
}
else if(m%2==1)
{
m=3*(m)+1;
}
printf("%d",m);
}
printf("child process is completed \n");
}
else
{
printf("parent is waiting \n");
wait(NULL);
printf("Parent process is completed \n");
}
Return 0;
}