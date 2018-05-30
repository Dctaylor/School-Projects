 /**************************
 *     socket example, server
 *     spring 2018
 ***************************/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>

int main (int, char *[]); 


/*********************
 * main
 *********************/
int main (int argc, char *argv[])
{
	int	n;
	char *p; 
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr; 
	char buff[10];
	char file[1024];

	// set up
	memset (&serv_addr, '0', sizeof (serv_addr));
	memset (buff, '0', sizeof (buff)); 

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl (INADDR_ANY);
	serv_addr.sin_port = htons (atoi(argv[1])); 

	// create socket, bind, and listen
	listenfd = socket (AF_INET, SOCK_STREAM, 0);
	bind (listenfd, (struct sockaddr*)&serv_addr, sizeof (serv_addr)); 
	listen (listenfd, 10); 

	// accept and interact
	while (1) {
		connfd = accept (listenfd, (struct sockaddr*)NULL, NULL); 

		printf("connected\n");

		// receive output File Name
		if((n = read (connfd, file, sizeof (file))) > 0) {
			printf("\n");
			p = file;
			printf(p);
			printf("\n");
		}

		printf("read in output file name\n");
		//open output file
		FILE *fp = fopen(p,"wb");

		printf("opened out file\n");

		//write text from in file to output file
		while ((n = read (connfd, buff, 10)) > 0) {
			fwrite(buff, 1, n, fp);
		}

		printf("read input file and wrote to output file\n");
		fclose(fp);
		printf("closed file\n");
		close(connfd);
		printf("closed connection\n");
		break;
	}
	return 0; 
}
