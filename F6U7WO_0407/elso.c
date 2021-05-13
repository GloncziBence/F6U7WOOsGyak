#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(){

char out[80];
int pid, file;
char in[] = "Glonczi Bence";
char * myfifo = "/home/mynameisbence/Documents";
mkfifo(myfifo, 0666);

pid = fork();

if (pid < 0){
	exit(1);
}

if (pid == 0){

	file = open(myfifo, O_WRONLY);
	write(file, in, strlen(in)+1);
	close(file);
	printf("Child: File irasa sikeres!\n");

}

else if (pid > 0 ){

	file = open(myfifo, O_RDONLY);
	read(file, out, strlen(in)+1);
	printf("Parent: kapott: %s\n", out);
	close(file);
}

return 0;
}
