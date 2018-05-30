 /**************************
	socket example, client
	spring 2018
 **************************/

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

int main (int, char *[]);


/********************
 * main
 ********************/
int main (int argc, char *argv[])
{	
	int i;
	int sockfd = 0, n = 0;
	char buff[10];
	char *p;
	struct sockaddr_in serv_addr; 
	FILE *inputFp = fopen(argv[1],"r");
	size_t data;
	
	if (argc != 5)
	{
		printf ("Usage: %s <ip of server> \n",argv[0]);
		return 1;
	} 

	// set up
	memset (buff, '0', sizeof (buff));
	memset (&serv_addr, '0', sizeof (serv_addr)); 

	// open socket
	if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf ("Error : Could not create socket \n");
		return 1;
	} 

	// set address
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons (atoi(argv[4])); 

	if (inet_pton (AF_INET, argv[3], &serv_addr.sin_addr) <= 0)
	{
		printf ("inet_pton error occured\n");
		return 1;
	} 

	// connect
	if (connect (sockfd, (struct sockaddr *)&serv_addr, sizeof (serv_addr)) < 0)
	{
		printf ("Error : Connect Failed \n");
		return 1;
	} 
	printf("connected\n");

	//send output file name
	write(sockfd, argv[2], strlen(argv[2]) + 1);
	printf("send output file name\n");

	//send in file text to server
	while((data = fread(buff,1, 10, inputFp)) > 0) {
		write(sockfd, buff, data);
	}
	printf("send in file data\n");

	fclose(inputFp);
	close (sockfd);
	return 0;
}
