#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(){

	int fd, ret;

	char buf[32];

	buf[0]=0;

	fd=open("F6U7WO.txt",O_RDWR);

	if(fd == -1){
		perror("Open() hiba!");
		exit(-1);
	}

	ret=lseek(fd,0,SEEK_SET);
	printf("lseek() eredménye: %d\n",ret);

	ret=write(fd,buf,32);
	printf("write() eredmenye: %d\n",ret);

	ret=read(fd,buf,32); //Beolvasott kerekterek száma
	printf("read() olvasott %d bytot, ami a kovetkezo: %s\n",ret,buf);
	strcpy(buf,"F6U7WO");

	close(fd);

}
