#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main() {
 int pipefds1[2], pipefds2[2];
 int returnstatus1, returnstatus2;
 int pid;
 char pipe1writemessage[20];
 char pipe2writemessage[20];
 char readmessage[20];
 returnstatus1 = pipe(pipefds1);
 
 if (returnstatus1 == -1) {
 printf("Unable to create pipe 1 \n");
 return 1;
 }
 returnstatus2 = pipe(pipefds2);
 
 if (returnstatus2 == -1) {
 printf("Unable to create pipe 2 \n");
 return 1;
 }
 int n1 = fork();
 int n2=fork();
 
 if (n1 > 0 && n2 > 0) {
    
 printf("parent\n");
 printf("%d %d \n", n1, n2);
 printf(" my id (parent) is %d \n", getpid());
 printf("_____________________\n");
//  waitpid(n1, NULL, 0);
//  waitpid(n2, NULL, 0);
 }
 int pip1=1;
while(pip1) {
 if (n1> 0 && n2 ==0){ // child 2
 printf("parent id %d\n",getppid());
 close(pipefds1[0]); // Close the unwanted pipe1 read side
 close(pipefds2[1]); // Close the unwanted pipe2 write side
 
 printf("In Child 2: Writing to pipe 1 – Message is \n");
 scanf("%s", pipe1writemessage);
 if(strcmp(pipe1writemessage,"STOP")==0) {
    close(pipefds1[1]); 
    close(pipefds2[0]); 
    break;
 }
 write(pipefds1[1], pipe1writemessage, sizeof(pipe1writemessage));
 read(pipefds2[0], readmessage, sizeof(readmessage));
 printf("In Child 2: Reading from pipe 2 – Message is %s\n", readmessage);
 
 }
 else if(n1==0 && n2>0) { //child1 process
 printf("parent id %d\n",getppid());
 close(pipefds1[1]); // Close the unwanted pipe1 write side
 close(pipefds2[0]); // Close the unwanted pipe2 read side
 read(pipefds1[0], readmessage, sizeof(readmessage));
 printf("In Child 1: Reading from pipe 1 – Message is %s\n", readmessage);
 printf("In Child 1: Writing to pipe 2 – Message is \n");
 scanf("%s", pipe2writemessage);
 if(strcmp(pipe2writemessage,"STOP")==0) {
    close(pipefds1[0]); 
    close(pipefds2[1]); 
 
    break;
 }
 write(pipefds2[1], pipe2writemessage, sizeof(pipe2writemessage));
 }
}
 return 0;
}