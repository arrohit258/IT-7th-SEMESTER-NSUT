#include <unistd.h>
#include <stdio.h>
int main()
{
int pipefds[2];
int returnstatus;
char writemessages[20]="Divyanshu";
char readmessage[20];
returnstatus = pipe(pipefds);
 
 if (returnstatus == -1) {
 printf("Unable to create pipe\n");
 return 1;
 }
 // Creating first child
int n1 = fork();

if (n1 > 0) //finding parent ID
{
    printf("parent\n");
    printf("n1:\t %d \n", n1);
    printf("my id (parent) is %d \n", getpid());
    waitpid(n1, NULL, 0);
    // Creating second child. 
    int n2 = fork(); 
    if(n2==0){
        printf("second child\n");
        printf("n2: \t %d \n", n2);
        printf("my id is (Second child) %d \n", getpid());
        printf("my parentid ( for second child)is %d \n", getppid());
        
        read(pipefds[0], readmessage, sizeof(readmessage));
        printf("Reading from pipe – Message 1 is %s\n", readmessage);
    }
    else{
        waitpid(n2, NULL, 0);
    }   

}
else if (n1 == 0) //child 1 writing to pipe
{
    printf("First child\n");
    printf("n1:\t %d \n", n1);
    printf("my id is (First child) %d \n", getpid());
    printf("my parentid (for first child) is %d \n", getppid());
    printf("Writing to pipe - Message 1 is %s\n", writemessages);
    write(pipefds[1], writemessages, sizeof(writemessages));
}

return 0;
}
